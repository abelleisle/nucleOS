/*
 * Copyright (C) 2019  Belle-Isle, Andrew <drumsetmonkey@gmail.com>
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

#include "clock.h"

// The number of clock ticks that have been run since the start of the OS.
volatile uint32_t clock_ticks = 0;

void Clock_Init(void)
{
    // Set the number of ticks to skip for the System Tick IRQ by taking
    //  HCLK (system clock) and dividing it by the number of times per second
    //  this should trigger, and subtract one.
    SysTick_Config((SystemCoreClock/1000)-1);
}

/**
 * Accuracy of 1ms.
 */
void SysTick_Handler(void)
{
    clock_ticks++;
}

void Clock_Delay(uint32_t delay)
{
    uint32_t expected = clock_ticks + delay;
    while(clock_ticks < expected);
}
