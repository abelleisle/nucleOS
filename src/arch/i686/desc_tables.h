#ifndef _DESC_TABLES_H
#define _DESC_TABLES_H

#include <stdint.h>

/*****************
*  GDT HEADERS  *
*****************/

#define GDT_ENTRY_COUNT 6

#define GDT_PRESENT 0b10010000 // Present bit
#define GDT_USER    0b01100000 // Priviledge level, 2 bits. 0 = highest (kernel)
                               //                           3 = lower (user)

#define GDT_EXECUTABLE 0b00001000 // Executable bit. If this bit is 1 then this
                                  //  is a code segment, if this is a 0 then
                                  //  this is a data segment.
#define GDT_READWRITE  0b00000010 // Readable bit for code selectors
                                  // Writeable bit for data selectors
#define GDT_ACCESSED   0b00000001 // Access bit, 1 if data was accessed
                                  //             0 if data was untouched

#define GDT_FLAGS 0b1100
#define TSS_FLAGS 0

/*****************
*  IDT HEADERS  *
*****************/

#define IDT_ENTRY_COUNT 256

/***************
*  GDT TYPES  *
***************/

typedef struct __attribute__((packed))
{
    uint32_t prev_tss;

    uint32_t esp0;
    uint32_t ss0;
    uint32_t esp1;
    uint32_t ss1;
    uint32_t esp2;
    uint32_t ss2;

    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;

    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;

    uint32_t es;
    uint32_t cs;
    uint32_t ss;
    uint32_t ds;
    uint32_t fs;
    uint32_t gs;

    uint32_t ldt;
    uint16_t trap;
    uint16_t iomap_base;
} TSS;

typedef struct __attribute__((packed))
{
    uint16_t size;
    uint32_t offset;
} GDTDescriptor;

typedef struct __attribute__((packed))
{
    uint16_t limit0_15;
    uint16_t base0_15;
    uint8_t  base16_23;
    uint8_t  access;
    uint8_t  limit16_19 : 4;
    uint8_t  flags : 4;
    uint8_t  base24_31;
} GDTEntry;

/***************
*  IDT TYPES  *
***************/

typedef struct __attribute__((packed))
{
    uint16_t limit;
    uint32_t base;
} IDTDescriptor;

typedef struct __attribute__((packed))
{
    uint16_t base_lo;
    uint16_t sel;
    uint8_t  always0;
    uint8_t  flags;
    uint16_t base_hi;
} IDTEntry;

/*******************
*  GDT FUNCTIONS  *
*******************/

GDTEntry GDT_CreateEntry(uint32_t base, uint32_t limit, 
                         uint32_t access, uint32_t flags);

void GDT_Setup(void);
void GDT_SetKernelStack(uint32_t stack);
extern void GDT_Flush(uint32_t);

/*******************
*  IDT FUNCTIONS  *
*******************/

void IDT_Setup();
IDTEntry IDT_CreateEntry(uint32_t, uint16_t, uint8_t);
extern void IDT_Flush(uint32_t);

extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
extern void isr8 ();
extern void isr9 ();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

#endif /* ifndef _DESC_TABLES_H */
