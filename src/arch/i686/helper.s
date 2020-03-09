section .text

global GDT_Flush
GDT_Flush:
    mov eax, [esp + 4]
    lgdt [eax]

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov ss, ax
    mov gs, ax
    jmp 0x08:._GDT_Flush

._GDT_Flush:
    ret

global IDT_Flush
IDT_Flush:
    mov eax, [esp + 4]
    lidt [eax]
    ret
