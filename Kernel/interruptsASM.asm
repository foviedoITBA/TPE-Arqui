global _cli
global _sti
global _lidt
global _sidt
global _keyboard_ISR
global _mask_for_keyboard
extern _key_handler
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
	;hlt			; para ver si entra a la rutina, trato de colgar la máquina para que no se reinicie
	push rdi
	xor rax, rax
	in al, 0x64		; verify there's
	and rax, 0x1	; a key
	cmp rax, 0x1	; to be read
	jne fin
	in al, 0x60		; read key
	mov rdi, rax
	call _key_handler
fin:
	mov al, 20h
	out 20h, al		; EOI
	pop rdi
	iretq

_mask_for_keyboard:
	push rax
	mov ax, 0xFFFD	; enable only IRQ1 (keyboard)
	out 21h, al
	pop rax
	ret
