#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdint.h>

#pragma pack(push)
#pragma pack(1)

typedef struct
{
	uint16_t limit;
	uint64_t offset;
} Idtr;

typedef struct
{
	uint16_t offset_l;
	uint16_t selector;
	uint8_t zero_8_bits;
	uint8_t type_attr;
	uint16_t offset_m;
	uint32_t offset_h;
	uint32_t zero_32_bits;
} Idt_Desc;

#pragma pack(pop)

#endif