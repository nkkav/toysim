#
# Filename: fibo.asm
# Purpose : N-address code (NAC) implementation for the iterative version of 
#           Fibonacci series computation.
# Author  : Nikolaos Kavvadias (C) 2009, 2010, 2011, 2012, 2013, 2014
# Date    : 17-Sep-2009
# Revision: 0.2.0 (17/09/09)
#           Initial version.
# 
# at = R[1]
# n = R[2]
# x = R[3]
# f0 = R[4]
# f1 = R[5]
# res = R[6]
# k = R[7]
# f = R[8]
# outp = R[9]
#  .data
#  .align  0
  .text
  .align  2
  .globl  main
main:  
L_16:
  load r2, 255
  move r3, r2
  lda r4, 0
  lda r5, 1
  move r6, r4
  jz r3, L_35
L_22:
  move r6, r5
  lda r1, 1
  sub r1, r3, r1
  jz r1, L_35
L_26:
  lda r7, 1
L_27:
  lda r1, 1
  add r7, r7, r1
  add r8, r5, r4
  move r4, r5
  move r5, r8
  move r6, r8
  sub r1, r3, r7
  jp r1, L_27
L_35:
  move r9, r6
  store r9, 255
  nop
  nop
  nop
  halt
  nop
