
ARMGNU ?= aarch64-linux-gnu

COPS = -Wall -Os -nostdlib -nostartfiles -ffreestanding -I "../lib"

all : clean gcc

clean :
	rm -f *.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf
	rm -f *.list
	rm -f *.img
	rm -f *.bc
	rm -f *.clang.s

gcc : kernel7.img

start.o : start.s
	$(ARMGNU)-as start.s -o start.o

main.o : main.c
	$(ARMGNU)-gcc $(COPS) -c main.c -o main.o

vectors.o : vectors.s
	$(ARMGNU)-as vectors.s -o vectors.o

kernel7.img : memmap start.o vectors.o main.o
	$(ARMGNU)-ld start.o main.o vectors.o -T memmap -o main.elf
	$(ARMGNU)-objdump -D main.elf > main.list
	$(ARMGNU)-objcopy main.elf -O ihex main.hex
	$(ARMGNU)-objcopy main.elf -O binary kernel7.img
