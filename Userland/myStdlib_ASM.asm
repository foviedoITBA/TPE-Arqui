global _write
global _read
global _malloc
global _free
global _remove_char
global _fractal
section .text
_write:
	push rbp
	mov rbp, rsp
	push rax
	push rbx
	push rcx
	mov rax, 0		;sys_write
	mov rbx, rdi	;buffer
	mov rcx, rsi	;bytes
	int 80h			;system call
	pop rcx
	pop rbx
	pop rax
	leave
	ret

_read:
	push rbp
	mov rbp, rsp
	push rax
	push rbx
	push rcx
	mov rax, 1		;sys_read
	mov rbx, rdi	;key holder
	mov rcx, rsi	;bytes
	int 80h			;system call
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

_remove_char:
	push rbp
	mov rbp, rsp
	mov rax, 4	;sys_remove_char
	int 80h		;system call
	leave
	ret

_fractal:
	push rbp
	mov rbp, rsp
	mov rax, 5	;sys_fractal
	int 80h		;system call
	leave
	ret