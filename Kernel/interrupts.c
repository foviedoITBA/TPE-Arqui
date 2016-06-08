#include "interrupts.h"
#include "interruptsASM.h"
#include "videoDriver.h"
#include <stdint.h>

#define IDT_SIZE 0x24
#define KEYBOARD_VECTOR 0x21

Idtr idtr;
Idt_Desc idt[IDT_SIZE];

void initializeIDT()
{
	/* Set up IDTR */
	_cli();
	idtr.limit = (uint16_t) sizeof(idt)-1;
	idtr.offset = (uint64_t) idt;
	_lidt(&idtr);

	/* Set up keyboard interrupt (keyboard ---> IRQ1 ---> vector 0x21)*/
	uint64_t offset = (uint64_t)_keyboard_ISR;

	idt[KEYBOARD_VECTOR].offset_l = (uint16_t) (offset & 0xFFFF);
	idt[KEYBOARD_VECTOR].offset_m = (uint16_t) ((offset >> 16) & 0xFFFF);
	idt[KEYBOARD_VECTOR].offset_h = (uint32_t) (offset >> 32);
	idt[KEYBOARD_VECTOR].selector = (uint16_t) 0x8;	/* index = 1, TI = 0 (GDT, not LDT), RPL = 0 (maximum privilege) */
	idt[KEYBOARD_VECTOR].zero_8_bits = (uint8_t) 0;
	idt[KEYBOARD_VECTOR].zero_32_bits = (uint32_t) 0;
	idt[KEYBOARD_VECTOR].type_attr = (uint8_t) 0x8E; /* Present, ¿32 bits? interrupt gate */

	/* Disable all but keyboard interrupt */
	_pic_mask(0xFFFD);

	// Enable interrupts
	_sti();

}

void _key_handler(uint64_t key_scan_code)
{
	print_msg("Keyboard interrupt\n", RED, WHITE);
}