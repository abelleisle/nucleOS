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

#include "usart.h"
#include "assert.h"
#include "system_stm32h7xx.h"

int _usart_data_length(USART_TypeDef *usart, int data_length)
{
    assert(data_length >= 7 && data_length <= 9);
    switch(data_length) {
        case 7: // M[1:0] = '00'
            break;
        case 8: // M[1:0] = '01'
            usart->CR1 |= USART_CR1_M0;
            break;
        case 9: // M[1:0] = '10'
            usart->CR1 |= USART_CR1_M0;
            usart->CR1 |= USART_CR1_M1;
            break;
        default:;
    }

    return 0;
}

int init_usart(USART_TypeDef *usart, int data_length)
{
    _usart_data_length(usart, data_length);

    GPIO_Mode(GPIOD, 8, ALTERNATE)
    GPIO_Mode(GPIOD, 9, ALTERNATE)

    GPIO_AlternativeMode(GPIOD, 8, 7);
    GPIO_AlternativeMode(GPIOD, 9, 7);

    //usart->BRR = 0x0341h;
	RCC->APB1LENR |= RCC_APB1LENR_USART3EN;
    usart->BRR = 64000000U/9600U;

    usart->CR1 |= (USART_CR1_TE | USART_CR1_RE); // enable rx and tx

    //usart->CR2 |= USART_CR2_ABREN; // enable auto baud rate detection

    usart->CR1 |= USART_CR1_UE; // enable usart

    return 0;
}

int PutChar(USART_TypeDef *usart, char c)
{
    while(!(usart->ISR & USART_ISR_TXE));
    usart->TDR = c & 0xFF;

    return 1;
}
