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

/**
 * Mode selector for a GPIO pin. The integers are used to set the mode in
 *  binary in the GPIO control registers.
 */
enum GPIO_MODE {
    MODE_RESET = 0, /**< Resets the GPIO pin to default state (input) */
    INPUT = 0,      /**< Sets the GPIO pin to input mode (default) */
    OUTPUT = 1,     /**< Sets the GPIO pin to output mode */
    ALTERNATE = 2,  /**< Allows the GPIO pin to get used for other things */
    ANALOG = 3      /**< Sets the GPIO pin to analog mode */
};

/**
 * Sets the type of a GPIO pin.
 */
enum GPIO_TYPE {
    TYPE_RESET = 0, /**< Resets the pin to default type (push/pull) */
    PUSH_PULL = 0,  /**< Sets the pin to push/pull mode. */
    OPEN_DRAIN = 1  /**< Sets pin to open/drain mode. */
};

/**
 * Sets the speed of a GPIO pin.
 */
enum GPIO_SPEED {
    LOW = 0,        /**< Low speed */
    MEDIUM = 1,     /**< Medium speed */
    HIGH = 2,       /**< High speed */
    VERY_HIGH = 3   /**< Very high speed */
};

/**
 * Pull up or pull down resistor modes for GPIO pins.
 */
enum GPIO_PUPDR {
    NO = 0,         /**< No pull-up/pull-down resistor */
    UP = 1,         /**< Pull-up resistor */
    DOWN = 2        /**< Pull-down resistor */
};

/**
 * Initializes all the GPIO clocks for all GPIO ports.
 * (Ports A through K)
 */
void GPIO_Init(void);

/**
 * Sets the type of a certain GPIO pin.
 *
 * @param port The GPIO port that this pin belongs to.
 * @param pin The specific pin in our port that will be modified.
 * @param type What type this pin will be set to.
 * @see GPIO_TYPE
 */
void GPIO_Type(GPIO_TypeDef* port, uint32_t pin, enum GPIO_TYPE type);

/**
 * Sets the mode of a particular GPIO pin.
 *
 * @param port The GPIO port that this pin belongs to.
 * @param pin The specific pin in our port that will be modified.
 * @param mode The mode this specific pin will be set to.
 * @see GPIO_MODE
 */
void GPIO_Mode(GPIO_TypeDef* port, uint32_t pin, enum GPIO_MODE mode);

/**
 * Sets the speed of a certain GPIO pin.
 *  STM standard lets this pin either be: low, medium, high, or very high speed.
 *
 * @param port The GPIO port that this pin belongs to.
 * @param pin The specific pin in our port that will be modified.
 * @param speed What speed to set this pin too
 * @see GPIO_SPEED
 */
void GPIO_Speed(GPIO_TypeDef* port, uint32_t pin, enum GPIO_SPEED speed);

/**
 * Sets the pull up or pull down resistor for a certain GPIO pin.
 *  Every GPIO pin has a pull-up and pull-down resistor attached, and this
 *  function lets us either set or unset one of these resistors.
 *
 * @param port The GPIO port that this pin belongs to.
 * @param pin The specific pin in our port that will be modified.
 * @param pupd What resistor mode to set the pin to.
 * @see GPIO_PUPDT
 */
void GPIO_PUPD(GPIO_TypeDef* port, uint32_t pin, enum GPIO_PUPDR pupd);

/**
 * Sets an alternate mode for a GPIO pin.
 *  GPIO pins have alternate modes. These modes allow external devices on the
 *  chip to control the pin. This is what allows these pins to be used for
 *  things like serial over USART, or SPI.
 *
 * @param port The GPIO port that this pin belongs to.
 * @param pin The specific pin in our port that will be modified.
 * @param mode What alternative mode to set each pin to.
 *  The pins have 16 differenet modes that can be set, so this has to be a value
 *  of 0-15. Every pin has different specs for what its alternate functions
 *  can be, so the STM documentation for each chip should be checked to find
 *  the mode for this pin.
 */
void GPIO_AlternateMode(GPIO_TypeDef* port, uint32_t pin, uint32_t mode);

/**
 * Set the output value of a certain GPIO pin.
 *
 * @param port The GPIO port that this pin belongs to.
 * @param pin The specific pin in our port that will be modified.
 * @param value The value the pin will be set to. A value of zero won't set
 *  the pin voltage, and anything but zero will set the pin voltage.
 */
void GPIO_SetValue(GPIO_TypeDef* port, uint32_t pin, uint32_t value);

/**
 * Sets a certain GPIO pin voltage to high.
 *
 * @param port The GPIO port that this pin belongs to.
 * @param pin The specific pin in our port that will be modified.
 * @see GPIO_SetValue()
 */
void GPIO_SetPin(GPIO_TypeDef* port, uint32_t pin);

/**
 * Sets a certain GPIO pin voltage to low.
 *
 * @param port The GPIO port that this pin belongs to.
 * @param pin The specific pin in our port that will be modified.
 * @see GPIO_SetValue()
 */
void GPIO_ResetPin(GPIO_TypeDef* port, uint32_t pin);

/**
 * Flips the output of a certain GPIO pin.
 *
 * @param port The GPIO port that this pin belongs to.
 * @param pin The specific pin in our port that will be modified.
 * @see GPIO_SetValue()
 */
void GPIO_TogglePin(GPIO_TypeDef* port, uint32_t pin);

/**
 * Reads the value from a given GPIO pin.
 *
 * @param port The GPIO port that this pin belongs to.
 * @param pin The specific pin in our port that will be modified.
 * @return uint32_t Returns 1 if the pin is high and 0 if the pin is low.
 */
uint32_t GPIO_GetValue(GPIO_TypeDef* port, uint32_t pin);

#endif // GPIO_H
