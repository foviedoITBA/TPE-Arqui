#ifndef IO_ASM_H
#define IO_ASM_H

#include <stdint.h>

extern void _out_16(uint16_t port, uint16_t data);
extern uint16_t _in_16(uint16_t port);

#endif