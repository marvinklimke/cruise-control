/************************************************************************/
/* project: cruise-control                                              */
/* file:    bt.c                                                        */
/* author:  Marvin Klimke                                               */
/************************************************************************/

#include "lib/uart.h"
#include "bt.h"


void bt_init(uint16_t baudrate)
{
    uart0_init(baudrate);
}

int8_t bt_recv_i8(uint8_t newline)
{
    int8_t c1;
    while(uart0_available() < 1);
    c1 = uart0_getc() & 0xff;
    if(newline) {
        while(uart0_getc() != '\n');
    }
    return c1;
}

int16_t bt_recv_i16(uint8_t newline)
{
    int16_t c1, c2;
    while(uart0_available() < 2);
    c1 = uart0_getc() & 0xff;
    c2 = uart0_getc() & 0xff;
    if(newline) {
        while(uart0_getc() != '\n');
    }
    return c1 | c2 << 8;
}

int32_t bt_recv_i32(uint8_t newline)
{
    int32_t c1, c2, c3, c4;
    while(uart0_available() < 4);
    c1 = uart0_getc() & 0xff;
    c2 = uart0_getc() & 0xff;
    c3 = uart0_getc() & 0xff;
    c4 = uart0_getc() & 0xff;
    if(newline) {
        while(uart0_getc() != '\n');
    }
    return c1 | c2 << 8 | c3 << 16 | c4 << 24;
}

void bt_send_i8(int8_t value, uint8_t newline)
{
    uart0_putc(value);
    if(newline) {
        uart0_putc('\n');
    }
}

void bt_send_i16(int16_t value, uint8_t newline)
{
    uart0_putc(value & 0xff);
    uart0_putc((value>>8) & 0xff);
    if(newline) {
        uart0_putc('\n');
    }
}

void bt_send_i32(int32_t value, uint8_t newline)
{
    uart0_putc(value & 0xff);
    uart0_putc((value>>8) & 0xff);
    uart0_putc((value>>16) & 0xff);
    uart0_putc((value>>24) & 0xff);
    if(newline) {
        uart0_putc('\n');
    }
}
