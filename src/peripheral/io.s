global outb

; outb - Send byte to I/O port
;
; param: [esp + 8] Data port
;        [esp + 4] I/O port
;        [esp    ] Return address
outb:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al
    ret

global inb

; inb - Read byte from I/O port
;
; param: [esp + 4] I/O port
;        [esp    ] Return address
inb:
    mov dx, [esp + 4]
    in al, dx
    ret
