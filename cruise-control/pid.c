/************************************************************************/
/* project: cruise-control                                              */
/* file:    pid.c                                                       */
/* author:  Marvin Klimke                                               */
/************************************************************************/

#include "pid.h"


/* current setpoint */
int32_t setpoint = 0;

/* proportional factor */
int32_t kp = PID_DEFAULT_KP;

/* integral factor */
int32_t ki = PID_DEFAULT_KI;

/* differential factor */
int32_t kd = PID_DEFAULT_KD;

/* maximum error sum */
int32_t emax = PID_DEFAULT_EMAX;

/* error from last round for differential part */
int32_t eold = 0;

/* error sum for integral part */
int32_t esum = 0;


void pid_setpoint(int32_t new_setpoint)
{
    setpoint = new_setpoint;
}

void pid_reset()
{
    eold = 0;
    esum = 0;
}

int32_t pid_control(int32_t actual)
{
    int32_t e;
    int32_t ediff;

    /* calculate error */
    e = setpoint - actual;

    /* integrate error */
    esum += e;

    /* constrain error sum */
    if(esum > emax) esum = emax;
    if(esum < -emax) esum = -emax;

    /* calculate derivation */
    ediff = e - eold;

    /* save error for next round */
    eold = e;

    /* calculate pid result */
    return (kp * e + ki * esum + kd * ediff) / PID_SCALING;
}

int32_t pid_get_kp() { return kp; }
int32_t pid_get_ki() { return ki; }
int32_t pid_get_kd() { return kd; }
int32_t pid_get_emax() {return emax; }

void pid_set_kp(int32_t new_kp) { kp = new_kp; }
void pid_set_ki(int32_t new_ki) { ki = new_ki; }
void pid_set_kd(int32_t new_kd) { kd = new_kd; }
void pid_set_emax(int32_t new_emax) { emax = new_emax; }
