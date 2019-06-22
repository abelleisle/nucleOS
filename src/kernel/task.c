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
#include "irq.h"
#include "peripherals/gpio.h"

//#define MAX_TASKS 8
//
//static uint32_t _nTask_currentPriority = (uint32_t)0xFF;
//static uint32_t _nTask_readSet = (uint32_t)0;
//
//typedef struct {
//    nTask task;     // The task that will actually be running
//    nEvent *queue;  // 
//    uint32_t end;   //
//    uint32_t head;  //
//    uint32_t tail;
//    uint32_t used;
//    uint32_t mask;
//} nTaskCB;
//
//static nTaskCB tasks[MAX_TASKS];
//
//void nTask_create(nTask task, uint32_t priority,
//                nEvent* queue, uint32_t queueLength,
//                nSignal sig, nParam par)
//{
//    nEvent ie; // initialization event
//    nTaskCB *tcb = &tasks[priority-1];
//    tcb->task = task;
//    tcb->queue = queue;
//    tcb->end = queueLength;
//    tcb->head = (uint32_t)0;
//    tcb->tail = (uint32_t)0;
//    tcb->used = (uint32_t)0;
//    tcb->mask = (1 << (priority-1));
//    ie.sig = sig;
//    ie.par = par;
//    tcb->task(ie);                                     /* Initialize the task */
//}
//
//void nTask_run(void)
//{
//    nTask_start(); // start all ISRs
//
//    nIRQ_Lock();
//    _nTask_currentPriority = 0; // set idle loop priority
//    _nTask_schedule();
//    nIRQ_Unlock();
//
//    while (1) {
//        nTask_onIdle();
//        _nTask_schedule();
//    }
//}
//
//void _nTask_schedule(void)
//{
//    static uint8_t const log2Lkup[] = {
//        0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4,
//        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
//        6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
//        6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
//        7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
//        7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
//        7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
//        7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
//        8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
//        8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
//        8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
//        8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
//        8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
//        8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
//        8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
//        8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
//    };
//    uint32_t pin = _nTask_currentPriority;               /* Internal priority */
//    uint32_t p;                                               /* new priority */
//
//    while ((p = log2Lkup[_nTask_readSet]) > pin) {
//        nTaskCB *tcb = &tasks[p -1];
//
//        nEvent e = tcb->queue[tcb->tail];
//        if ((++tcb->tail) == tcb->end)
//            tcb->tail = 0;
//
//        if ((--tcb->used) == 0)
//            _nTask_readSet &= ~tcb->mask;
//
//        _nTask_currentPriority = p;
//        nIRQ_Unlock();
//        
//        (*tcb->task)(e);
//
//        nIRQ_Lock();
//    }
//    _nTask_currentPriority = pin;
//}

// signal
//__attribute__ ((naked))
void PendSV_Handler(void)
{
    GPIO_TogglePin(GPIOB, 0);
}
