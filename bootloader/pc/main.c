/* Command line interface:
 * ./main <file>
 * <file> = file path
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "rs232.h"

#define CHECKSUM_VAR 0x06

unsigned char inByte[2] = {0, 0}, i, j;
unsigned long indx = 0;
int errorCount = 0;
unsigned char data[4];
float dataTransferSpeed = 0.00;

char ports[38][16]={"/dev/ttyS0","/dev/ttyS1","/dev/ttyS2","/dev/ttyS3","/dev/ttyS4","/dev/ttyS5",
                    "/dev/ttyS6","/dev/ttyS7","/dev/ttyS8","/dev/ttyS9","/dev/ttyS10","/dev/ttyS11",
                    "/dev/ttyS12","/dev/ttyS13","/dev/ttyS14","/dev/ttyS15","/dev/ttyUSB0",
                    "/dev/ttyUSB1","/dev/ttyUSB2","/dev/ttyUSB3","/dev/ttyUSB4","/dev/ttyUSB5",
                    "/dev/ttyAMA0","/dev/ttyAMA1","/dev/ttyACM0","/dev/ttyACM1",
                    "/dev/rfcomm0","/dev/rfcomm1","/dev/ircomm0","/dev/ircomm1",
                    "/dev/cuau0","/dev/cuau1","/dev/cuau2","/dev/cuau3",
                    "/dev/cuaU0","/dev/cuaU1","/dev/cuaU2","/dev/cuaU3"};

time_t start;

int main(int argc, char *argv[]) {
	for(i = 0; i < 25; i++) {
		if(RS232_OpenComport(i, 57600, "8N1") == 0) goto init;
		RS232_CloseComport(i);
	}
	printf("\nError opening Serial port.\n");
	return 0;
	init:
	printf("\nOpened Serial port %d (%s) succesfully.\n", i, ports[i]);
	if(argv[1] != NULL) {
		FILE *file = fopen(argv[1], "r");
		fseek(file, 0L, SEEK_END);
		unsigned long length = ftell(file);
		printf("\nFile length: %lu bytes.\n", length);
		fseek(file, 0L, 0); // start reading from beginning
		if (file == 0) {
			printf("Could not open file\n\n");
			RS232_CloseComport(i);
			fclose(file);
			return 0;
		}
		else {
			RS232_SendByte(i, '\n');
			start = clock();
			while(inByte[0] != '$') {
				RS232_PollComport(i, inByte, 1);
				if((clock() - start) / CLOCKS_PER_SEC > 2) {
					printf("\nError, Raspberry Pi did not respond.\n\n");
					RS232_CloseComport(i);
					fclose(file);
					return 0;
				}
			}
			inByte[0] = 0;
			dataTransferSpeed = clock();
			while(ftell(file) <= length - 3) {
				for(j = 0; j < 4; j++) {
					data[j] = fgetc(file) & 0xff;
					RS232_SendByte(i, data[j]);
				}
				RS232_SendByte(i, (data[0] + data[1] + data[2] + data[3]) / CHECKSUM_VAR);
				RS232_SendByte(i, '\n');
				// ****************************************************************
				start = clock();
				while(inByte[0] != 'A') {
					RS232_PollComport(i, inByte, 1);
					if(inByte[0] == '!') {
						errorCount++;
						fseek(file, 0L, indx);
						indx -= 4;
					}
					if((clock() - start) / CLOCKS_PER_SEC > 2) {
						printf("\nError, no confirmation byte.\n\n");
						RS232_CloseComport(i);
						fclose(file);
						return 0;
					}
				}
				indx += 4;
				inByte[0] = 0;
				// ****************************************************************
			}
			dataTransferSpeed = (clock() - dataTransferSpeed) / CLOCKS_PER_SEC;
			dataTransferSpeed = length / dataTransferSpeed;
			char prefix = 0;
			if(dataTransferSpeed > 1000) {
				dataTransferSpeed /= 1000;
				prefix = 'K';
			}
			for(j = 0; j < 4; j++) {
				RS232_SendByte(i, 0);
			}
			RS232_SendByte(i, 0xff);
			RS232_SendByte(i, '\n');
			start = clock();
		 	while(inByte[0] != 'R') {
				RS232_PollComport(i, inByte, 1);
				if((clock() - start) / CLOCKS_PER_SEC > 2) {
					printf("\nError, Raspberry Pi still in bootloader mode.");
					goto done;
				}
			}
			done:
			printf("\nDone uploading. %d data packet error(s).", errorCount);
			// printf("\nAverage data transfer speed: %f %cBytes per second.\n\n", dataTransferSpeed, prefix);
			RS232_CloseComport(i);
			fclose(file);
			return 0;
		}
	}
	else {
		printf("\nCan't upload nothing.\n\n");
		RS232_CloseComport(i);
		return 0;
	}
}
