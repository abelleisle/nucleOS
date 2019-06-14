/*
 * @file queue.h
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

#ifndef QUEUE_H
#define QUEUE_H

#include "stdint.h"

typedef struct
{
    int first;
    int last;
    int size;
    int capacity;
    uint8_t* buffer;
} Queue;

int Queue_Init(Queue*, int);
int Queue_Enqueue(Queue*, uint8_t);
uint8_t Queue_Dequeue(Queue*);
int Queue_Destroy(Queue*);

#endif //QUEUE_H
