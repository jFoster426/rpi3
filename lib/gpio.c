#ifndef gpio_c
#define gpio_c

#include "memory.c"

void gpio_fsel(unsigned char pin, unsigned char mode) {
  volatile unsigned int gp;
  if (pin >= 50) {
    gp = get32(GPFSEL5);
    gp &= ~(0b111 << ((pin - 50) * 3));
    gp |= mode << ((pin - 50) * 3);
    put32(GPFSEL5, gp);
  }
  else if (pin >= 40) {
    gp = get32(GPFSEL4);
    gp &= ~(0b111 << ((pin - 40) * 3));
    gp |= mode << ((pin - 40) * 3);
    put32(GPFSEL4, gp);
  }
  else if (pin >= 30) {
    gp = get32(GPFSEL3);
    gp &= ~(0b111 << ((pin - 30) * 3));
    gp |= mode << ((pin - 30) * 3);
    put32(GPFSEL3, gp);
  }
  else if (pin >= 20) {
    gp = get32(GPFSEL2);
    gp &= ~(0b111 << ((pin - 20) * 3));
    gp |= mode << ((pin - 20) * 3);
    put32(GPFSEL2, gp);
  }
  else if (pin >= 10) {
    gp = get32(GPFSEL1);
    gp &= ~(0b111 << ((pin - 10) * 3));
    gp |= mode << ((pin - 10) * 3);
    put32(GPFSEL1, gp);
  }
  else {
    gp = get32(GPFSEL0);
    gp &= ~(0b111 << (pin * 3));
    gp |= mode << (pin * 3);
    put32(GPFSEL0, gp);
  }
}

void gpio_write(unsigned char pin, unsigned char state) {
  volatile unsigned int gp;
  if (pin >= 32) {
    if (state == HIGH) {
      gp = get32(GPSET1);
      gp |= 1 << (pin - 32);
      put32(GPSET1, gp);
    }
    else {
      gp = get32(GPCLR1);
      gp |= 1 << (pin - 32);
      put32(GPCLR1, gp);
    }
  }
  else {
    if (state == HIGH) {
      gp = get32(GPSET0);
      gp |= 1 << pin;
      put32(GPSET0, gp);
    }
    else {
      gp = get32(GPCLR0);
      gp |= 1 << pin;
      put32(GPCLR0, gp);
    }
  }
}

unsigned char gpio_read(unsigned char pin) {
  volatile unsigned int gp;
  if (pin >= 32) {
    gp = get32(GPLEV1);
    gp &= (1 << (pin - 32));
    if (gp) {
      return HIGH;
    }
    else {
      return LOW;
    }
  }
  else {
    gp = get32(GPLEV0);
    gp &= (1 << pin);
    if (gp) {
      return HIGH;
    }
    else {
      return LOW;
    }
  }
}

#endif
