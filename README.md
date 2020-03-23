# nucleOS #

nucleOS is a hobbiest operating system designed to run on multiple platforms.

## Current State ##
Currently, nucleOS is going through **very** early development stages, so it's still lacking critical features

## Architecture Support ##
* i686
* x86_64 (in progress)
* ARM (planned)

## Features ##
* Custom toolchain
* An awesome boot logo (see for youself)
* Partially complete C Library (PDClib)
* x86 Specific
  * Framebuffer printing support
  * Multiboot support

## Planned Features ##
* Multitasking
* Real mode (user mode)
* Long mode
* Support for drivers
* Fully complete C Library
* Filesystem support
  * FAT
    * Simple enough for custom implementation
  * EXT2/3/4
    * Requires complete C library with all system calls
    * Not necessary
* Socket support
  * Passing data between tasks
