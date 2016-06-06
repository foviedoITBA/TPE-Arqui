#include "interrupts.h"
#include "interruptsASM.h"
#include "videoDriver.h"
#include <stdint.h>

#define IDT_SIZE 0xB
#define KEYBOARD_VECTOR 0x9

Idtr idtr;
Idt_Desc idt[IDT_SIZE];

void initializeIDT()
{
	/* Set up IDTR */
	_cli();
	idtr.limit = (uint16_t) sizeof(idt)-1;
	idtr.offset = (uint64_t) idt;
	_lidt(&idtr);

	// Verifica que el idtr haya quedado cargado con el valor adecuado
	/*
	Idtr idtr_aux;
	_sidt(&idtr_aux);
	if (idtr_aux.limit != 16*11-1 || idtr_aux.offset != &(idt[0]))
		print_msg("\nAlgo anda mal\n", RED, WHITE);
	else
		print_msg("\nPor ahora todo bien\n", RED, WHITE);
	*/

	/* Set up keyboard interrupt (keyboard ---> IRQ1 ---> vector 0x9 by BIOS default) */
	uint64_t offset = (uint64_t)_keyboard_ISR;
	
	// Verifica que offset apunte a la primera instrucción de la rutina de atención de interrupción de teclado,
	// que es "push rdi", cuyo opcode es 0x57
	/*	
	if (*(uint8_t*)offset != 0x57)
		print_msg("\nAlgo anda mal\n", RED, WHITE);
	else
		print_msg("\nPor ahora todo bien\n", RED, WHITE);
	*/
	
	idt[KEYBOARD_VECTOR].offset_l = (uint16_t) (offset & 0xFFFF);
	idt[KEYBOARD_VECTOR].offset_m = (uint16_t) ((offset >> 16) & 0xFFFF);
	idt[KEYBOARD_VECTOR].offset_h = (uint32_t) (offset >> 32);
	
	// Verifica que el offset haya quedado bien armado
	/*
	if ((uint64_t) idt[0x9].offset_l + (uint64_t) idt[0x9].offset_m * 0x10000 + (uint64_t) idt[0x9].offset_h * 0x100000000l != _keyboard_ISR)
		print_msg("\nAlgo anda mal...\n", RED, WHITE);
	else
		print_msg("\nPor ahora todo bien\n", RED, WHITE);
	*/

	idt[KEYBOARD_VECTOR].selector = (uint16_t) 0x8;	/* index = 1, TI = 0 (GDT, not LDT), RPL = 0 (maximum privilege) */
	
	idt[KEYBOARD_VECTOR].zero_8_bits = (uint8_t) 0;
	idt[KEYBOARD_VECTOR].zero_32_bits = (uint32_t) 0;
	idt[KEYBOARD_VECTOR].type_attr = (uint8_t) 0x8E; /* Present, ¿32 bits? interrupt gate */

	/* Disable all but keyboard interrupt */
	_mask_for_keyboard();

	// Enable interrupts
	_sti();

}

void _key_handler(uint64_t key_scan_code)
{
	print_msg("Keyboard interrupt\n", RED, WHITE);
	while(1);
}