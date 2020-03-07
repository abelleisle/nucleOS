; x86 crtn.s
section .init
    ; crtend.o .init goes here
    pop ebp
    ret

section .fini
    ; crtend.o .fini goes here
    pop ebp
    ret
