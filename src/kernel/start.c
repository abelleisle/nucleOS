/*
 * @file start.c
 * The first file that is run when the board is booted.
 *
 * Copyright (C) 2018  Belle-Isle, Andrew <drumsetmonkey@gmail.com>
 * Author: Belle-Isle, Andrew <drumsetmonkey@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// C LIBS
#include "stdint.h"
#include "stdio.h"

// STM LIBS
#include "system/system_stm32h7xx.h"
#include "system/stm32h743xx.h"

// MY HEADERS
#include "peripherals/usart.h"
#include "peripherals/gpio.h"
#include "kernel/clock.h"
#include "peripherals/serial.h"

int main(void) 
{
    __disable_irq();
    Clock_Init();
    GPIO_Init();

    RCC->AHB3ENR |= ~(RCC_AHB3RSTR_CPURST | RCC_AHB3RSTR_FMCRST);
    
    GPIO_Mode(GPIOB, 0, OUTPUT);
    GPIO_Mode(GPIOB, 7, OUTPUT);
    //USART_Init(USART3, 115200, 8);
    Serial_Init(115200, 8);

    __enable_irq();

    while (1) {
        static char c = 'a';
        GPIO_TogglePin(GPIOB, 0);

        c += 1;
        if (c >= 123)
            c = 97;
        PutChar(c);

        //if (GetChar() == 'f')
        //    GPIO_TogglePin(GPIOB, 7);

        Clock_Delay(1000);
    };

    return 0;
}
