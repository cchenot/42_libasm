section	.text
		global ft_strcpy

ft_strcpy:
			xor	rdx, rdx
			xor rcx, rcx

_copy:
			mov	dl, BYTE [rsi + rcx]
			mov BYTE [rdi + rcx], dl
			cmp	dl, 0
			je	_return
			inc	rcx
			jmp _copy

_return:
			mov rax, rdi
			ret