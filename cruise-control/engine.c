/************************************************************************/
/* project: cruise-control                                              */
/* file:    engine.c                                                    */
/* author:  Marvin Klimke                                               */
/************************************************************************/

#include <avr/interrupt.h>
#include <avr/io.h>

#include "engine.h"
#include "clock.h"


volatile uint32_t vo_deltas[ENGINE_TOTAL_PULSES] = {0};


/* interrupt service routine for INT0 rising edge */
ISR(INT0_vect)
{
    /* current time */
    static uint32_t msec;

    /* time from last round */
    static uint32_t last;

    /* time delta between rounds */
    static uint32_t delta;

    /* index variable */
    static uint8_t idx;
    
    /* get current time (µs) */
    msec = clock_micros();

    /* calculate time delta since last round */
    delta = msec - last;
    
    /* ignore time deltas below threshold (debounce) */
    if(delta < ENGINE_INTERVAL_MIN)
    {
        return;
    }

    /* ignore time deltas above threshold (reset) */
    if(delta > ENGINE_INTERVAL_MAX)
    {
        delta = 0;
    }

    /* cyclic indexing */
    idx = (idx+1) % ENGINE_TOTAL_PULSES;

    /* save time delta */
    vo_deltas[idx] = delta;

    /* save time for next round */
    last = msec;
}


void engine_init()
{
    /* engine RPM input */
    DDRD &= ~(1<<PIND2);

    /* engine idle input */
    DDRB &= ~(1<<PINB2);

    /* trigger INT0 on rising edge */
    EICRA = (1<<ISC01) | (1<<ISC00);

    /* enable external INT0 */
    EIMSK = (1<<INT0);
}

uint16_t engine_get_rpm()
{
    uint32_t delta = 0;
    uint8_t i;

    /* disable interrupts */
    cli();

    /* calculate total delta for one turn */
    for(i = 0; i < ENGINE_TOTAL_PULSES; ++i)
    {
        delta += vo_deltas[i];
    }

    /* enable interrupts */
    sei();
    
    /* calculate RPM from 60 000 000 µs / delta µs */
    return 60000000UL * ENGINE_SMOOTH_TURNS / delta;
}

uint8_t engine_is_idle()
{
    /* idle if pin B.2 not set */
    return (PINB & PINB2) ? 0 : 1;
}
