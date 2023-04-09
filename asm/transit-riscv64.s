# transit code for riscv64
	.text
transit:
	# save registers
	addi sp, sp, -16*8
	sd ra, 0(sp)
	sd x8, 1*8(sp)
	sd x9, 2*8(sp)
	sd x10, 3*8(sp)
	sd x11, 4*8(sp)
	sd x12, 5*8(sp)
	sd x13, 6*8(sp)
	sd x14, 7*8(sp)
	sd x15, 8*8(sp)
	sd x16, 9*8(sp)
	sd x17, 10*8(sp)
	sd x18, 11*8(sp)
	sd x19, 12*8(sp)
	# 1st arg: the start address of transit
	la a0, transit
	# 2nd arg: stack pointer at the beginning of transit
	addi a1, sp, 16*8
	# call funchook_hook_caller
	la t1, hook_caller_addr
	jalr ra, t1, 0
	# restore registers
	ld ra, 0(sp)
	ld x8, 1*8(sp)
	ld x9, 2*8(sp)
	ld x10, 3*8(sp)
	ld x11, 4*8(sp)
	ld x12, 5*8(sp)
	ld x13, 6*8(sp)
	ld x14, 7*8(sp)
	ld x15, 8*8(sp)
	ld x16, 9*8(sp)
	ld x17, 10*8(sp)
	ld x18, 11*8(sp)
	ld x19, 12*8(sp)
	addi sp, sp, 16*8
	# jump to hook_func
	la t1, hook_func_addr
	jr t1

hook_caller_addr:
	# dummy bytes to be replaced with absolute address of funchook_hook_caller function.
	nop
	nop
hook_func_addr:
	# dummy bytes to be replaced with absolute address of funchook_hook_caller function.
	nop
	nop
