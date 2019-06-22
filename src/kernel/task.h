/*
 * @file task.h
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


#ifndef TASK_H
#define TASK_H

// C LIBS
#include "stdint.h"

// KERNEL
#include "event.h"

typedef void (*nTask)(nEvent e);

/**************************
 *  PLATFORM INDEPENDENT  *
 **************************/
//void nTask_init(void);
//void nTask_create(nTask task, uint32_t priority,
//                nEvent* queue, uint32_t queueLength,
//                nSignal sig, nParam par);
//
//void nTask_run(void);
//
//void _nTask_schedule(void);

/******************
 *  USER DEFINED  *
 ******************/
//void nTask_start(void);
//void nTask_onIdle(void);
//void nTask_exit(void);
#endif // TASK_H
