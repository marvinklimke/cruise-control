/************************************************************************/
/* project: cruise-control                                              */
/* file:    adc.c                                                       */
/* author:  Marvin Klimke                                               */
/************************************************************************/

#include <avr/io.h>

#include "adc.h"


void adc_init()
{
    /* use external reference */
    ADMUX = 0x00;
    
    /* prescaler 128 */
    ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    
    /* enable ADC */
    ADCSRA |= (1 << ADEN);
    
    /* start test measurement */
    ADCSRA |= (1<<ADSC);

    /* wait for measurement to finish */
    while (ADCSRA & (1<<ADSC));
}

uint16_t adc_read(uint8_t channel)
{
    /* select channel, masking all other bits */
    ADMUX = (ADMUX & ~(0x1F)) | (channel & 0x1F);
    
    /* start measurement */
    ADCSRA |= (1<<ADSC);
    
    /* wait for measurement to finish */
    while(ADCSRA & (1<<ADSC));
    
    /* read and return value */
    return ADCW;
}

uint16_t adc_read_avg(uint8_t channel, uint8_t n)
{
    uint16_t sum = 0;
    uint8_t i;
    
    /* do multiple measurements */ 
    for(i = 0; i < n; i++)
    {
        sum += adc_read(channel);
    }
    
    /* return mean value */
    return sum / n;
}

uint16_t adc_read_mv(uint8_t channel)
{
    return adc_read(channel) * ADC_REFERENCE / 1024;
}
