#include <RaspberryPi.h>

short real[N_WAVE];
short imag[N_WAVE];
short samp;

unsigned long int sqroot(long int value) {
    if(value == 0)
        return 0;
    unsigned root = 0;
    unsigned _bit;
    for(_bit = 0x4000; _bit > 0; _bit >>= 2) {
        unsigned trial = root + _bit;
        root >>= 1;
        if(trial <= value) {
            root += _bit;
            value -= trial;
        }
    }
    return root;
}

int c3_main(void) {
	while(1);
}

int c2_main(void) {
	while(1);
}

int c1_main(void) {
	while(1);
}

int c0_main(void) {
	while(1);
}
