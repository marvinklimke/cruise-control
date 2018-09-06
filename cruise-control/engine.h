/************************************************************************/
/* project: cruise-control                                              */
/* file:    engine.h                                                    */
/* author:  Marvin Klimke                                               */
/************************************************************************/

#ifndef ENGINE_H_
#define ENGINE_H_

#include <stdint.h>


/* engine impulses on RPM input per turn */
#define ENGINE_TURN_PULSE 3

/* number of turns to smooth rpm value */
#define ENGINE_SMOOTH_TURNS 1

/* total number of pulses to save for rpm calculation */
#define ENGINE_TOTAL_PULSES (ENGINE_SMOOTH_TURNS*ENGINE_TURN_PULSE)

/* ignore impulses below this threshold (µs) */
#define ENGINE_INTERVAL_MIN 2000

/* ignore impulses above this threshold (µs) */
#define ENGINE_INTERVAL_MAX 200000


/* initialize engine ports and timer */
void engine_init();

/* get current RPM value */
uint16_t engine_get_rpm();

/* get the current idle state */
uint8_t engine_is_idle();


#endif /* ENGINE_H_ */