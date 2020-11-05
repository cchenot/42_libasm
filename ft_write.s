section	.text
		global	ft_write
		extern	__errno_location

ft_write:
			mov rax, 1
			syscall
			cmp rax, 0
			jl	error

success:
			push rax
			call __errno_location
			mov dword [rax], 0
			pop rax
			ret

error:
			xor rbx, rbx
			neg eax
			mov ebx, eax
			call __errno_location
			mov dword [rax], ebx
			mov rax, -1
			ret