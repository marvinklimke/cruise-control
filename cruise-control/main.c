/************************************************************************/
/* project: cruise-control                                              */
/* file:    main.c                                                      */
/* author:  Marvin Klimke                                               */
/************************************************************************/

#include <math.h>
#include <stdlib.h>

#include <avr/interrupt.h>
#include <avr/io.h>

#include "lib/uart.h"
#include "adc.h"
#include "bt.h"
#include "clock.h"
#include "engine.h"
#include "pid.h"
#include "servo.h"
#include "ui.h"


/* cpu frequency (Hz) */
#define F_CPU 16000000UL

/* mainloop execution period (ms) */
#define MAINLOOP_PERIOD 100

/* setpoint rpm decrement & increment */
#define RPM_STEP 50


/* bluetooth application in sync */
uint8_t bt_sync = 0;

/* controller currently active */
uint8_t running = 0;

/* last main loop iteration time */
uint32_t msec = 0;

/* setpoint for rpm controller */
uint16_t setpoint_rpm = 3000;

/* current rpm */
uint16_t current_rpm = 0;

/* servo regulating variable */
int16_t controller_output = 0;


void init_components()
{
    adc_init();
    bt_init(UART_BAUD_SELECT(9600, F_CPU));
    clock_init();
    engine_init();
    servo_init();
    ui_init();
}

void task_controller()
{
    controller_output = pid_control(current_rpm);
    servo_write_adj(controller_output);
}

void start_controller()
{
    running = 1;
    bt_send_i8(BT_START, 1);
}

void stop_controller()
{
    running = 0;
    servo_write_adj(0);
    pid_reset();
    bt_send_i8(BT_STOP, 1);
}

void update_setpoint()
{
    pid_setpoint(setpoint_rpm);
    bt_send_i8(BT_SETPOINT, 0);
    bt_send_i16(setpoint_rpm, 1);
}

void task_ui()
{
    /* enable/disable */
    if(ui_getkey_pulse(UI_SW_IO)) {
        if(running) {
            stop_controller();
        } else {
            start_controller();
        }
    }
    
    /* set current rpm as setpoint */
    if(ui_getkey_pulse(UI_SW_SETSPEED)) {
        setpoint_rpm = engine_get_rpm();
        update_setpoint();
        start_controller();
    }

    /* decrement rpm setpoint */
    if(ui_getkey_pulse(UI_SW_DECSPEED)) {
        setpoint_rpm -= RPM_STEP;
        update_setpoint();
    }

    /* increment rpm setpoint */
    if(ui_getkey_pulse(UI_SW_INCSPEED)) {
        setpoint_rpm += RPM_STEP;
        update_setpoint();
    }

    /* update notification leds */
    ui_set_leds(running, running && controller_output >= 0, running && controller_output <= -1000);
}

void task_bt()
{
    /* to be implemented */
}

int main(void)
{
    /* init all components */
    init_components();

    /* save initial setpoint */
    pid_setpoint(setpoint_rpm);

    /* enable interrupts */
    sei();

    /* mainloop */
    while(1)
    {
        msec = clock_millis();

        current_rpm = engine_get_rpm();

        /* controller task */
        if(running)
        {
            task_controller();
        }

        /* send current values to bluetooth device */
        if(bt_sync) {
            bt_send_i8(BT_CURRENTRPM, 0);
            bt_send_i16(current_rpm, 1);
            bt_send_i8(BT_CONTROLLER, 0);
            bt_send_i16(controller_output, 1);
        }

        /* handle user interface */
        do {

            task_ui();
            task_bt();

        } while((clock_millis() - msec) < MAINLOOP_PERIOD);

    }

    return 0;
}
