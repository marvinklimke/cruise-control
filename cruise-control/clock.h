/************************************************************************/
/* project: cruise-control                                              */
/* file:    clock.h                                                     */
/* author:  Marvin Klimke                                               */
/************************************************************************/

#ifndef CLOCK_H_
#define CLOCK_H_

#include <stdint.h>


/* initialize clock timer */
void clock_init();

/* get current time in µs */
uint32_t clock_micros();

/* get current time in ms */
uint32_t clock_millis();

/* get current time in s */
uint32_t clock_seconds();


#endif /* CLOCK_H_ */
