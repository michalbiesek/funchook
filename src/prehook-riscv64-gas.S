	.text
	.globl	funchook_hook_caller_asm
	.type	funchook_hook_caller_asm, @function
funchook_hook_caller_asm:
	// save frame pointer (s0) and link register (ra).
	addi sp, sp, -16*8
	sd s0, 0(sp)
	sd ra, 8(sp)
	// set frame pointer
	addi s0, sp, 16*8
	// save integer or pointer arguments passed in registers.
	sd a0, 0(s0)
	sd a1, 8(s0)
	sd a2, 16(s0)
	sd a3, 24(s0)
	sd a4, 32(s0)
	sd a5, 40(s0)
	// save indirect return value address and platform register.
	sd a6, 48(s0)
	sd t0, 56(s0)
	// save floating-point registers used as arguments.
	fsd ft0, 64(s0)
	fsd ft1, 72(s0)
	fsd ft2, 80(s0)
	fsd ft3, 88(s0)
	fsd ft4, 96(s0)
	fsd ft5, 104(s0)
	// 1st arg: the start address of transit. Note: a4 is set by transit.
	mv a0, a4
	// 2nd arg: frame pointer
	mv a1, s0
	// call funchook_hook_caller
	call funchook_hook_caller
	mv t0, a0
	// restore registers
	ld a0, 0(s0)
	ld a1, 8(s0)
	ld a2, 16(s0)
	ld a3, 24(s0)
	ld a4, 32(s0)
	ld a5, 40(s0)
	ld a6, 48(s0)
	ld t0, 56(s0)
	// restore floating-point registers used as arguments.
	fld ft0, 64(s0)
	fld ft1, 72(s0)
	fld ft2, 80(s0)
	fld ft3, 88(s0)
	fld ft4, 96(s0)
	fld ft5, 104(s0)
	ld s0, 0(sp)
	ld ra, 8(sp)
	addi sp, sp, 16*8
	// jump to hook_func
	jr t0