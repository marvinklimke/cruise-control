/************************************************************************/
/* project: cruise-control                                              */
/* file:    ui.h                                                        */
/* author:  Marvin Klimke                                               */
/************************************************************************/

#ifndef UI_H_
#define UI_H_

#include <stdint.h>


/* address of the PCF8574 port expander */
#define UI_PORTEX_ADDRESS 0x40

/* pin mapping of port expander */
#define UI_SW1 0
#define UI_SW2 1
#define UI_SW3 2
#define UI_SW4 3
#define UI_SW5 4
#define UI_LED1 5
#define UI_LED2 6
#define UI_LED3 7
#define UI_SW_MASK ((1<<UI_SW1)|(1<<UI_SW2)|(1<<UI_SW3)|(1<<UI_SW4)|(1<<UI_SW5))

/* readable pin names */
#define UI_SW_IO UI_SW1
#define UI_SW_SETSPEED UI_SW2
#define UI_SW_INCSPEED UI_SW3
#define UI_SW_DECSPEED UI_SW4
#define UI_SW_NC UI_SW5
#define UI_LED_RUNNING UI_LED1
#define UI_LED_INCREQ UI_LED2
#define UI_LED_DECREQ UI_LED3


/* initialize I2C link and port expander */
void ui_init();

/* write byte to port expander */
void ui_portex_write(uint8_t data);

/* read byte from portexpander */
uint8_t ui_portex_read();

/* write masked byte to port expander */
void ui_write(uint8_t data);

/* set all LEDs on portexpander */
void ui_set_leds(uint8_t led1, uint8_t led2, uint8_t led3);

/* change one LED on portexpander */
void ui_change_led(uint8_t led, uint8_t state);

/* check one switch on portexpander */
uint8_t ui_getkey(uint8_t key);

/* check for falling edge on portexpander */
uint8_t ui_getkey_pulse(uint8_t key);


#endif /* UI_H_ */
