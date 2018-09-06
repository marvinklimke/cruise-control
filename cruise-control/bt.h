/************************************************************************/
/* project: cruise-control                                              */
/* file:    bt.h                                                        */
/* author:  Marvin Klimke                                               */
/************************************************************************/

#ifndef BT_H_
#define BT_H_

#include <stdint.h>


#define BT_ACK 64
#define BT_NAK 65
#define BT_SYNC 66
#define BT_DESYNC 67
#define BT_START 68
#define BT_STOP 69
#define BT_SETSPEED 70

#define BT_SETPOINT 128
#define BT_CURRENTRPM 129
#define BT_CONTROLLER 130
#define BT_KP 131
#define BT_KI 132
#define BT_KD 133
#define BT_EMAX 134


/* initialize bluetooth uart */
void bt_init(uint16_t baudrate);

/* receive 8bit integer */
int8_t bt_recv_i8(uint8_t newline);

/* receive 16bit integer */
int16_t bt_recv_i16(uint8_t newline);

/* receive 32bit integer */
int32_t bt_recv_i32(uint8_t newline);

/* send 8bit integer */
void bt_send_i8(int8_t value, uint8_t newline);

/* send 16bit integer */
void bt_send_i16(int16_t value, uint8_t newline);

/* send 32bit integer */
void bt_send_i32(int32_t value, uint8_t newline);


#endif /* BT_H_ */