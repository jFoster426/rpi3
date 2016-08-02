/* All the system control registers are defined in RaaspberryPi.h. *
 * Just include this file before including any other library to    *
 * make sure it'll work on your specific Pi.                       */

#ifndef RaspberryPi_h
#define RaspberryPi_h

#define PBASE					0x3F000000

#define SYS_CLOCK				250000000  // 250 MHz core_freq, note this is different from the arm_freq in comfig.txt

// ** General Defines ** //

#define AUX_ENABLES				(PBASE + 0x00215004)

// ** UART Defines ** //

#define AUX_MU_IO_REG			(PBASE + 0x00215040)
#define AUX_MU_IER_REG			(PBASE + 0x00215044)
#define AUX_MU_IIR_REG			(PBASE + 0x00215048)
#define AUX_MU_LCR_REG			(PBASE + 0x0021504C)
#define AUX_MU_MCR_REG			(PBASE + 0x00215050)
#define AUX_MU_LSR_REG			(PBASE + 0x00215054)
#define AUX_MU_MSR_REG			(PBASE + 0x00215058)
#define AUX_MU_SCRATCH			(PBASE + 0x0021505C)
#define AUX_MU_CNTL_REG			(PBASE + 0x00215060)
#define AUX_MU_STAT_REG			(PBASE + 0x00215064)
#define AUX_MU_BAUD_REG			(PBASE + 0x00215068)

// ** GPIO Defines ** //

#define GPFSEL0					(PBASE + 0x00200000)
#define GPFSEL1					(PBASE + 0x00200004)
#define GPFSEL2					(PBASE + 0x00200008)
#define GPFSEL3					(PBASE + 0x0020000C)
#define GPFSEL4					(PBASE + 0x00200010)
#define GPFSEL5					(PBASE + 0x00200014)
#define GPSET0					(PBASE + 0x0020001C)
#define GPSET1					(PBASE + 0x00200020)
#define GPCLR0					(PBASE + 0x00200028)
#define GPCLR1					(PBASE + 0x0020002C)
#define GPLEV0					(PBASE + 0x00200034)
#define GPLEV1					(PBASE + 0x00200038)
#define GPEDS0					(PBASE + 0x00200040)
#define GPEDS1					(PBASE + 0x00200044)
#define GPREN0					(PBASE + 0x0020004C)
#define GPREN1					(PBASE + 0x00200050)
#define GPFEN0					(PBASE + 0x00200058)
#define GPFEN1					(PBASE + 0x0020005C)
#define GPHEN0					(PBASE + 0x00200064)
#define GPHEN1					(PBASE + 0x00200068)
#define GPLEN0					(PBASE + 0x00200070)
#define GPLEN1					(PBASE + 0x00200074)
#define GPAREN0					(PBASE + 0x0020007C)
#define GPAREN1					(PBASE + 0x00200080)
#define GPAFEN0					(PBASE + 0x00200088)
#define GPAFEN1					(PBASE + 0x0020008C)
#define GPPUD					(PBASE + 0x00200094)
#define GPPUDCLK0				(PBASE + 0x00200098)
#define GPPUDCLK1				(PBASE + 0x0020009C)

#define INPUT					0b000
#define OUTPUT					0b001
#define ALT0					0b100
#define ALT1					0b101
#define ALT2					0b110
#define ALT3					0b111
#define ALT4					0b011
#define ALT5					0b010
#define HIGH					1
#define LOW						0
#define P_OFF					0b00
#define PULLDOWN				0b01
#define PULLUP					0b10

// ** SPI Defines ** //

#define AUX_SPI0_CS				(PBASE + 0x00204000)
#define AUX_SPI0_FIFO			(PBASE + 0x00204004)
#define AUX_SPI0_CLK			(PBASE + 0x00204008)
#define AUX_SPI0_DLEN			(PBASE + 0x0020400C)
#define AUX_SPI0_LTOH			(PBASE + 0x00204010)
#define AUX_SPI0_DC				(PBASE + 0x00204014)

#define CS0						1
#define CS1						2
#define NO_CS					0

// ** TIMER Defines ** //

