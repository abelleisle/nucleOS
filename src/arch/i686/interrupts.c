#include "interrupts.h"
#include <peripheral/framebuffer/framebuffer.h>

static const char *exception_messages[32] = {
    "Divide by Zero",
    "Debug",
    "Non-maskable interrupt",
    "Breakpoint",
    "Overflow Detected",
    "Out-of-Bounds",
    "Invalid OPCode",
    "No Co-Processor",
    "Double Fault",
    "Co-Processor Segment Overrun",
    "Bad TSS",
    "Segment not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Co-Processor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
};

uint32_t ISR_Handler(uintptr_t esp, registers_t regs)
{
    Framebuffer_PutString("Recieved Interrupt: ");

    // TODO add specific handling
    if (regs.int_no <= 31) {
        Framebuffer_PutString(exception_messages[regs.int_no]);
        Framebuffer_PutString("\n\tESP:");
        Framebuffer_PutInt(regs.esp);
    } else {
        Framebuffer_PutInt(regs.int_no);
    }

    Framebuffer_PutChar('\n');

    return esp;
}
