This is the serial bootloader for the Raspberry Pi 3. It is designed to receive information over the serial port and store it in RAM. It's used in conjunction with a program running on your PC, which reads the kernel7.img file and transfers it over the serial connection. At startup, the Pi opens the UART at 57600 baud and waits for an incoming char. After receiving a valid char, the Pi then responds with a "$", indicating it is ready to recieve the new program. 4 bytes from the host computer are sent, along with a checksum variable and a newline char. Once the Raspberry Pi has received 6 characters, it prints "A" for "acknowledged", or "!" for "error". The transfer process is described as follows:

Computer			Raspberry Pi  
		start upload  
	TX	---"\n"--->		RX  
	RX	<---"$"----		TX  
		repeat:  
	TX	--"data0"->		RX  
	TX	--"data1"->		RX  
	TX	--"data2"->		RX  
	TX	--"data3"->		RX  
	TX	-"chksum"->		RX  
	TX	---"\n"--->		RX  
	RX	<-"A"/"!"--		TX  
		end of file:  
	TX	--"0x00"-->		RX  
	TX	--"0x00"-->		RX  
	TX	--"0x00"-->		RX  
	TX	--"0x00"-->		RX  
	TX	--"0xff"-->		RX  
	TX	---"\n"--->		RX  
	RX  <---"R"----		TX  
		upload complete  
		
At the end of the upload process, 0x00 is sent with a checksum var of 0xff. If 0x00000000 were a valid programming instruction, the checksum 0xff would be incorrect and therefore not go through into RAM. When the Raspberry Pi sees this specific "error", instead of priting a "!", it jumps to the origin of the new program after printing an "R" to the serial terminal.

*Note that if the new bootloader program initializes the serial terminal immediately, the "R" character might not be sent, and so the PC will return the error "Raspberry Pi still in bootloader mode". Creating a small delay in the start of your program will fix this issue for now, until I work on a fix for it inside the bootloader code.
