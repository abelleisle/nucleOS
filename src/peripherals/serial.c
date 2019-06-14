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

// HEADER
#include "serial.h"

// MY HEADERS
#include "usart.h"
#include "gpio.h"

int Serial_Init(uint32_t baudrate, int datalength)
{
    USART3->CR1 |= (USART_CR1_TXEIE | USART_CR1_RXNEIE);

    GPIO_Mode(GPIOD, 8, ALTERNATE);
    GPIO_Mode(GPIOD, 9, ALTERNATE);

    GPIO_AlternateMode(GPIOD, 8, 7);
    GPIO_AlternateMode(GPIOD, 9, 7);

    USART_Init(USART3, baudrate, datalength);

    return 1;
}

int PutChar(char c)
{
    while(!(USART3->ISR & USART_ISR_TXE));
    USART3->TDR = c & 0xFF;

    return 1;
}

char GetChar() {
    while(!(USART3->ISR & USART_ISR_RXNE));
    return USART3->RDR & 0xFF;
}

void USART3_IRQHandler(void)
{
    if (USART3->ISR & USART_ISR_RXFF) { // If interrupt was triggered by recieve
        // push character onto queue
        // disable rx interrupt
    } else if (USART3->ISR & USART_ISR_TXFE) { // If interrupted from transmitter
        // remove characters from queue to send
        // disable tx interrupt
    }
}
