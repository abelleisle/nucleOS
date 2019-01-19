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

#include "gpio.h"


void GPIO_Init(void)
{
    RCC->AHB4ENR |= 0x7FF; // enable all GPIO from A - K
}

void GPIO_Type(GPIO_TypeDef* port, uint32_t pin, enum GPIO_TYPE type)
{
    port->OTYPER &= ~(1 << pin);
    port->OTYPER |= type << pin;
}

void GPIO_Mode(GPIO_TypeDef* port, uint32_t pin, enum GPIO_MODE mode) 
{
    port->MODER &= ~(3 << (2 * pin)); // clears the GPIO pin
    port->MODER |= mode << (2 * pin); // sets GPIO pin mode
}

void GPIO_Speed(GPIO_TypeDef* port, uint32_t pin, enum GPIO_SPEED speed)
{
    port->OSPEEDR &= ~(3 << (2 * pin));
    port->OSPEEDR |= speed << (2 * pin);
}

void GPIO_PUPD(GPIO_TypeDef* port, uint32_t pin, enum GPIO_PUPDR pupd)
{
    port->PUPDR &= ~(3 << (2 * pin));
    port->PUPDR |= pupd << (2 * pin);
}

void GPIO_AlternateMode(GPIO_TypeDef* port, uint32_t pin, uint32_t mode)
{
    /*
     * Pins 0-7 use AFRL and pins 8-15 use AFRH.
     * By dividing the pin by 8 we can get 0 for 0-7 and 1 for 8-15.
     *  This will give the selection value for either AFRL or AFRH
     */
    port->AFR[pin/8] &= ~(0xF << (pin % 8));
    port->AFR[pin/8] |= mode << (pin % 8);
}

void GPIO_SetValue(GPIO_TypeDef* port, uint32_t pin, uint32_t value)
{
    if (value)  // setting the value
        GPIO_SetPin(port, pin);
    else        // resetting the pin
        GPIO_ResetPin(port, pin);
}

void GPIO_SetPin(GPIO_TypeDef* port, uint32_t pin)
{
    port->BSRRL |= (1 << pin); // BSRRL is for setting pins
}

void GPIO_ResetPin(GPIO_TypeDef* port, uint32_t pin)
{
    port->BSRRH |= (1 << pin); // BSRRH is for resetting pins
}

void GPIO_TogglePin(GPIO_TypeDef* port, uint32_t pin)
{
    uint32_t val = GPIO_GetValue(port, pin);
    GPIO_SetValue(port, pin, !val); // flip current value
}

uint32_t GPIO_GetValue(GPIO_TypeDef* port, uint32_t pin)
{
    return port->IDR & (1 << pin);
}
