#ifndef uart_c
#define uart_c

#include "memory.c"
#include "gpio.c"

unsigned char uart_read(void) {
	while (get32(AUX_MU_LSR_REG) & 1 == 0);
	return (get32(AUX_MU_IO_REG) & 0xff);
}

unsigned char uart_check(void) {
	if (get32(AUX_MU_LSR_REG) & 0x01) return 1;
	return 0;
}

void uart_putc(unsigned char c) {
	while (get32(AUX_MU_LSR_REG) & 0x20 == 0);
	put32(AUX_MU_IO_REG, c & 0xff);
}

void uart_puts(unsigned char *s) {
	while (*s != '\0') {
		uart_putc(*s++);
	}
}

void uart_flush(void) {
	while (get32(AUX_MU_LSR_REG) & 0x100);
}

void uart_puthex(unsigned int d) {
	unsigned int rb = 32, rc;
	while (1) {
		rb -= 4;
		rc = (d >> rb) & 0xf;
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
	for (i = 31; i >= 0; i--) {
		b = ((d >> i) & 1) + 48;
		uart_putc(b);
	}
}

void uart_putdec(unsigned int val) {
	unsigned int tmp, val2 = val;
	signed char ts = 0, i = 0;
	tmp = val2;
	while(tmp > 10) {
		tmp /= 10;
		ts++;
	}
	while(ts >= 0) {
		tmp = val2;
		while(i < ts) {
			tmp /= 10;
			i++;
		}
		uart_putc(tmp + 48);
		while(i > 0) {
			tmp *= 10;
			i--;
		}
		val2 = val2 - tmp;
		ts--;
	}
}

void uart_init(unsigned int baud) {
	baud = ((SYS_CLOCK / baud) / 8) - 1;
	put32(AUX_ENABLES, 1);
	put32(AUX_MU_IER_REG, 0);
	put32(AUX_MU_CNTL_REG, 0);
	put32(AUX_MU_LCR_REG, 3);
	put32(AUX_MU_MCR_REG, 0);
	put32(AUX_MU_IER_REG, 0);
	put32(AUX_MU_IIR_REG, 0xc6);
	put32(AUX_MU_BAUD_REG, baud);
	gpio_fsel(14, ALT5);
	gpio_fsel(15, ALT5);
	gpio_pullx(14, P_OFF);
	gpio_pullx(15, P_OFF);
	put32(AUX_MU_CNTL_REG, 3);
}

#endif
