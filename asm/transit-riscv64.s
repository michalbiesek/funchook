# transit code for riscv64
	.text
transit:
	# The address of the `transit` member in `funchook_entry_t` struct
	# is passed to funchook_hook_caller_asm via x5
	la x5, transit
	ld x6, hook_caller_addr
	jr x6

	.align 3
hook_caller_addr:
	# dummy bytes to be replaced with absolute address of funchook_hook_caller function.
	nop
	nop
