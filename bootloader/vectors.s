.org 0x504-0x3e8
	.word 0x00
	.word 0x00
	.word 0x00

.org 0x800-0x3b0
.globl undefined_handler
undefined_handler:
	b hang
.org 0x900-0x3b0
.globl swi_handler
swi_handler:
	b hang
.org 0xa00-0x3b0
.globl prefetch_handler
prefetch_handler:
	b hang
.org 0xb00-0x3b0
.globl data_handler
data_handler:
	b hang
.org 0xc00-0x3b0
.globl unused_handler
unused_handler:
	b hang
.org 0xd00-0x3b0
.globl irq_handler
irq_handler:
	ret
.org 0xe00-0x3b0
.globl fiq_handler
fiq_handler:
	ret
