/************************************************************************/
/* project: cruise-control                                              */
/* file:    servo.h                                                     */
/* author:  Marvin Klimke                                               */
/************************************************************************/

#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>


/* servo signal impulse maximum length (탎) */
#define SERVO_MAX_US 2000

/* servo signal impulse minimum length (탎) */
#define SERVO_MIN_US 1000

/* servo signal impulse default length (탎) */
#define SERVO_DEFAULT_US 1000

/* servo signal period length (탎) */
#define SERVO_PERIOD_US 20000U

/* servo timer prescaler (ticks/탎) */
#define SERVO_PRESCALER 2


/* initialize servo port and timer */
void servo_init();

/* write value to servo timer */
void servo_write(uint16_t value);

/* read value from servo timer */
uint16_t servo_read();

/* write adjusted value to servo */
void servo_write_adj(int16_t value);


#endif /* SERVO_H_ */
