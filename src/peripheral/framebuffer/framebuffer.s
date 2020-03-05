section .text

global vbe_get_mode
;extern vbe_info_block

vbe_get_mode:
    push es
    mov ax, 0x4F00
    ;mov di, vbe_info_block
    int 0x10
    pop es
