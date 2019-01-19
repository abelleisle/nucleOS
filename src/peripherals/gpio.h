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

#ifndef GPIO_H
#define GPIO_H

#include "stm32h7xx.h"

enum GPIO_MODE {
    MODE_RESET = 0,
    INPUT = 0,
    OUTPUT = 1,
    ALTERNATE = 2,
    ANALOG = 3
};

enum GPIO_TYPE {
    TYPE_RESET = 0,
    PUSH_PULL = 0,
    OPEN = 1
};

enum GPIO_SPEED {
    LOW = 0,
    MEDIUM = 1,
    HIGH = 2,
    VERY_HIGH = 3
};

enum GPIO_PUPDT {
    NO = 0,
    UP = 1,
    DOWN = 2
};

void GPIO_Init(void);

void GPIO_Type(GPIO_TypeDef* port, uint32_t pin, enum GPIO_TYPE type);

void GPIO_Mode(GPIO_TypeDef* port, uint32_t pin, enum GPIO_MODE mode);

void GPIO_Speed(GPIO_TypeDef* port, uint32_t pin, enum GPIO_SPEED speed);

void GPIO_PUPD(GPIO_TypeDef* port, uint32_t pin, enum GPIO_PUPDT pupd);

void GPIO_AlternateMode(GPIO_TypeDef* port, uint32_t pin, uint32_t mode);

void GPIO_SetValue(GPIO_TypeDef* port, uint32_t pin, uint32_t value);

void GPIO_SetPin(GPIO_TypeDef* port, uint32_t pin);

void GPIO_ResetPin(GPIO_TypeDef* port, uint32_t pin);

void GPIO_TogglePin(GPIO_TypeDef* port, uint32_t pin);

uint32_t GPIO_GetValue(GPIO_TypeDef* port, uint32_t pin);

#endif // GPIO_H
