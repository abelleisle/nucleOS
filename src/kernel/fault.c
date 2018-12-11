void HardFault_Handler(void)
{
    // loop forever and keep fault value in R0
    asm volatile(
        "cpsid  I\t\n"
        "b      .\t\n"
    );
}
