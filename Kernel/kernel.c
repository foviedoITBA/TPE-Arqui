#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include "videoDriver.h"
#include "interrupts.h"
#include "interruptsASM.h"

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};
	clear_screen();
	print_msg("KERNEL\n\n", GREEN, BLUE);
	
	print_msg("Loading modules... \n", GREEN, BLUE);
	loadModules(&endOfKernelBinary, moduleAddresses);
	print_msg("Done\n", GREEN, BLUE);
	print_msg("Clearing Kernel's bss... ", GREEN, BLUE);
	clearBSS(&bss, &endOfKernel - &bss);
	print_msg(" Done loading modules\n", GREEN, BLUE);

	print_msg("Setting up stack...\n", GREEN, BLUE);
	return getStackBase();
}

int main()
{	
	print_msg("Calling sample code module...\n", GREEN, BLUE);
	((EntryPoint)sampleCodeModuleAddress)();
	print_msg("Done\n", GREEN, BLUE);
	
	print_msg("Initializing IDT... ", GREEN, BLUE);
	initializeIDT();
	print_msg("Done\n", GREEN, BLUE);

	reset_position();
	
	while(1);
	return 0;
}
