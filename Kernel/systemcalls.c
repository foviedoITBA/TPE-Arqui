#include "systemcalls.h"
#include "interrupts.h"
#include "interruptsASM.h"
#include "videoDriver.h"

#define SYSTEMCALLS_VECTOR 0x80

static uint64_t (*syscalls[4])();
static uint64_t sys_write(uint64_t buffer, uint64_t bytes);
static uint64_t sys_read(uint64_t buffer, uint64_t bytes);
static uint64_t sys_malloc(uint64_t bytes);
static uint64_t sys_free();
static void * mem = 0xA00000;

void setupSystemcalls()
{
	syscalls[0] = sys_write;
	syscalls[1] = sys_read;
	syscalls[2] = sys_malloc;
	syscalls[3] = sys_free;
	add_IDT_descriptor(SYSTEMCALLS_VECTOR, (uint64_t) _systemcalls_ISR);
}

void systemcalls_dispatcher(uint64_t number, uint64_t first_parameter, uint64_t second_parameter)
{
	return (*syscalls[number])(first_parameter, second_parameter);
}

static uint64_t sys_write(uint64_t buffer, uint64_t bytes)
{
	video_write((char *) buffer, bytes);
	return 0;
}

static uint64_t sys_read(uint64_t buffer, uint64_t bytes)
{
	return 0;
}

static uint64_t sys_malloc(uint64_t bytes)
{
	void * aux = mem;
	mem = ((char*) mem) + bytes;
	return aux;
}

static uint64_t sys_free()
{
	return 0;
}