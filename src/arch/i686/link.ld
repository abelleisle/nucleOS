ENTRY(_loader)                   /* Label where program will enter */

SECTIONS {
    . = 0x00100000;             /* Load code at 1 MB */
    __start = .;

    .text ALIGN (0x1000) :      /* Align @ 4kb */
    {
        *(.multiboot)
        *(.text)                /* Text sections from every file */
    }

    .rodata ALIGN (0x1000) :    /* Align @ 4kb */
    {
        *(.rodata*)             /* Read-only sections from every file */
    }

    .data ALIGN (0x1000) :      /* Align @ 4kb */
    {
        *(.data)                /* Data sections from every file */
    }

    .bss ALIGN (0x1000) :       /* Align @ 4kb */
    {
        *(COMMON)               /* Common sections from every file */
        *(.bss)                 /* Zero-d out memory from every file */
    }
    __end = .;
}
