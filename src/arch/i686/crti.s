; x86 crti.s
section .init
global _init:function
_init:
    push ebp
    mov ebp, esp
    ; crtbegin.o .init goes here

section .fini
global _fini:function
_fini:
    push ebp
    mov ebp, esp
    ; crtbegin.o .fini goes here
