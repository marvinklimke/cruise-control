/************************************************************************/
/* project: cruise-control                                              */
/* file:    clock.c                                                     */
/* author:  Marvin Klimke                                               */
/************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>

#include "clock.h"


volatile uint32_t vo_overflows = 0;

/* interrupt service routine for timer 2 overflow */
ISR(TIMER2_OVF_vect)
{
    ++vo_overflows;
}


void clock_init()
{
    /* reset timer 2 counter */
    TCNT2 = 0;

    /* configure timer 2 as: prescaler=8 (16MHz / 8 = 2ticks/µs) */
    TCCR2B = (1 << CS21);

    /* enable timer 2 overflow interrupt */
    TIMSK2 = (1 << TOIE2);
}

uint32_t clock_micros()
{
    uint32_t overflows, counter;

    /* disable interrupts */
    cli();

    /* save timer values */
    overflows = vo_overflows;
    counter = TCNT2;

    /* enable interrupts */
    sei();
    
    /* calculate time in µs */
    return overflows*128 + counter/2;
}

uint32_t clock_millis()
{
    return clock_micros() / 1000;
}

uint32_t clock_seconds()
{
    return clock_millis() / 1000;
}
