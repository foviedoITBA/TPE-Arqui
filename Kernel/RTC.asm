global _get_seconds
global _get_minutes
global _get_hours

section .text
_get_seconds:
	mov eax, 0
	out 70h,al
	in al,71h
	ret

_get_minutes:
	mov eax, 2
	out 70h, al
	in al, 71h
	ret

_get_hours:
	mov eax, 4
	out 70h, al
	in al, 71h
	ret