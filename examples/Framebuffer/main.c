#include <RaspberryPi.h>
#include <console.c>
#include <uart.c>

int c0_main(void) {
	uart_init(115200);
	while(uart_recv() != 'V');

	console_init(100, 40);
	console_puts("Hello, World!\n", 0xFFFFFF);
	while(1);
}
