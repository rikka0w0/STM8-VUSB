# STM8 custom HID device demo

# Announcement and last update

This project has been stopped for nearly a year and I think it is time to
 demonstrate some of my latest progress.
 Unfortunately, I am super busy at this moment, I made a really hard decision,
 which is I am about to stop working on this project, but you can still feel free to contact me for 
 support. I am going to release some of my un-uploaded progress here.

This piece of software consists of two major parts:
* Rx and Tx, written is ASM, handles the low level communication, bit-stuffing, bit-destuffing
* USB state machine, written in C, controls the device enumeration process, emulates end points...

The original author (the Russian) did not implement bit-destuffing properly in the Rx code. I proposed 
two ways to overcome this problem:
* Keep 12MHz crystal, receive raw data from USB Host, then do bit-destuffing later
Perhaps this is the easiest approach, but the major drawback is that the program will take twice the time
to process a given income packet. USB_R.docx demostrates how this approach works.
* Migrate to 15MHz crystal, this gives 2 extra instruction cycles per USB bit(1.5Mhz), however it is still not 
easy to implement such algorithms. The STM8 series got a crappy instruction set, compared to AVR 
microcontroller, some critical instructions are missing, e.g. XNOR. Furthermore, only one register can be
used as a parameter and receive result, we have to move data around! This takes extra cycles!

License stuff:
I'm not a professional programmer. You can use this software in any open source projects and you are allowed to 
distribute modified version of this software, as long as the entire source code remains open source! For 
commercial purposes, contact me.

# Setup and Configuration

Aim:
Simulate a low-speed USB1.1 device using cost-effective STM8 microcontrollers

Current progress:
Able to enumerate the device as a vendor-defined HID device
Able to receive data from the host

To-Do:
Add support to "String Descriptors"
"Hide" low level USB functions for high level designers

Hardware configuration:
- MCU(STM8S103F3P6) is work at 3.3V, supplied by USB 5V via a linear regulator(AMS1117)
- PC7 - "D+ green line"
- PC6 - "D- white line" + 1,5 kOm pull up to +3.3V
- PA1 and PA2 - 12M crystal oscillator
- NRST - 10K resistor to 3.3V and 0.1u capacitor to ground
- VCap - 0.1u capacitor to ground

Optional Bits:
AFR0 - Port C6 = TIM1_CH1, C7 = TIM1_CH2
Above settings can be done using "light programmer" in STVD

Compiler: 
ST Visual Develop (STVD) + Cosmic CxSTM8 C compiler

Special thanks:
Original author (Russian):
https://github.com/ZiB/STM8S-USB
HID Example (Chinese):
https://github.com/wlianmin/stm8_usb


Background and references:
http://www.usbmadesimple.co.uk/ums_3.htm
http://www.beyondlogic.org/usbnutshell/usb4.shtml#Interrupt