/*
 * @file event.h
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

#ifndef EVENT_H
#define EVENT_H

#include "stdint.h"

typedef enum
{
    NSIGNAL_TASK_INIT,
    NSIGNAL_TASK_KILL,
    NSIGNAL_TASK_EXIT,
    NSIGNAL_TASK_IDLE,
    NSIGNAL_TASK_RUNNING,
} nSignal;

typedef uint16_t nParam;

typedef struct
{
    nSignal sig;
    nParam par;
} nEvent;

nEvent nEvent_Create(nSignal, nParam);

#endif //EVENT_H
