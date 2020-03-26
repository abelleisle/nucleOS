#include "desc_tables.h"

/*******************
*  GDT VARIABLES  *
*******************/

static TSS tss = {
    .ss0  = 0x10,
    .esp0 = 0,
    .cs   = 0x0b,
    .ss   = 0x13,
    .ds   = 0x13,
    .es   = 0x13,
    .fs   = 0x13,
    .gs   = 0x13,
};

static GDTEntry gdt_entries[GDT_ENTRY_COUNT];

static GDTDescriptor gdt_descriptor = {
    .size = sizeof(GDTEntry) * GDT_ENTRY_COUNT,
    .offset = (uint32_t)&gdt_entries[0]
};

/*******************
*  IDT VARIABLES  *
*******************/

static IDTEntry idt_entries[IDT_ENTRY_COUNT];
static IDTDescriptor idt_descriptor = {
    .limit = sizeof(IDTEntry) * IDT_ENTRY_COUNT - 1,
    .base = (uint32_t)&idt_entries
};

/*******************
*  GDT FUNCTIONS  *
*******************/

void GDT_Setup(void)
{
    gdt_entries[0] = GDT_CreateEntry(0, 0, 0, 0);

    gdt_entries[1] = GDT_CreateEntry(
        0,
        0xffffffff,
        GDT_PRESENT | GDT_READWRITE | GDT_EXECUTABLE,
        GDT_FLAGS
    );

    gdt_entries[2] = GDT_CreateEntry(
        0,
        0xffffffff,
        GDT_PRESENT | GDT_READWRITE,
        GDT_FLAGS
    );

    gdt_entries[3] = GDT_CreateEntry(
        0,
        0xffffffff,
        GDT_PRESENT | GDT_READWRITE | GDT_USER | GDT_EXECUTABLE,
        GDT_FLAGS
    );

    gdt_entries[4] = GDT_CreateEntry(
        0,
        0xffffffff,
        GDT_PRESENT | GDT_READWRITE | GDT_USER,
        GDT_FLAGS
    );

    gdt_entries[5] = GDT_CreateEntry(
        ((uintptr_t)&tss),
        sizeof(TSS),
        GDT_PRESENT | GDT_READWRITE | GDT_ACCESSED,
        TSS_FLAGS
    );

    GDT_Flush((uint32_t)&gdt_descriptor);
}

GDTEntry GDT_CreateEntry(uint32_t base, uint32_t limit, 
                         uint32_t access, uint32_t flags)
{
    return (GDTEntry)
    {
        .access     = (access),
        .flags      = (flags),
        .base0_15   = (base) & 0xffff,
        .base16_23  = ((base) >> 16) & 0xff,
        .base24_31  = ((base) >> 24) & 0xff,
        .limit0_15  = (limit) & 0xffff,
        .limit16_19 = ((limit) >> 16) & 0x0f
    };
}

void GDT_SetKernelStack(uint32_t stack)
{
    tss.esp0 = stack;
}

/*******************
*  IDT FUNCTIONS  *
*******************/

static void idt_FillTable();

void IDT_Setup()
{
    IDTEntry blank = IDT_CreateEntry(0, 0, 0);
    // TODO replace with memset
    for (int i = 0; i < IDT_ENTRY_COUNT; i++) {
        idt_entries[i] = blank;
    }

    // Fill all IDT tables
    idt_FillTable();

    IDT_Flush((uint32_t)&idt_descriptor);
}

IDTEntry IDT_CreateEntry(uint32_t base, uint16_t sel, uint8_t flags)
{
    return (IDTEntry)
    {
        .base_lo = base & 0xFFFF,
        .base_hi = (base >> 16) & 0xFFFF,
        .sel     = sel,
        .always0 = 0,

        // TODO remove the comment when implementing user-mode
        // This sets the interrupt gate's privilege level to 3
        .flags   = flags /* | 0x60 */
    };
}

static void idt_FillTable(void)
{
    idt_entries[ 0] = IDT_CreateEntry((uint32_t)isr0,  0x08, 0x8E);
    idt_entries[ 1] = IDT_CreateEntry((uint32_t)isr1,  0x08, 0x8E);
    idt_entries[ 2] = IDT_CreateEntry((uint32_t)isr2,  0x08, 0x8E);
    idt_entries[ 3] = IDT_CreateEntry((uint32_t)isr3,  0x08, 0x8E);
    idt_entries[ 4] = IDT_CreateEntry((uint32_t)isr4,  0x08, 0x8E);
    idt_entries[ 5] = IDT_CreateEntry((uint32_t)isr5,  0x08, 0x8E);
    idt_entries[ 6] = IDT_CreateEntry((uint32_t)isr6,  0x08, 0x8E);
    idt_entries[ 7] = IDT_CreateEntry((uint32_t)isr7,  0x08, 0x8E);
    idt_entries[ 8] = IDT_CreateEntry((uint32_t)isr8,  0x08, 0x8E);
    idt_entries[ 9] = IDT_CreateEntry((uint32_t)isr9,  0x08, 0x8E);
    idt_entries[10] = IDT_CreateEntry((uint32_t)isr10, 0x08, 0x8E);
    idt_entries[11] = IDT_CreateEntry((uint32_t)isr11, 0x08, 0x8E);
    idt_entries[12] = IDT_CreateEntry((uint32_t)isr12, 0x08, 0x8E);
    idt_entries[13] = IDT_CreateEntry((uint32_t)isr13, 0x08, 0x8E);
    idt_entries[14] = IDT_CreateEntry((uint32_t)isr14, 0x08, 0x8E);
    idt_entries[15] = IDT_CreateEntry((uint32_t)isr15, 0x08, 0x8E);
    idt_entries[16] = IDT_CreateEntry((uint32_t)isr16, 0x08, 0x8E);
    idt_entries[17] = IDT_CreateEntry((uint32_t)isr17, 0x08, 0x8E);
    idt_entries[18] = IDT_CreateEntry((uint32_t)isr18, 0x08, 0x8E);
    idt_entries[19] = IDT_CreateEntry((uint32_t)isr19, 0x08, 0x8E);
    idt_entries[20] = IDT_CreateEntry((uint32_t)isr20, 0x08, 0x8E);
    idt_entries[21] = IDT_CreateEntry((uint32_t)isr21, 0x08, 0x8E);
    idt_entries[22] = IDT_CreateEntry((uint32_t)isr22, 0x08, 0x8E);
    idt_entries[23] = IDT_CreateEntry((uint32_t)isr23, 0x08, 0x8E);
    idt_entries[24] = IDT_CreateEntry((uint32_t)isr24, 0x08, 0x8E);
    idt_entries[25] = IDT_CreateEntry((uint32_t)isr25, 0x08, 0x8E);
    idt_entries[26] = IDT_CreateEntry((uint32_t)isr26, 0x08, 0x8E);
    idt_entries[27] = IDT_CreateEntry((uint32_t)isr27, 0x08, 0x8E);
    idt_entries[28] = IDT_CreateEntry((uint32_t)isr28, 0x08, 0x8E);
    idt_entries[29] = IDT_CreateEntry((uint32_t)isr29, 0x08, 0x8E);
    idt_entries[30] = IDT_CreateEntry((uint32_t)isr30, 0x08, 0x8E);
    idt_entries[31] = IDT_CreateEntry((uint32_t)isr31, 0x08, 0x8E);
}
