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

// STD
#include "stdlib.h"

#define MAX_TASKS = 8;

static uint32_t task_pid = 0; // current task process ID
static uint32_t task_sem = 0; // current task semaphore

typedef struct {
    nTask task;     // The task that will actually be running
    nEvent *queue;  // 
    uint32_t end;   //
    uint32_t head;  //
    uint32_t tail;
    uint32_t used;
    utin32_t mask;
} nTaskCB;

static nTaskCB tasks[MAX_TASKS];

void nTask_Init(nTask task, uint32_t priority,
                nEvent* queue, uint32_t queueLength,
                nSignal sig, nParam par)
{
    nEvent = ie; // initialization event
    nTaskCB tcb* = &tasks[priority-1];
    tcb->task = task;
    tcb->queue = queue;
    tcb->end = queueLength;
    tcb->head = (uint32_t)0;
    tcb->tail = (uint32_t)0;
    tcb->used = (uint32_t)0;
    tcb->mask = (1 << (priority-1));
    ie.sig = sig;
    ie.par = par;
    tcb->task(ie);
}
