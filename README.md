# Introduction

These are bare metal projects for the Raspberry Pi 3. They are designed to be run without an OS (such as Raspbian) running in the background.

See my other repos for other board models. Keeping them separate makes the code a lot simpler.

All of the examples here (with the exception of bootloader) are designed to be uploaded using the bootloader code already on the SD Card, and connected to the host downloader application, which is also included here.

# Getting Started

To use any of the examples provided in this repository, I strongly recommend that you get an FTDI adapter cable or breakout, this one from Sparkfun will work:  
https://www.sparkfun.com/products/9873  
There are some cheaper ones on Amazon that do the same thing but make sure the one you buy is 3.3V or else it could damage your Pi.

Now the FTDI pinout is as follows:  
1  Black   GND          -> Connect to pin 6 on Raspberry Pi GPIO Header  
2  Brown   CTS          -> Not connected  
3  Red     VCC (3.3V)   -> Not connected  
4  Orange  TXD          -> Connect to pin 8 on Raspberry Pi GPIO Header  
5  Yellow  RXD          -> Connect to pin 10 on Raspberry Pi GPIO Header  
6  Green   DTR          -> Not connected 
* Note that some FTDI boards have switched RX and TX labels, experiment and make sure yours is in the right way.  
* Note that these pinouts are the same for 26 and 40 pin GPIO Headers on the Raspberry Pi 1, 2, 3.  

Once that's all nice and tidy, you'll want to make sure that there are no other idle serial devices attached to your computer while uploading new code; it can interfere with the upload process.

# Downloading Programs

So to put a program on your Raspberry Pi there are two options:

####Option 1 (Only for /bootloader)
These examples are designed to be uploaded using the bootloader code, therefore I will not be providing standalone examples (that don't use the bootloader) for each example.

Inside /bootloader, you will need to choose your Raspberry Pi model (Pi2 or Pi3). Inside those folders will be a directory named "sd". There you will find all the files that need to be placed on the SD card for it to work. Simply put those on a clean, formatted SD card and stick that into your Pi. Alternatively you can modify the source code to build it for another Pi model.

####Option 2 (For everything else)
Using the bootloader to upload programs to your Pi is much faster than going standalone and will not wear out the SD card socket of your computer and the Raspberry Pi. Go to /bootloader/pc and choose the corresponding folder based on your OS (Windows / Linux). The program inside is another C program and is already compiled with GCC. It's designed to be run immediately after the code is compiled. Since it's launched from the Makefile, you won't need to press upload yourself.
 
* I recommend soldering a couple headers to the RUN pins on your Pi and attaching a pushbutton to it. This lets you reset the Pi without removing the power and turning it back on to upload a new code (saves even more time).  
* Also note that once power is removed from your Pi, the code that was uploaded via the bootloader is GONE (it is stored in RAM). You will need to re-upload your program as soon as you short the RUN pins (hard reset), or cycle the power.

# Compiling and Making Your Own Programs

After a while, running someone else's code gets quite boring and most people want to make their own things, or at least edit some pre-made stuff so it works better for their intentions. In this section I'll explain how to download the compiler toolchain and everything you'll need to make your own code.

For the Raspberry Pi 3, you will need to download the aarch64 toolchain to compile C code. Procedure for install is slightly different depending on whether you're running Linux or Windows. For Linux, simply type:  
<code>sudo apt get install aarch64-linux-gnu-gcc</code>  
into the command line. On Windows, you'll need to go to this website:  
<url>https://launchpad.net/gcc-arm-embedded</url>  
There you can download your particular version of the software for your computer.

Makefiles are included in these example codes so most people who use them won't need to change anything to compile code. Simply type <code>make</code> into the command line (making sure the directory is in the right place), and then all the files such as kernel7.img will show up in the folder you make the project in. Also, the Makefile launches the uploader code on the computer, so everything is done all in one step.

These examples use four different files that work in conjunction to make the binary file kernel7.img. These files are:  
#####main.c  
* Holds the main source file that runs your program.

#####start.s  
* Contains the entry symbol <code>_start:</code> used by GCC. Jumps to main() in main.c.

#####memmap  
* Organizes the .text, .bss and .data sections of the final binary, since the "ROM" is all stored on the same RAM as the actual variables in RAM (Everything has a place in RAM!).

#####Makefile  
* Holds all the commands, compiler and linker options that tells GCC what to do with the previous 3 files.  

# Using Libraries

I'm currently working on lots of different libraries for bare metal development using the Pi. These will eventually cover everything from turning on an LED all the way up to using the USB ports. You can go into /lib to see what's accomplished so far. Inside each library file there will be instructions on how to use them.

All libraries rely on the file "RaspberryPi.h". Make sure you include it as the first line of your program. It's basically a bunch of #define statements that tell the other libraries where the perhiperal addresses are located in RAM.

#Other Repos, Sites, etc.

It has taken me many months to reach the stage that I'm at today. A lot of information, advice and help has been provided from the Raspberry Pi forums and from other sites. Here is where I'd like to put some of the places that I've found most helpful in creating these examples.

<url>https://github.com/dwelch67/raspberrypi</url>  
Large chunks of the code here has been taken from dwelch67's Github, particularily the start.s files and most of uart.c. I highly reccomend visiting his repository if you haven't already, there are a lot more examples than there are here (as of right now). The only reason why I re-did his bootloader code was because I couldn't figure out how to use minicom on my computer. I also couldn't find any free programs to use on Windows.

<url>http://www.valvers.com/open-software/raspberry-pi/step01-bare-metal-programming-in-cpt1/</url>  
This site is great because it explains how to use the GPU as well as many other important aspects of Raspberry Pi bare metal. A great tutorial and it's where I started and got my first "Hello World" program to run!

<url>https://github.com/rsta2/circle64</url>  
There are a lot of features in here, I will start looking through it and expand the list of libraries that I have. Great place to go after you understand the basics of bare metal, and want to get into some deeper programs.
