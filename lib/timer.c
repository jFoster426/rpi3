#ifndef timer_c
#define timer_c

// Timer "ARM Side"

#include "memory.c"

unsigned int FRC_timer_init(unsigned int FRC_prediv) {
	FRC_prediv <<= 16;
	FRC_prediv |= (1 << 9);
	unsigned int old_timer = get32(T_CONTROL);
	FRC_prediv |= (old_timer & 0xffff);
	put32(T_CONTROL, FRC_prediv);
	return SYS_CLOCK / ((FRC_prediv >> 16) + 1);
}

unsigned int FRC_timer_get() {
	return get32(T_CNT);
}

void FRC_timer_rst() {
	put32(T_CNT, 0xFFFFFFFF); // timer counts down
}

#endif
