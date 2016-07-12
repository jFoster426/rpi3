#define RPI3

#include <RaspberryPi.h>
#include <multicore.c>
#include <uart.c>

int c3_main(void) {
	uart_puts("Hello from Core 3!\n");
	while(1);
}

int c2_main(void) {
	uart_puts("Hello from Core 2!\n");
	initializeCore(CORE3, &c3_main);
	while(1);
}

int c1_main(void) {
	uart_puts("Hello from Core 1!\n");
	initializeCore(CORE2, &c2_main);
	while(1);
}

int c0_main(void) {
	uart_init(115200);
	while(uart_recv() != 'V');
	uart_puts("Hello from Core 0!\n");
	initializeCore(CORE1, &c1_main);
	while(1);
}
