section	.text
		global ft_read
		extern __errno_location

ft_read:
			xor rax, rax
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