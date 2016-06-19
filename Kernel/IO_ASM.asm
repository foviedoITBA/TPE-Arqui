global _out_16
global _in_16
section .text
; void _out_16(uint16_t port, uint16_t data)
_out_16:
	push rbp
	mov rbp, rsp
	push rdx
	push rax
	mov rdx, rdi
	mov rax, rsi
	out dx, ax
	pop rax
	pop rdx
	leave
	ret

; uint16_t _in_16(uint16_t port)
_in_16:
	push rbp
	mov rbp, rsp
	push rdx
	mov rdx, rdi
	in ax, dx
	pop rdx
	leave
	ret