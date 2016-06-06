#ifndef INTERRUPTS_ASM_H
#define INTERRUPTS_ASM_H

#include "interrupts.h"

extern void _sti(void);
extern void	_cli(void);
extern void _lidt(Idtr * idtr);
extern void _sidt(Idtr * idtr);
extern void _keyboard_ISR();
extern void _mask_for_keyboard();

#endif