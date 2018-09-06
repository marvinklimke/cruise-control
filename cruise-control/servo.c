/************************************************************************/
/* project: cruise-control                                              */
/* file:    servo.c                                                     */
/* author:  Marvin Klimke                                               */
/************************************************************************/

#include <avr/interrupt.h>
#include <avr/io.h>

#include "servo.h"


/* interrupt service routine for timer 1 compare match */
ISR(TIMER1_COMPA_vect)
{
    /* set timer to rest of period */
    OCR1A = (SERVO_PERIOD_US * SERVO_PRESCALER) - OCR1A;

    /* toggle servo data pin */
    PORTD ^= (1 << PIND5);
}


void servo_init()
{
    /* declare servo data pin as output */
    DDRD = (1 << PIND5);
    
    /* configure timer 1 as: waveform=ctc-mode, prescaler=8 (16MHz / 8 = 2ticks/µs) */
    TCCR1B = (1 << WGM12) | (1 << CS01);

    /* enable timer 1 compare interrupt */
    TIMSK1 = (1 << OCIE1A);
    
    /* move servo to default position */
    OCR1A = (SERVO_PERIOD_US - SERVO_DEFAULT_US) * SERVO_PRESCALER;
}

void servo_write(uint16_t value)
{
    /* constrain value to valid interval */
    if(value > SERVO_MAX_US) value = SERVO_MAX_US;
    if(value < SERVO_MIN_US) value = SERVO_MIN_US;

    /* turn time (µs) into ticks */
    value *= SERVO_PRESCALER;
    
    /* disable interrupts */
    cli();

    /* mirror period on half */
    if(OCR1A > (SERVO_PERIOD_US * SERVO_PRESCALER / 2))
    {
        value = (SERVO_PERIOD_US * SERVO_PRESCALER) - value;
    }

    /* set value for timer */
    OCR1A = value;

    /* enable interrupts */
    sei();
}

uint16_t servo_read()
{
    uint16_t value = 0;
    
    /* disable interrupts */
    cli();

    /* read value from timer */
    value = OCR1A;

    /* enable interrupts */
    sei();
    
    /* mirror period on half */
    if(value > (SERVO_PERIOD_US * SERVO_PRESCALER / 2))
    {
        value = (SERVO_PERIOD_US * SERVO_PRESCALER) - value;
    }

    /* turn ticks into time (µs) */
    value /= SERVO_PRESCALER;
    
    return value;
}

void servo_write_adj(int16_t value)
{
    servo_write(1000 - value);
}
