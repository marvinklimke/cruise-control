/************************************************************************/
/* project: cruise-control                                              */
/* file:    adc.h                                                       */
/* author:  Marvin Klimke                                               */
/************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>


/* ADC reference voltage (mV) */
#define ADC_REFERENCE 4900


/* initialize ADC reference and prescaler */
void adc_init();

/* read a value from the given ADC channel */
uint16_t adc_read(uint8_t channel);

/* read values from the given ADC channel and mean over n samples */
uint16_t adc_read_avg(uint8_t channel, uint8_t n);

/* get voltage from ADC (mV) */
uint16_t adc_read_mv(uint8_t channel);


#endif /* ADC_H_ */
