# rak811Demos
## Introduction
This repository contains simple examples on how to program the STM32L151CB-A processor implemented on the Rak811 chip. This chip 
contains the processor and an SX1276 LoRa transceiver. Rak Wireless has released a reference program for the Rak811 tracker board. This program however is quite huge and not very easy to understand for a newcomer. In this repository I try to provide small demo programs showing how to interact with the individual components of the tracker board.
The programs use peripherals either implemented on the processor chip itself or on the Rak811 Tracker board. All programs have been developed with STM32CubeMX which generates the peripheral initialization code. This code is included into Eclipse with the Ac6STM32 plugin. STM32CubeMX generated code for the ST HAL (Hardware Abstraction Layer) library whose functions are subsequently used in the programs. Once the program has been successfully built it is flashed into the Rak811 processor using an ST-Link V2 debugging probe. In circuit debugging is accomplished using this probe with the help of openocd and gdb. All this can be done from within the Eclipse IDE.
## The Blink Demo (Rak811Blink)
The Rak811 tracker board has 2 user programmable LEDs connected to the GPIO port PA12 (LED1) and PB4 (LED2) The Blink program uses a 2 bit binary counter to drive those LEDs. The HAL_Delay function determines the frequency of blinking.
## The Timer Demo (Rak811Timer)
This program also uses the LEDs on te tracker board but here the blinking frequency is determined by 2 hardware timers. When the first timer expires it triggers an interrupt at a frequency of 1 Hz. In the callback routine associated with this interrupt the state of the first LED is toggled and the second LED switched on. Then a second 200 ms timer is started and the interrupt generated by this timer will switch the second LED off again.
## The UART or a Hello World program (Rak811HelloWorld)
The Hello World program in the world of embedded systems is the blinking LED. It is already quite a bit more difficult to write the traditional Hello World program because there usually a UART or an Internet connection is needed. The Rak811 tracker connects its UART1 to the USB connector which is seen on the Linux PC as /dev/ttyUSB0. When connecting /dev/ttyUSB0  with a serial Terminal emulator like minicom you can see the text sent to the UART on the Rak811 tracker board. The program also demonstrates how to redirect printf calls to the UART. For this the file syscalls.c from STM32CubeMX is copied into the project and a new file uart_io.c is added which does the actual re-direction implementing \_\_io_putchar \_\_io_getchar.
## GPS (Rak811GPS)
The Rak811 tracker uses an U-blox Max Q7 GNSS module as a GPS receiver. This module is interfaced to the Rak811 processor through its UART3. The Max Q7 sends GPS information in form of NMEA sentences. The program reads and prints these sentences which are in ASCII format. It send interprets each of the sentences and saves the results in dedicated data structures.
## I2C Scanner (Rak811_I2C_scanner)
The Rak811 tracker has a MEMS digital motion sensor on board. This chip is interfaced to the Rak811 chip through I2C. In order to scan the I2C bus for I2C slaves connected I wrote a simple I2C scanner. These program tries to acces an I2C slave on each of the possible I2C addresses and print the address on which it gets an answer.
## The LIS3-DH MEMS motion scanner (Rak811_lis3d)
In this program I try to read the LIS3-DH chip and print motion information. This needs some polishing.
## The Real Time Clock (Ral811RTC)
A demo program for the RTC. At the start of the program the user is asked to enter the current date and time (no line editing yet!). These data are sent to the RTC to set up date and time. In the main loop the RTC is read out every 5 s and date and time are printed.
## Flash writing and reading (Rak811Flash)
The new version of thee Rak Wireless reference program uses at-commands to configure the LoRa transceiver. The settings are saved in a page on the STM32L151CB-A flash. This program demonstrates how to erase, write and re-read a page in flash.
## The SX1276 LoRa transceiver (Rak811sx1276)
This program is intended to demonstrate how to send data from the Rak811 tracker to The Things Network (TTN). Dummy data is used.
For the moment this program is under construction and does not work yet.

