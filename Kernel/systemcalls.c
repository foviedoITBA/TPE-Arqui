#include "systemcalls.h"
#include "interrupts.h"
#include "interruptsASM.h"
#include "videoDriver.h"
#include "bga.h"

#define SYSTEMCALLS_VECTOR 0x80
#define BACKSPACE 8

static uint64_t (*syscalls[6])();
static uint64_t sys_write(uint64_t buffer, uint64_t bytes);
static uint64_t sys_read(uint64_t key_holder, uint64_t bytes);
static uint64_t sys_malloc(uint64_t bytes);
static uint64_t sys_free();
static uint64_t sys_remove_char();
static uint64_t sys_fractal();

typedef enum {FALSE = 0, TRUE} BOOL;

/* For sys_malloc */
static void * dynamic_mem = (void*) 0xA00000;

/* For sys_read */
static char * fill_char;
static int fill_bytes;
static BOOL reading = FALSE;

void setupSystemcalls()
{
	syscalls[0] = sys_write;
	syscalls[1] = sys_read;
	syscalls[2] = sys_malloc;
	syscalls[3] = sys_free;
	syscalls[4] = sys_remove_char;
	syscalls[5] = sys_fractal;
	add_IDT_descriptor(SYSTEMCALLS_VECTOR, (uint64_t) _systemcalls_ISR);
}

uint64_t systemcalls_dispatcher(uint64_t number, uint64_t first_parameter, uint64_t second_parameter)
{
	return (*syscalls[number])(first_parameter, second_parameter);
}

static uint64_t sys_write(uint64_t buffer, uint64_t bytes)
{
	video_write((char *) buffer, bytes);
	return 0;
}

static uint64_t sys_read(uint64_t key_holder, uint64_t bytes)
{
	if (bytes == 0)
		return 1;
	fill_char = (char*) key_holder;
	fill_bytes = bytes;
	reading = TRUE;
	return 0;
}

void send_key(char key)
{
	if (key == 0 || reading == FALSE)
		return;
	*fill_char = key;
	if (key == BACKSPACE)
		fill_bytes++;
	else
		fill_bytes--;
	if (fill_bytes == 0 || key == '\n')
		reading = FALSE;
}

static uint64_t sys_malloc(uint64_t bytes)
{
	void * aux = dynamic_mem;
	dynamic_mem = ((char*) dynamic_mem) + bytes;
	return (uint64_t) aux;
}

static uint64_t sys_free()
{
	return 0;
}

static uint64_t sys_remove_char()
{
	video_remove_char();
	return 0;
}

static uint64_t sys_fractal()
{
	print_fractal();
	return 0;
}