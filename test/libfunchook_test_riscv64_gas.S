	.file	"libfunchook_test_riscv64_gas.S"
	.text
	.align	1

call_get_val_in_dll:
	.globl	call_get_val_in_dll
	.type	call_get_val_in_dll, @function
	addi	sp,sp,-16
	sd	ra,8(sp)
	sd	s0,0(sp)
	addi	s0,sp,16
	call	get_val_in_dll@plt
	mv	a5,a0
	mv	a0,a5
	ld	ra,8(sp)
	ld	s0,0(sp)
	addi	sp,sp,16
	jr	ra

jump_get_val_in_dll:
	.globl	jump_get_val_in_dll
	.type	jump_get_val_in_dll, @function
	addi	sp,sp,-16
	sd	ra,8(sp)
	sd	s0,0(sp)
	addi	s0,sp,16
	call	get_val_in_dll@plt
	mv	a5,a0
	mv	a0,a5
	ld	ra,8(sp)
	ld	s0,0(sp)
	addi	sp,sp,16
	jr	ra
