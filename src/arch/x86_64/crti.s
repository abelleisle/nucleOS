/* x86_65 crti.s */
.section .init
.global _init
.type _init, @function
_init:
    push %rbp
    movq %rsp, %rbp
    // crtbegin.o .init goes here

.section .fini
.global _fini
.type _fini, @function
_fini:
    push %rbp
    movq %rsp, %rbp
    // crtbegin.o .fini goes here

