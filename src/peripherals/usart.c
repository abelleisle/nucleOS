/*
 * Copyright (C) 2018  Belle-Isle, Andrew <drumsetmonkey@gmail.com>
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

int _usart_data_length(int data_length)
{
    assert(data_length >= 7 && data_length <= 9);
    switch(data_length) {
        case 7: // M[1:0] = '00'
            break;
        case 8: // M[1:0] = '01'
            USART1->CR1 |= USART_CR1_M0;
            break;
        case 9: // M[1:0] = '10'
            USART1->CR1 |= USART_CR1_M0;
            USART1->CR1 |= USART_CR1_M1;
            break;
        default:;
    }

    return 0;
}

int init_usart(int data_length)
{
    _usart_data_length(data_length);

    USART1->CR1 |= (USART_CR1_TE | USART_CR1_RE);
    USART1->CR1 |= USART_CR1_UE;

    return 0;
}

