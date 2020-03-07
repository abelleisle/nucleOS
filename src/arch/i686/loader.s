;----------------------;
;-  MULTIBOOT HEADER  -;
;----------------------;

MULTIBOOT_PAGE_ALIGN    equ  1 << 0     ; align loaded modules on page boundaries
MULTIBOOT_MEMORY_INFO   equ  1 << 1     ; provide memory map
MULTIBOOT_VIDEO_MODE    equ  1 << 2     ; provide memory map
MULTIBOOT_MAGIC         equ  0x1BADB002 ; 'magic number' lets bootloader find the header

multiboot_flags         equ  MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO
multiboot_checksum      equ -(MULTIBOOT_MAGIC + multiboot_flags)
 
; Tell multiboot that this is a kernel
section .multiboot
align 4
    dd MULTIBOOT_MAGIC
    dd multiboot_flags
    dd multiboot_checksum
    
    dd 0x00000000
    dd 0x00000000
    dd 0x00000000
    dd 0x00000000
    dd 0x00000000

    dd 0x00000000
    dd 800
    dd 600
    dd 32
 
;------------------;
;-  KERNEL STACK  -;
;------------------;

section .bss
align 16

global __stack_bottom
global __stack_top
__stack_bottom:
resb 8192 ; Define our stack to be 8MB
__stack_top:

;------------------------;
;-  KERNEL ENTRY POINT  -;
;------------------------;

section .text
global _loader:function (_loader.end - _loader)
_loader:
    cli
    cld
    ; Point to the top of the stack since stack grows downwards in x86
    ;   based systems
    mov esp, __stack_top
 
    push eax ; Push the multiboot magic
    push ebx ; Push the multiboot header adress.
    
    extern kmain
    call kmain ; Enter the kernel main

    cli
.hang:  hlt
    jmp .hang
.end:
