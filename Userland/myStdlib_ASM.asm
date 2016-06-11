global _write
global _malloc
global _free
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

_malloc:
	push rbp
	mov rbp, rsp
	push rbx
	mov rax, 2	;sys_malloc
	mov rbx, rdi
	int 80h		;system call
	pop rbx
	leave
	ret

_free:
	push rbp
	mov rbp, rsp
	push rbx
	mov rax, 3	;sys_free
	mov rbx, rdi
	int 80h		;system call
	pop rbx
	leave
	ret
	