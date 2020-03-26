#ifndef _TYPES_H
#define _TYPES_H

#include <stdint.h>

typedef struct
{
    uint32_t gs, fs, ex, ds;                         // Data segment selector
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha
    uint32_t int_no, err_code;                       // ISR number and err code
    uint32_t eip, cs, eflags, useresp, ss;           // Pushed by CPU
} registers_t;

#endif /* ifndef _TYPES_H */
