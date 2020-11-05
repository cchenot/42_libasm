section	.data

section	.text
		global ft_strlen

ft_strlen:
		mov rax, 0
		jmp _compare

_compare:
		cmp BYTE [rdi], 0
		jne _increment
		ret

_increment:
		inc rax
		inc rdi
		jmp _compare