/* RaspberryPi.h                                                                                          *
* Controls which ARM chip is included in libraries based off compiler                                    *
* flags. Change this to use different Raspberry Pi's in the Makefile                                     *
* Just include this file before including any other library to make sure it'll work on your specific Pi. */

#define PBASE         0x3F000000

#define SYS_CLOCK       250000000  // 250 MHz core_freq, note this is different from the arm_freq in comfig.txt

// ** General Defines ** //

#define AUX_ENABLES     (PBASE + 0x00215004)

// ** UART Defines ** //

#define AUX_MU_IO_REG   (PBASE + 0x00215040)
#define AUX_MU_IER_REG  (PBASE + 0x00215044)
#define AUX_MU_IIR_REG  (PBASE + 0x00215048)
#define AUX_MU_LCR_REG  (PBASE + 0x0021504C)
#define AUX_MU_MCR_REG  (PBASE + 0x00215050)
#define AUX_MU_LSR_REG  (PBASE + 0x00215054)
#define AUX_MU_MSR_REG  (PBASE + 0x00215058)
#define AUX_MU_SCRATCH  (PBASE + 0x0021505C)
#define AUX_MU_CNTL_REG (PBASE + 0x00215060)
#define AUX_MU_STAT_REG (PBASE + 0x00215064)
#define AUX_MU_BAUD_REG (PBASE + 0x00215068)

// ** GPIO Defines ** //

#define GPFSEL0		(PBASE + 0x00200000)
#define GPFSEL1		(PBASE + 0x00200004)
#define GPFSEL2		(PBASE + 0x00200008)
#define GPFSEL3		(PBASE + 0x0020000C)
#define GPFSEL4		(PBASE + 0x00200010)
#define GPFSEL5		(PBASE + 0x00200014)
#define GPSET0		(PBASE + 0x0020001C)
#define GPSET1		(PBASE + 0x00200020)
#define GPCLR0		(PBASE + 0x00200028)
#define GPCLR1		(PBASE + 0x0020002C)
#define GPLEV0		(PBASE + 0x00200034)
#define GPLEV1		(PBASE + 0x00200038)
#define GPEDS0		(PBASE + 0x00200040)
#define GPEDS1		(PBASE + 0x00200044)
#define GPREN0		(PBASE + 0x0020004C)
#define GPREN1		(PBASE + 0x00200050)
#define GPFEN0		(PBASE + 0x00200058)
#define GPFEN1		(PBASE + 0x0020005C)
#define GPHEN0		(PBASE + 0x00200064)
#define GPHEN1		(PBASE + 0x00200068)
#define GPLEN0		(PBASE + 0x00200070)
#define GPLEN1		(PBASE + 0x00200074)
#define GPAREN0		(PBASE + 0x0020007C)
#define GPAREN1		(PBASE + 0x00200080)
#define GPAFEN0		(PBASE + 0x00200088)
#define GPAFEN1		(PBASE + 0x0020008C)
#define GPPUD		(PBASE + 0x00200094)
#define GPPUDCLK0	(PBASE + 0x00200098)
#define GPPUDCLK1	(PBASE + 0x0020009C)

#define INPUT		0b000
#define OUTPUT		0b001
#define ALT0		0b100
#define ALT1		0b101
#define ALT2		0b110
#define ALT3		0b111
#define ALT4		0b011
#define ALT5		0b010
#define HIGH	        1
#define LOW		0

#define GP0		0
#define GP1		1
#define GP2		2
#define GP3		3
#define GP4		4
#define GP5		5
#define GP6		6
#define GP7		7
#define GP8		8
#define GP9		9
#define GP10		10
#define GP11		11
#define GP12		12
#define GP13		13
#define GP14		14
#define GP15		15
#define GP16		16
#define GP17		17
#define GP18		18
#define GP19		19
#define GP20		20
#define GP21		21
#define GP22		22
#define GP23		23
#define GP24		24
#define GP25		25
#define GP26		26
#define GP27		27
#define GP28		28
#define GP29		29
#define GP30		30
#define GP31		31
#define GP32		32+0
#define GP33		32+1
#define GP34		32+2
#define GP35		32+3
#define GP36		32+4
#define GP37		32+5
#define GP38		32+6
#define GP39		32+7
#define GP40		32+8
#define GP41		32+9
#define GP42		32+10
#define GP43		32+11
#define GP44		32+12
#define GP45		32+13
#define GP46		32+14
#define GP47		32+15
#define GP48		32+16
#define GP49		32+17
#define GP50		32+18
#define GP51		32+19
#define GP52		32+20
#define GP53		32+21

// ** SPI Defines ** //

#define AUX_SPI0_CS     (PBASE + 0x00204000)
#define AUX_SPI0_FIFO   (PBASE + 0x00204004)
#define AUX_SPI0_CLK    (PBASE + 0x00204008)
#define AUX_SPI0_DLEN   (PBASE + 0x0020400C)
#define AUX_SPI0_LTOH   (PBASE + 0x00204010)
#define AUX_SPI0_DC     (PBASE + 0x00204014)

#define CS0		1
#define CS1		2
#define NO_CS	0


// ** TIMER Defines ** //

#define T_LOAD          (PBASE + 0x0000B400)
#define T_VALUE         (PBASE + 0x0000B404)
#define T_CONTROL       (PBASE + 0x0000B408)
#define T_IRQCLR        (PBASE + 0x0000B40C)
#define T_IRQRAW        (PBASE + 0x0000B410)
#define T_IRQMASK       (PBASE + 0x0000B414)
#define T_RELOAD        (PBASE + 0x0000B418)
#define T_PREDIV        (PBASE + 0x0000B41C)
#define T_CNT           (PBASE + 0x0000B420)
