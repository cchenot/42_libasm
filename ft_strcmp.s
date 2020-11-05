section 	.text
			global ft_strcmp

ft_strcmp:
			xor rcx, rcx
			xor rax, rax

_comp:
			xor	rdx, rdx
			mov dl, BYTE [rsi + rcx]
			cmp	BYTE [rdi + rcx], dl
			jne	_return
			cmp BYTE [rdi + rcx], 0
			je _return
			cmp BYTE [rsi + rcx], 0
			je _return

_increment:
			inc rcx;
			jmp _comp;

_return:
			movzx rax, BYTE [rdi + rcx]
			movzx rbx, BYTE [rsi + rcx]
			sub rax, rbx
			ret