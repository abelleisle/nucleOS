; x86_64 crti.s
section .init
global _init:function
_init:
    push rbp
    mov rbp, rsp
    ; crtbegin.o .init goes here

section .fini
global _fini:function
_fini:
    push rbp
    mov rbp, rsp
    ; crtbegin.o .fini goes here
