# nucleOS #

## What is this? ##
nucleOS is my rendition of an RTOS for the STM32 Nucleo development boards.

This OS is being developed on an STM32-Nucleo H743ZI

## Features ##
* Real-time multitasking using round robin scheduling
* Serial over ST-Link USB
* HAL Drivers
  * USART
  * GPIO
  * SPI
* No external dependancies :)
* Very Lightweight

## Planned Features ##
* Custom NucleOS toolchain and custom implementations of system calls
* SD Card program loading using FAT **(In progress)**
* Ability to load programs using ELF format
* I2C Hal driver
* TFT-RGB display driver
* Ethernet driver

## Current State ##
Currently, nucleOS is going through a rewrite in which local unorganized test code is being rewritten and optimized before being compiled into this repository.
