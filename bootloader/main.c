#define CHECKSUM_VAR 0x06

#include <RaspberryPi.h>

void __attribute__ ((noinline)) put32(unsigned int a, unsigned int b) {
	asm volatile("str w1,[x0]");
}
unsigned int __attribute__ ((noinline)) get32(unsigned int a) {
	asm volatile("ldr w0,[x0]");
}

unsigned char uart_recv(void) {
	while (1) {
		if (get32(AUX_MU_LSR_REG) & 0x01) {
			break;
		}
	}
	return (get32(AUX_MU_IO_REG) & 0xFF);
}

unsigned char uart_check(void) {
	if (get32(AUX_MU_LSR_REG) & 0x01) return (1);
	return (0);
}

void uart_putc(char c) {
	while (1) {
		if (get32(AUX_MU_LSR_REG) & 0x20) {
			break;
		}
	}
	put32(AUX_MU_IO_REG, c);
}

void boot_c0() {
	unsigned char data[6], checksum;
	unsigned int addr = 0x800 /*start at bootstrap user code*/, val, i;
	// *** uart init *** //
	put32(AUX_ENABLES, 1);
	put32(AUX_MU_IER_REG, 0);
	put32(AUX_MU_CNTL_REG, 0);
	put32(AUX_MU_LCR_REG, 3);
	put32(AUX_MU_MCR_REG, 0);
	put32(AUX_MU_IER_REG, 0);
	put32(AUX_MU_IIR_REG, 0xC6);
	put32(AUX_MU_BAUD_REG, 433); // 115200 baud
	i = get32(GPFSEL1);
	i &= ~(0b111 << 12);
	i |= (ALT5 << 12);
	put32(GPFSEL1, i);
	i = get32(GPFSEL1);
	i &= ~(0b111 << 15);
	i |= (ALT5 << 15);
	put32(GPFSEL1, i);
	put32(GPPUD, 0);
	for (i = 0; i < 150; i++)
	asm volatile("Nop");
	put32(GPPUDCLK0, (1 << 14) | (1 << 15));
	for (i = 0; i < 150; i++)
	asm volatile("Nop");
	put32(GPPUDCLK0, 0);
	put32(AUX_MU_CNTL_REG, 3);
	// ***************** //
	while (1) {
		while (!uart_check());
		if (uart_recv() == '\n')
		break;
	}
	uart_putc('$');
	while (1) {
		for (i = 0; i < 6; i++) {
			while (!uart_check());
			data[i] = uart_recv();
		}
		checksum = (data[0] + data[1] + data[2] + data[3]) / CHECKSUM_VAR;
		val = (data[3] << 24) + (data[2] << 16) + (data[1] << 8) + data[0];
		if (data[4] != checksum || data[5] != '\n')
		if (val == 0x00 && data[4] == 0xff) {
			uart_putc('R');
			uart_putc('\n');
			BRANCHTO(0x1000); // branch to main code, not IRQ code
			while(1);
		}
		else
		uart_putc('!');
		else {
			put32(addr, val);
			uart_putc('A');
			addr += 4;
		}
	}
}

void boot_c1() {
	while(1) {
		unsigned int x = get32(0x504);
		if(x != 0) BRANCHTO(x);
	}
}

void boot_c2() {
	while(1) {
		unsigned int x = get32(0x508);
		if(x != 0) BRANCHTO(x);
	}
}

void boot_c3() {
	while(1) {
		unsigned int x = get32(0x50C);
		if(x != 0) BRANCHTO(x);
	}
}
