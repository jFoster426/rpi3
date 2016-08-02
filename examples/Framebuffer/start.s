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
	mrs x0,sctlr_el3
	mov x1,0x1000  // enable instruction cache
	orr x0,x0,x1
	msr sctlr_el3,x0
    bl c0_main
hang:
	b hang
.globl debug_cache
debug_cache:
	mrs x0,sctlr_el3
	ret
