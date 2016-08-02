#ifndef mailbox_c
#define mailbox_c

static volatile unsigned int *MAILBOX0READ = (unsigned int *) 0x3f00b880;
static volatile unsigned int *MAILBOX0STATUS = (unsigned int *) 0x3f00b898;
static volatile unsigned int *MAILBOX0WRITE = (unsigned int *) 0x3f00b8a0;

#define MAILBOX_FULL 0x80000000
#define MAILBOX_EMPTY 0x40000000

unsigned int mailbox0_read(unsigned int channel) {
  unsigned int count = 0;
  unsigned int data;
	while (1) {
		while (*MAILBOX0STATUS & MAILBOX_EMPTY) {
			if (count++ > (1 << 25)) {
				return 0xffffffff;
			}
		}
		asm volatile("DMB ISHST");
		data = *MAILBOX0READ;
		asm volatile("DMB ISHST");
		if ((data & 15) == channel)
			return data & 0xfffffff0;
	}
	return 0;
}

void mailbox0_write(unsigned int channel, unsigned int data) {
	while (*MAILBOX0STATUS & MAILBOX_FULL);
	asm volatile("DMB ISHST");
	data &= 0xfffffff0;
	*MAILBOX0WRITE = (data | channel);
}

#endif
