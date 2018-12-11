#include "stdint.h"

void HardFault_Handler(void)
{
    // TODO output this value over serial for debugging
    volatile uint32_t* location asm("r0");

    // loop forever and keep fault value in R0
    asm volatile(
        "cpsid  I\t\n"      // disable interrupts
        "b      .\t\n"      // loop
    );
}
