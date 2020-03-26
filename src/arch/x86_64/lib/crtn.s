; x86_64 crtn.s
.section .init
    ; crtend.o .init goes here
    pop rbp
    ret

.section .fini
    ; crtend.o .fini goes here
    pop rbp
    ret
