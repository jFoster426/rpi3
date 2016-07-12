#ifndef memory_c
#define memory_c

void __attribute__ ((noinline)) put32(unsigned int a, unsigned int b) {
	asm volatile("str w1,[x0]");
}
unsigned int __attribute__ ((noinline)) get32(unsigned int a) {
	asm volatile("ldr w0,[x0]");
}

void __attribute__ ((noinline)) put8(unsigned int a, unsigned char b) {
	asm volatile("uxtb w1, w1");
	asm volatile("uxtw x0, w0");
	asm volatile("strb w1, [x0]");
}
unsigned char __attribute__ ((noinline)) get8(unsigned int a) {
	asm volatile("uxtw x0, w0");
	asm volatile("ldrb w0, [x0]");
}

#endif
