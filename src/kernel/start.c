#include "stdint.h"
#include "system/system_stm32h7xx.h"
#include "system/stm32h743xx.h"

void main(void) 
{
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOGEN;
    while(1){};
}