#define T_LOAD					(PBASE + 0x0000B400)
#define T_VALUE					(PBASE + 0x0000B404)
#define T_CONTROL				(PBASE + 0x0000B408)
#define T_IRQCLR				(PBASE + 0x0000B40C)
#define T_IRQRAW				(PBASE + 0x0000B410)
#define T_IRQMASK				(PBASE + 0x0000B414)
#define T_RELOAD				(PBASE + 0x0000B418)
#define T_PREDIV				(PBASE + 0x0000B41C)
#define T_CNT					(PBASE + 0x0000B420)

// ** GPU Mailbox Defines ** //

#define TAG_FIRMWARE_VERSION	0x1

#define TAG_BOARD_MODEL			0x10001
#define TAG_BOARD_REVISION		0x10002
#define TAG_BOARD_MAC_ADDRESS	0x10003
#define TAG_BOARD_SERIAL		0x10004
#define TAG_ARM_MEMORY			0x10005
#define TAG_VC_MEMORY			0x10006
#define TAG_CLOCKS				0x10007

#define TAG_COMMAND_LINE		0x50001

#define TAG_DMA_CHANNELS		0x60001

#define TAG_POWER_STATE			0x20001
#define TAG_TIMING				0x20002

#define TAG_CLOCK_STATE			0x30001
#define TAG_CLOCK_RATE			0x30002
#define TAG_MAX_CLOCK_RATE		0x30004
#define TAG_MIN_CLOCK_RATE		0x30007
#define TAG_GET_TURBO			0x30009
#define TAG_SET_TURBO			0x38009

#define TAG_VOLTAGE				0x38003
#define TAG_MAX_VOLTAGE			0x30005
#define TAG_MIN_VOLTAGE			0x30008
#define TAG_TEMPERATURE			0x30006
#define TAG_MAX_TEMPERATURE		0x3000A
#define TAG_ALLOCATE_MEMORY		0x3000C
#define TAG_LOCK_MEMORY			0x3000D
#define TAG_UNLOCK_MEMORY		0x3000E
#define TAG_RELEASE_MEMORY		0x3000F
#define TAG_EXECUTE_CODE		0x30010
#define TAG_DISPMANX_MEM_HANDLE	0x30014
#define TAG_EDID_BLOCK			0x30020

#define TAG_ALLOCATE_BUFFER		0x40001
#define TAG_RELEASE_BUFFER		0x48001
#define TAG_BLANK_SCREEN		0x40002
#define TAG_GET_PHYSICAL_SIZE	0x40003
#define TAG_TEST_PHYSICAL_SIZE	0x44003
#define TAG_SET_PHYSICAL_SIZE	0x48003
#define TAG_GET_VIRTUAL_SIZE	0x40004
#define TAG_TEST_VIRTUAL_SIZE	0x44004
#define TAG_SET_VIRTUAL_SIZE	0x48004
#define TAG_GET_DEPTH			0x40005
#define TAG_TEST_DEPTH			0x44005
#define TAG_SET_DEPTH			0x48005
#define TAG_GET_PIXEL_ORDER		0x40006
#define TAG_TEST_PIXEL_ORDER	0x44006
#define TAG_SET_PIXEL_ORDER		0x48006
#define TAG_GET_ALPHA_MODE		0x40007
#define TAG_TEST_ALPHA_MODE		0x44007
#define TAG_SET_ALPHA_MODE		0x48007
#define TAG_PITCH				0x40008
#define TAG_GET_VIRTUAL_OFFSET	0x40009
#define TAG_TEST_VIRTUAL_OFFSET	0x44009
#define TAG_SET_VIRTUAL_OFFSET	0x48009
#define TAG_GET_OVERSCAN		0x4000A
#define TAG_TEST_OVERSCAN		0x4400A
#define TAG_SET_OVERSCAN		0x4800A
#define TAG_GET_PALETTE			0x4000B
#define TAG_TEST_PALETTE		0x4400B
#define TAG_SET_PALETTE			0x4800B
#define TAG_CURSOR_INFO			0x8011
#define TAG_CURSOR_STATE		0x8010

#endif
