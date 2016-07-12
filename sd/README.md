To run any of the examples in this repository, you'll need to use these files. Simply copy-paste them onto a clean, formatted SD card.

For the Raspberry Pi 3, config.txt is mandatory in order to run 64 bit kernels. These are lines that are required inside config.txt, and why they're needed:

<code>arm_control=0x200</code>  
Bit 9 of arm_control needs to be set to allow 64 bit execution of the Raspberry Pi 3.  
<code>kernel_old=1</code>  
Set this bit to load kernel7.img into address 0x0000, not 0x8000 on previous Raspberry Pi boards.  
<code>disable_commandline_tags=1</code>  
Stops 'start.elf' from filling in ATAGS (memory from 0x100) before launching the kernel.  

More information about the different options available for config.txt here:  
<url>http://elinux.org/images/c/ca/Raspi_documented_config.txt,</url>
