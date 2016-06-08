global _cli
global _sti
global _lidt
global _sidt
global _keyboard_ISR
global _PIT_ISR
global _systemcalls_ISR
global _pic_mask
extern key_handler
extern update_clock
section .text

_cli:
	cli
	ret

_sti:
	sti
	ret

_lidt:
	lidt [rdi]
	ret

_sidt:
	sidt [rdi]
	ret

_keyboard_ISR:
	push rdi
	xor rax, rax
	in al, 0x64		; verify there's
	and rax, 0x1	; a key
	cmp rax, 0x1	; to be read
	jne fin
	in al, 0x60		; read key
	mov rdi, rax
	call key_handler
fin:
	mov al, 20h
	out 20h, al		; EOI
	pop rdi
	iretq

_PIT_ISR:
	call update_clock
	mov al, 20h
	out 20h, al		; EOI
	iretq

_systemcalls_ISR:
	iretq

_pic_mask:
	push rax
	mov rax, rdi
	out 21h, al
	pop rax
	ret