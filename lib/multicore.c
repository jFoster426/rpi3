#ifndef multicore_c
#define multicore_c

#include "memory.c"

#define CORE0	0x500
#define CORE1	0x504
#define CORE2	0x508
#define CORE3	0x5A0

char initializeCore(unsigned int c, unsigned int(*a)()) {
	if (c != CORE1 && c != CORE2 && c != CORE3) return 1;
	put32(c, a);
	return 0;
}

#endif
