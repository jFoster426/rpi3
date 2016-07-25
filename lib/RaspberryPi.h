/* All the system control registers are defined in RaaspberryPi.h. *
 * Just include this file before including any other library to    *
 * make sure it'll work on your specific Pi.                       */

#define PBASE			0x3F000000

#define SYS_CLOCK		250000000  // 250 MHz core_freq, note this is different from the arm_freq in comfig.txt

// ** General Defines ** //

#define AUX_ENABLES		(PBASE + 0x00215004)

// ** UART Defines ** //

#define AUX_MU_IO_REG	(PBASE + 0x00215040)
#define AUX_MU_IER_REG	(PBASE + 0x00215044)
#define AUX_MU_IIR_REG	(PBASE + 0x00215048)
#define AUX_MU_LCR_REG	(PBASE + 0x0021504C)
#define AUX_MU_MCR_REG	(PBASE + 0x00215050)
#define AUX_MU_LSR_REG	(PBASE + 0x00215054)
#define AUX_MU_MSR_REG	(PBASE + 0x00215058)
#define AUX_MU_SCRATCH	(PBASE + 0x0021505C)
#define AUX_MU_CNTL_REG	(PBASE + 0x00215060)
#define AUX_MU_STAT_REG	(PBASE + 0x00215064)
#define AUX_MU_BAUD_REG	(PBASE + 0x00215068)

// ** GPIO Defines ** //

#define GPFSEL0			(PBASE + 0x00200000)
#define GPFSEL1			(PBASE + 0x00200004)
#define GPFSEL2			(PBASE + 0x00200008)
#define GPFSEL3			(PBASE + 0x0020000C)
#define GPFSEL4			(PBASE + 0x00200010)
#define GPFSEL5			(PBASE + 0x00200014)
#define GPSET0			(PBASE + 0x0020001C)
#define GPSET1			(PBASE + 0x00200020)
#define GPCLR0			(PBASE + 0x00200028)
#define GPCLR1			(PBASE + 0x0020002C)
#define GPLEV0			(PBASE + 0x00200034)
#define GPLEV1			(PBASE + 0x00200038)
#define GPEDS0			(PBASE + 0x00200040)
#define GPEDS1			(PBASE + 0x00200044)
#define GPREN0			(PBASE + 0x0020004C)
#define GPREN1			(PBASE + 0x00200050)
#define GPFEN0			(PBASE + 0x00200058)
#define GPFEN1			(PBASE + 0x0020005C)
#define GPHEN0			(PBASE + 0x00200064)
#define GPHEN1			(PBASE + 0x00200068)
#define GPLEN0			(PBASE + 0x00200070)
#define GPLEN1			(PBASE + 0x00200074)
#define GPAREN0			(PBASE + 0x0020007C)
#define GPAREN1			(PBASE + 0x00200080)
#define GPAFEN0			(PBASE + 0x00200088)
#define GPAFEN1			(PBASE + 0x0020008C)
#define GPPUD			(PBASE + 0x00200094)
#define GPPUDCLK0		(PBASE + 0x00200098)
#define GPPUDCLK1		(PBASE + 0x0020009C)

#define INPUT			0b000
#define OUTPUT			0b001
#define ALT0			0b100
#define ALT1			0b101
#define ALT2			0b110
#define ALT3			0b111
#define ALT4			0b011
#define ALT5			0b010
#define HIGH			1
#define LOW				0
#define P_OFF			0b00
#define PULLDOWN		0b01
#define PULLUP			0b10

// ** SPI Defines ** //

#define AUX_SPI0_CS		(PBASE + 0x00204000)
#define AUX_SPI0_FIFO	(PBASE + 0x00204004)
#define AUX_SPI0_CLK	(PBASE + 0x00204008)
#define AUX_SPI0_DLEN	(PBASE + 0x0020400C)
#define AUX_SPI0_LTOH	(PBASE + 0x00204010)
#define AUX_SPI0_DC		(PBASE + 0x00204014)

#define CS0				1
#define CS1				2
#define NO_CS			0

// ** TIMER Defines ** //

#define T_LOAD			(PBASE + 0x0000B400)
#define T_VALUE			(PBASE + 0x0000B404)
#define T_CONTROL		(PBASE + 0x0000B408)
#define T_IRQCLR		(PBASE + 0x0000B40C)
#define T_IRQRAW		(PBASE + 0x0000B410)
#define T_IRQMASK		(PBASE + 0x0000B414)
#define T_RELOAD		(PBASE + 0x0000B418)
#define T_PREDIV		(PBASE + 0x0000B41C)
#define T_CNT			(PBASE + 0x0000B420)
