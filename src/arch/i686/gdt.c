#include "gdt.h"

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
