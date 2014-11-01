	.file	1 "start.c"
	.text
	.align	1
	.globl	_start
_start:
	li	 $sp, 20480			# 0x5000
    lda  $at, 128
    sub  $sp, $sp, -128
	la	 $gp, _gp
	jal	 main
	nop
	jal	 _exit
	nop
	.end _start
