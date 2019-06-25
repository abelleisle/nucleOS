/*
 * @file serial.c
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

#define QUEUE_SIZE 64

// C LIBS
#include "stdlib.h"

// HEADER
#include "serial.h"

// KERNEL
#include "usart.h"
#include "gpio.h"
#include "data/queue.h"
#include "kernel/irq.h"

static Queue* sendQueue;
static Queue* recvQueue;

int Serial_Init(uint32_t baudrate, int datalength)
{
    USART3->CR1 |= USART_CR1_RXNEIE;

    GPIO_Mode(GPIOD, 8, ALTERNATE);
    GPIO_Mode(GPIOD, 9, ALTERNATE);

    GPIO_AlternateMode(GPIOD, 8, 7);
    GPIO_AlternateMode(GPIOD, 9, 7);

    USART_Init(USART3, baudrate, datalength);

    NVIC_EnableIRQ(USART3_IRQn);

    sendQueue = Queue_Init(QUEUE_SIZE);
    recvQueue = Queue_Init(QUEUE_SIZE);

    return 1;
}

int PutChar(char c)
{
    Queue_Enqueue(sendQueue, c);
    USART3->CR1 |= USART_CR1_TXEIE; // enable TX interrupt
    return 0;
}

int PutString(char* string)
{
    for (char *c = string; *c; c++)
        PutChar(*c);
    return 0;
}

char GetChar() {
    return Queue_Pop(recvQueue);
}

void USART3_IRQHandler()
{
    nIRQ_Lock();

    if (USART3->ISR & USART_ISR_RXNE) { // If interrupt was triggered by recieve
        Queue_Enqueue(recvQueue, (USART3->RDR & 0xFF));
    }
    if (USART3->ISR & USART_ISR_TXE) { // If interrupted from transmitter
        if (Queue_Size(sendQueue) >= 1)
            USART3->TDR = Queue_Pop(sendQueue) & 0xFF;

        if (Queue_Size(sendQueue) == 0)     // Disable tx interrupts if there
            USART3->CR1 &= ~USART_CR1_TXEIE;//  are no more characters to send
    }

    nIRQ_Unlock();
}
