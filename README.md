# STM8 custom HID device demo
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
