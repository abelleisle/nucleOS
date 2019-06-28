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

// KERNEL
#include "kernel/event.h"
#include "kernel/clock.h"
#include "kernel/task.h"
#include "kernel/irq.h"

#include "peripherals/usart.h"
#include "peripherals/gpio.h"
#include "peripherals/serial.h"

#include "data/queue.h"

#include "fs/fat/fat.h"


void flash1_task(void);
void flash2_task(void);
void flash3_task(void);
void serial_task(void);

int main(void) 
{
    nIRQ_Lock();
    nClock_Init();
    GPIO_Init();

    RCC->AHB3ENR |= ~(RCC_AHB3RSTR_CPURST | RCC_AHB3RSTR_FMCRST);
    
    GPIO_Mode(GPIOB, 0, OUTPUT);
    GPIO_Mode(GPIOB, 7, OUTPUT);
    GPIO_Mode(GPIOB, 14, OUTPUT);
    Serial_Init(115200, 8);

    nTask_Start(&flash1_task, 128);
    nTask_Start(&flash2_task, 128);
    nTask_Start(&flash3_task, 128);
    nTask_Start(&serial_task, 4096);

    nIRQ_Unlock();

    nTask_Begin();

    while (1);

    return 0;
}

void flash1_task(void)
{
    while(1) {
        GPIO_TogglePin(GPIOB, 0);
        nClock_Delay(1000);
    }
}

void flash2_task(void)
{
    while(1) {
        GPIO_TogglePin(GPIOB, 7);
        nClock_Delay(500);
    }
}

void flash3_task(void)
{
    while(1) {
       GPIO_TogglePin(GPIOB, 14);
       nClock_Delay(250);
    }
}

void serial_task(void)
{
    while(1) {
        PutString("You boys need to look out\n\r");
        nClock_Delay(5000);
    }
}
