# NucleOS #

## What is this? ##
nucleOS is my rendition of a operating system (OS) that's both architecture and board agnostic.

## Features ##
None at the moment, check back later :)

## Directory Structure
* `boot` - Basic bootloader or bootup sequence code
* `kernel` - The kernel itself. Only handles kernel tasks, no hardware drivers, etc..:
  * Task scheduling
  * Timers/callbacks
  * Priviledge management
  * Memory management
  * IPC
* `system` - The system code used to create a "distro" of sorts. Hardware initializtion, entrypoint from bootloader, linker script generation, initramfs, file system loader, etc..

* `docs` - NucleOS documentation (augmented with code docs)
* `examples` - Example system code that is used to provide examples (and test) the use of NucleOS

## Building
NucleOS uses a root `build.zig` to package and build NucleOS how the user feels. It can either be used to expose just the kernel to the user, or build a system image (with or without packaged bootloader).
