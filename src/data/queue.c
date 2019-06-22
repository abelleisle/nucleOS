/*
 * @file queue.c
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

#include "queue.h"

#include "stdlib.h"

struct Queue
{
    int first;
    int last;
    int size;
    int capacity;
    char* buffer;
};

Queue* Queue_Init(int capacity)
{
    Queue *queue = (Queue*)malloc(sizeof(Queue));

    // allocate queue data
    queue->buffer = (char*)malloc(capacity * sizeof (char));

    queue->capacity = capacity;
    queue->size = 0;

    queue->first = 0;
    queue->last = 0;

    return queue;
}

QUEUE_STATUS Queue_Enqueue(Queue* queue, char data)
{
    if (queue->size < queue->capacity) {
        queue->buffer[queue->last] = data;
        queue->last = (queue->last + 1) % queue->capacity;
        queue->size++;
        return QUEUE_OK;
    } else {
        return QUEUE_FULL;
    }
}

char Queue_Front(Queue* queue)
{
    if (queue->size != 0)
        return queue->buffer[queue->first];
    else
        return 0xFF;
}

QUEUE_STATUS Queue_Dequeue(Queue* queue)
{
    if (queue->size != 0) {
        queue->first = (queue->first + 1) % queue->capacity;
        queue->size--;
        return QUEUE_OK;
    } else {
        return QUEUE_EMPTY;
    }
}

char Queue_Pop(Queue* queue)
{
    char ret = Queue_Front(queue);
    Queue_Dequeue(queue);
    return ret;
}

QUEUE_STATUS Queue_Destroy(Queue* queue)
{
    free(queue->buffer);

    return QUEUE_OK;
}

int Queue_Size(Queue* queue)
{
    return queue->size;
}
