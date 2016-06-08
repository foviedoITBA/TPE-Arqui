#include "systemcalls.h"
#include "interrupts.h"
#include "interruptsASM.h"

#define SYSTEMCALLS_VECTOR 0x80

void setupSystemcalls()
{
	add_IDT_descriptor(SYSTEMCALLS_VECTOR, (uint64_t) _systemcalls_ISR);
}