section .text
		global ft_strdup
		extern malloc

ft_strdup:
			cmp		rdi, 0
			je		_error
			xor		rcx, rcx

_length:
			cmp		BYTE [rdi + rcx], 0
			je		_create_pointer
			inc		rcx
			jmp		_length

_create_pointer:
			push	rdi
			inc		rcx
			mov		rdi, rcx
			call	malloc
			pop		rdi
			cmp		rax, 0
			je		_error
			xor		rcx, rcx
			jmp		_copy

_increment:
			inc		rcx

_copy:
			xor		rdx, rdx
			mov		dl, BYTE [rdi + rcx]
			mov		BYTE [rax + rcx], dl
			cmp		dl, 0
			jne		_increment

_return:
			ret

_error:
			xor		rax, rax
			ret