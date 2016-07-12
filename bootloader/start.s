.globl _start
_start:
	mrs x0,mpidr_el1
	mov x1,#0xFF000000
	bic x0,x0,x1
	cbz x0,core_0
	sub x1,x0,#1
	cbz x1,core_1
	sub x1,x0,#2
	cbz x1,core_2
	sub x1,x0,#3
	cbz x1,core_3
hang:
	b hang
core_0:
	mrs x0,mpidr_el1
	mov x1,#0x40000
	str w0,[x1]
	mov sp,#0x3F000000
	b boot_c0
core_1:
	mrs x0,mpidr_el1
	mov x1,#0x10000
	str w0,[x1]
	mov x0,#0x3F000000
	sub x0,x0,#0x1000
	mov sp,x0
	b boot_c1
core_2:
	mrs x0,mpidr_el1
	mov x1,#0x20000
	str w0,[x1]
	mov x0,#0x3F000000
	sub x0,x0,#0x2000
	mov sp,x0
	b boot_c2
core_3:
	mrs x0,mpidr_el1
	mov x1,#0x30000
	str w0,[x1]
	mov x0,#0x3F000000
	sub x0,x0,#0x3000
	mov sp,x0
	b boot_c3
.globl BRANCHTO
BRANCHTO:
	mov w30,w0
	ret
