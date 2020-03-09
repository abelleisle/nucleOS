;----------------------;
;-  MULTIBOOT HEADER  -;
;----------------------;

MULTIBOOT_MAGIC         equ  0x1BADB002 ; 'magic number' lets bootloader find the header
MULTIBOOT_PAGE_ALIGN    equ  0x1        ; align loaded modules on page boundaries
MULTIBOOT_MEMORY_INFO   equ  0x2        ; provide memory map
MULTIBOOT_VIDEO_MODE    equ  0x4        ; provide memory map

multiboot_flags         equ  MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO | MULTIBOOT_VIDEO_MODE
multiboot_checksum      equ -(MULTIBOOT_MAGIC + multiboot_flags)
 
; Tell multiboot that this is a kernel
section .multiboot
align 4
    dd MULTIBOOT_MAGIC
    dd multiboot_flags
    dd multiboot_checksum
    
    ; Multiboot memory info
    dd 0x00000000 ; Header Address
    dd 0x00000000 ; Load Address
    dd 0x00000000 ; Load End Address
    dd 0x00000000 ; BSS End Address
    dd 0x00000000 ; Entry Address

    ; Multiboot video mode
    dd 0x00000000 ; Video mode type
    dd 1280       ; Width
    dd 720        ; Height
    dd 32         ; Depth
 
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
