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

int main(void) 
{
    Clock_Init();
    
    //init_usart(USART3, 8);
    GPIO_Init();
    GPIO_Mode(GPIOB, 0, OUTPUT);

    while (1) {
        GPIO_TogglePin(GPIOB, 0);
        Clock_Delay(1000);
    };

    return 0;
}
