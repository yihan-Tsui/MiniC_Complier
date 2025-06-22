.text
.globl _main
_main:
	stp x29, x30, [sp, #-16]!   // push FP, LR
	mov x29, sp
	sub sp, sp, #80
	mov w9, #0
	str w9, [x29, #-24]
	ldr w9, [x29, #-24]
	str w9, [x29, #-8]
	mov w9, #0
	str w9, [x29, #-32]
	ldr w9, [x29, #-32]
	str w9, [x29, #-16]
L1:
	mov w9, #4
	str w9, [x29, #-40]
	ldr w9, [x29, #-16]
	mov w10, w9
	ldr w9, [x29, #-40]
	mov w11, w9
	cmp w10, w11
	cset w9, lt
	str w9, [x29, #-48]
	ldr w9, [x29, #-48]
	cmp w9, #0
	beq L3
	ldr w9, [x29, #-8]
	mov w10, w9
	ldr w9, [x29, #-16]
	mov w11, w9
	add w9, w10, w11
	str w9, [x29, #-56]
	ldr w9, [x29, #-56]
	str w9, [x29, #-8]
L2:
	mov w9, #1
	str w9, [x29, #-64]
	ldr w9, [x29, #-16]
	mov w10, w9
	ldr w9, [x29, #-64]
	mov w11, w9
	add w9, w10, w11
	str w9, [x29, #-72]
	ldr w9, [x29, #-72]
	str w9, [x29, #-16]
	b L1
L3:
	ldr w9, [x29, #-8]
	mov w0, w9
	add sp, sp, #80
	ldp x29, x30, [sp], #16   // pop FP, LR
	ret
