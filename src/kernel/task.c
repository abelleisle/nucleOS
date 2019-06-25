/*
 * @file task.c
 *
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
#include "task.h"

// C LIBS
#include "stdlib.h"

// KERNEL
#include "kernel/irq.h"
#include "kernel/event.h"
#include "kernel/clock.h"

#include "peripherals/gpio.h"
#include "peripherals/serial.h"

nTask * volatile nTask_Current;
nTask * volatile nTask_Next;

nTask *nTask_Threads[32 + 1]; 
uint8_t nTask_ThreadNum = 0;
uint8_t nTask_ThreadIDX = 0;

nTask* nTask_Start(nTaskHandler handler, nStack stackSize)
{
    nTask* t = (nTask*)malloc(sizeof(nTask));
    t->stack = (void*)malloc(stackSize);

    uint32_t* sp = (uint32_t*)((((uint32_t)t->stack + stackSize) / 8) * 8); // align
    uint32_t* stk_limit;

    /* xPSR */ *(--sp) = (1U << 24);
    /*  PC  */ *(--sp) = (uint32_t)handler;
    /*  LR  */ *(--sp) = 0xEU;
    /*  R12 */ *(--sp) = 0xCU;
    /*  R3  */ *(--sp) = 0x3U;
    /*  R2  */ *(--sp) = 0x2U;
    /*  R1  */ *(--sp) = 0x1U;
    /*  R0  */ *(--sp) = 0x0U;

    /* Registers R4-R11 */
    /*  R11 */ *(--sp) = 0xBU;
    /*  R10 */ *(--sp) = 0xAU;
    /*  R9  */ *(--sp) = 0x9U;
    /*  R8  */ *(--sp) = 0x8U;
    /*  R7  */ *(--sp) = 0x7U;
    /*  R6  */ *(--sp) = 0x6U;
    /*  R5  */ *(--sp) = 0x5U;
    /*  R4  */ *(--sp) = 0x4U;

    t->sp = sp;

    stk_limit = (uint32_t*)(((((uint32_t)t->stack - 1U) / 8) + 1U) * 8);

    for (sp = sp - 1U; sp >= stk_limit; --sp)
        *(sp) = 0xDEADBEEFU;

    if (nTask_ThreadNum < (sizeof(nTask_Threads)/sizeof(nTask_Threads[0])))
        nTask_Threads[nTask_ThreadNum++] = t;
        

    return t;
}

void nTask_Begin()
{
    nIRQ_Lock();
    nTask_Schedule();
    nIRQ_Unlock();
}

void nTask_Schedule(void)
{
    nTask_ThreadIDX = ((nTask_ThreadIDX + 1) % nTask_ThreadNum);
    nTask_Next = nTask_Threads[nTask_ThreadIDX];

    if (nTask_Next != nTask_Current)
        SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk; // Switch tasks (PendSV)
}


__attribute__((naked))
void PendSV_Handler(void) {

__asm("     CPSID    I;");

/* Are we currently in a task or not? */
__asm("     MOV      r1, %0;" :: "r" (nTask_Current->sp));
__asm("     CBZ      r1, PendSV_restore;"); // if not load new task

/* Store old task */
__asm("     PUSH     {r4-r11};");
__asm("     MOV      %0, sp;" : "=r" (nTask_Current->sp));

/* Switch to new task */
__asm(" PendSV_restore:;");

nTask_Current = nTask_Next;

__asm("     MOV      sp, %0;" :: "r" (nTask_Next->sp));
__asm("     POP      {r4-r11};");

__asm("     CPSIE    I;");
__asm("     BX       lr;");
}
