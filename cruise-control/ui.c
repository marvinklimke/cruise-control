/************************************************************************/
/* project: cruise-control                                              */
/* file:    ui.c                                                        */
/* author:  Marvin Klimke                                               */
/************************************************************************/

#include <avr/io.h>

#include "lib/i2cmaster.h"
#include "ui.h"


uint8_t last_key_state[5] = {0};


void ui_init()
{
    /* initialize I2C library */
    i2c_init();

    /* set all bits on port expander */
    ui_portex_write(0xff);
}

void ui_portex_write(uint8_t data)
{
    /* start I2C link for write access */
    i2c_start_wait(UI_PORTEX_ADDRESS | I2C_WRITE);

    /* write data to bus */
    i2c_write(data);

    /* stop I2C link */
    i2c_stop();
}

uint8_t ui_portex_read()
{
    uint8_t data;

    /* start I2C link for read access */
    i2c_start_wait(UI_PORTEX_ADDRESS | I2C_READ);

    /* receive data from bus */
    data = i2c_readNak();

    /* stop I2C link */
    i2c_stop();

    return data;
}

void ui_write(uint8_t data)
{
    /* apply mask and write data out */
    ui_portex_write(data | UI_SW_MASK);
}

void ui_set_leds(uint8_t led1, uint8_t led2, uint8_t led3)
{
    /* low active */
    led1 = (led1 == 0) ? 1 : 0;
    led2 = (led2 == 0) ? 1 : 0;
    led3 = (led3 == 0) ? 1 : 0;

    /* set all leds according to parameters */
    ui_write((led1<<UI_LED1)|(led2<<UI_LED2)|(led3<<UI_LED3));
}

void ui_change_led(uint8_t led, uint8_t state)
{
    if(state)
    {
        /* low active: on = bit clear */
        ui_write(ui_portex_read() & ~(1<<led));
    }
    else
    {
        /* low active: off = bit set */
        ui_write(ui_portex_read() | (1<<led));
    }
}

uint8_t ui_getkey(uint8_t key)
{
    /* low active: key pressed = bit clear */
    return ui_portex_read() & (1<<key);
}

uint8_t ui_getkey_pulse(uint8_t key)
{
    uint8_t edge;
    uint8_t state;

    /* get current port state */
    state = ui_getkey(key);

    /* rising edge since last round */
    edge = state && !last_key_state[key] ? 1 : 0;

    /* save state for next round */
    last_key_state[key] = state;

    return edge;
}
