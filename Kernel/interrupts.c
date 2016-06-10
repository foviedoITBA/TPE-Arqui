#include "interrupts.h"
#include "interruptsASM.h"
#include "videoDriver.h"
#include <stdint.h>


#define IDT_SIZE 0xFF /* Arbitrario */
#define KEYBOARD_VECTOR 0x21
#define TIMER_TICK_VECTOR 0x20
#define CODE_SEGMENT_SELECTOR 0x8 /* index = 1, TI = 0 (GDT, not LDT), RPL = 0 (maximum privilege) */
#define TYPE_ATTR 0x8E /* Present, interrupt gate */

Idtr idtr;
Idt_Desc idt[IDT_SIZE];

void initializeIDT()
{
	/* Set up IDTR */
	_cli();
	idtr.limit = (uint16_t) sizeof(idt)-1;
	idtr.offset = (uint64_t) idt;
	_lidt(&idtr);

	/* Set up keyboard interrupt (keyboard ---> IRQ1 ---> vector 0x21) */
	add_IDT_descriptor(KEYBOARD_VECTOR, (uint64_t)_keyboard_ISR);
	/* Set up timer tick interrupt (PIT ---> IRQ0 ---> vector 0x20) */
	add_IDT_descriptor(TIMER_TICK_VECTOR, (uint64_t)_PIT_ISR);

	/* Enable only keyboard and timer tick */
	_pic_mask(0xFFFC);

	// Enable interrupts
	_sti();

}

void add_IDT_descriptor(uint32_t index, uint64_t ISR)
{
	idt[index].offset_l = (uint16_t) (ISR & 0xFFFF);
	idt[index].offset_m = (uint16_t) ((ISR >> 16) & 0xFFFF);
	idt[index].offset_h = (uint32_t) (ISR >> 32);
	idt[index].selector = (uint16_t) CODE_SEGMENT_SELECTOR;
	idt[index].zero_8_bits = (uint8_t) 0;
	idt[index].zero_32_bits = (uint32_t) 0;
	idt[index].type_attr = (uint8_t) TYPE_ATTR;
}
