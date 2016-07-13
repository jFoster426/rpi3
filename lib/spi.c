#ifndef spi_c
#define spi_c

#include "memory.c"
#include "gpio.c"

unsigned int spi_init(unsigned int cdiv, unsigned int cspins) {
	unsigned int spi;
	spi = get32(AUX_ENABLES);
	put32(AUX_ENABLES, spi | 2);
	if(cspins | 1) {
		gpio_fsel(GP7, ALT0);
	}
	if(cspins | 2) {
		gpio_fsel(GP8, ALT0);
	}
	gpio_fsel(GP9, ALT0);
	gpio_fsel(GP10, ALT0);
	gpio_fsel(GP11, ALT0);
	put32(AUX_SPI0_CS, 0x0000030);
	put32(AUX_SPI0_CLK, cdiv);

	return SYS_CLOCK / cdiv;
}

unsigned char spi_transfer8(unsigned char data, unsigned char cs) {
	put32(AUX_SPI0_CS, 0x000000B0 | cs);
	while (1) {
		if (get32(AUX_SPI0_CS) & (1 << 18)) {
			break;
		}
	}
	put8(AUX_SPI0_FIFO, data);
	while (1) {
		if (get32(AUX_SPI0_CS) & (1 << 16)) {
			break;
		}
	}
	data = get8(AUX_SPI0_FIFO);
	put32(AUX_SPI0_CS, 0x00000000);
	return data;
}

unsigned int spi_transfer16(unsigned int data, unsigned char cs) {
	unsigned char l = data & 0xFF;
	unsigned char h = (data & 0xFF00) >> 8;
	put32(AUX_SPI0_CS, 0x000000B0 | cs);
	while (1) {
		if (get32(AUX_SPI0_CS) & (1 << 18)) {
			break;
		}
	}
	put8(AUX_SPI0_FIFO, h);
	while (1) {
		if (get32(AUX_SPI0_CS) & (1 << 16)) {
			break;
		}
	}
	h = get8(AUX_SPI0_FIFO);
	while (1) {
		if (get32(AUX_SPI0_CS) & (1 << 18)) {
			break;
		}
	}
	put8(AUX_SPI0_FIFO, l);
	while (1) {
		if (get32(AUX_SPI0_CS) & (1 << 16)) {
			break;
		}
	}
	l = get8(AUX_SPI0_FIFO);
	put32(AUX_SPI0_CS, 0x00000000 | cs);
	return (h << 8) | l;
}

#endif
