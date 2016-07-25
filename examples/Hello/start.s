.org 0x00
	b hang // undefined handler
.org 0x100
	b hang // swi handler
.org 0x200
	b hang // prefetch handler
.org 0x300
	b hang // data handler
.org 0x400
	b hang // unused handler
.org 0x500
	b hang // irq handler
.org 0x600
	b hang // fiq handler
.org 0x800
.globl _start
_start:
	bl c0_main // user code
hang:
	b hang
