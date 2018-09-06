/************************************************************************/
/* project: cruise-control                                              */
/* file:    pid.h                                                       */
/* author:  Marvin Klimke                                               */
/************************************************************************/

#ifndef PID_H_
#define PID_H_

#include <stdint.h>


/* default proportional factor */
#define PID_DEFAULT_KP 200

/* default integral factor */
#define PID_DEFAULT_KI 30

/* default differential factor */
#define PID_DEFAULT_KD 0

/* default maximum error sum */
#define PID_DEFAULT_EMAX 20000

/* pid scaling factor for fixed point arithmetic */
#define PID_SCALING 1000

/* set pid setpoint */
void pid_setpoint(int32_t new_setpoint);

/* reset pid error sum */
void pid_reset();

/* calculate pid */
int32_t pid_control(int32_t actual);

/* parameter controller getter */
int32_t pid_get_kp();
int32_t pid_get_ki();
int32_t pid_get_kd();
int32_t pid_get_emax();

/* parameter controller setter */
void pid_set_kp(int32_t new_kp);
void pid_set_ki(int32_t new_ki);
void pid_set_kd(int32_t new_kd);
void pid_set_emax(int32_t new_emax);


#endif /* PID_H_ */
