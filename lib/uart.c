#ifndef uart_c
#define uart_c

#include "memory.c"
#include "gpio.c"

unsigned int uart_lcr(void) {
	return (get32(AUX_MU_LSR_REG));
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

void uart_putc(unsigned char c) {
	while (1) {
		if (get32(AUX_MU_LSR_REG) & 0x20) {
			break;
		}
	}
	put32(AUX_MU_IO_REG, c & 0xff);
}

void uart_puts(unsigned char *s) {
	while (*s != '\0') {
		uart_putc(*s++);
	}
}

void uart_flush(void) {
	while (1) {
		if ((get32(AUX_MU_LSR_REG) & 0x100) == 0) {
			break;
		}
	}
}

void uart_puthex(unsigned int d) {
	unsigned int rb = 32, rc;
	while (1) {
		rb -= 4;
		rc = (d >> rb) & 0xF;
		if (rc > 9)
		rc += 0x37;
		else
		rc += 0x30;
		uart_putc(rc);
		if (rb == 0)
		break;
	}
}

void uart_putbin(unsigned int d) {
	signed int i;
	unsigned char b;
	for(i = 31; i >= 0; i--) {
		b = ((d >> i) & 1) + 48;
		uart_putc(b);
	}
}

void uart_init(unsigned int baud) {
	baud = ((SYS_CLOCK / baud) / 8) - 1;
	unsigned int ra;
	put32(AUX_ENABLES, 1);
	put32(AUX_MU_IER_REG, 0);
	put32(AUX_MU_CNTL_REG, 0);
	put32(AUX_MU_LCR_REG, 3);
	put32(AUX_MU_MCR_REG, 0);
	put32(AUX_MU_IER_REG, 0);
	put32(AUX_MU_IIR_REG, 0xC6);
	put32(AUX_MU_BAUD_REG, baud);

	gpio_fsel(14, ALT5);
	gpio_fsel(15, ALT5);

	put32(GPPUD, 0);
	for (ra = 0; ra < 150; ra++) {
		asm volatile("Nop");
	}
	put32(GPPUDCLK0, (1 << 14) | (1 << 15));
	for (ra = 0; ra < 150; ra++) {
		asm volatile("Nop");
	}
	put32(GPPUDCLK0, 0);
	put32(AUX_MU_CNTL_REG, 3);
}

#endif
