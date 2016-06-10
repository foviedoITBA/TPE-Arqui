global _write
section .text
_write:
	push rbp
	mov rbp, rsp
	push rax
	push rbx
	push rcx
	mov rax, 0		;write
	mov rbx, rdi	;buffer
	mov rcx, rsi	;bytes
	int 80h			;systemcall
	pop rcx
	pop rbx
	pop rax
	leave
	ret