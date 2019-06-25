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

// HEADER
#include "clock.h"

// KERNEL
#include "kernel/irq.h"
#include "kernel/task.h"
//#include "kernel/miros.h"

// The number of clock ticks that have been run since the start of the OS.
volatile nTime clock_ticks = 0;

void nClock_Init(void)
{
    // Set the number of ticks to skip for the System Tick IRQ by taking
    //  HCLK (system clock) and dividing it by the number of times per second
    //  this should trigger, and subtract one.
    SysTick_Config((SystemCoreClock/1000)-1);
    NVIC_SetPriority(SysTick_IRQn, 0U);
    NVIC_SetPriority(PendSV_IRQn, 0xE0U);
}

/**
 * Accuracy of 1ms.
 * Trigger task switch every 8ms
 */
void SysTick_Handler(void)
{
    ++clock_ticks;
    if (!(clock_ticks & 7)) {
        nIRQ_Lock();
        nTask_Schedule();
        //OS_sched();
        nIRQ_Unlock();
    }
}

void nClock_Delay(uint32_t delay)
{
    uint32_t expected = clock_ticks + delay;
    while(clock_ticks < expected); // hang here until delay is done
}

nTime nClock_Ticks(void)
{
    return clock_ticks;
}
