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

#ifndef SPI_H
#define SPI_H

#include "stm32h7xx.h"

/**
 * Initializes the given SPI port.
 * For now this function enables all SPI port clocks, then enables the port.
 * 
 * @param port The SPI port to initialize
 */
void SPI_Init(SPI_TypeDef* port);

/**
 * Sets the length of data to transmit over the SPI port.
 *
 * @param spi The SPI port to set this data on
 * @param length How many bits of data will be sent over SPI in each
 *  transmission. This value can be anything from 1-32
 */
void SPI_Set_DataLength(SPI_TypeDef* spi, uint32_t length);

/**
 * Tells how many packets should be used to send the data
 *
 * @param spi The SPI port to set the FIFO threshold on
 * @param length How many packets to use to send the data
 */
void SPI_Set_FIFO_Threshold(SPI_TypeDef* spi, uint32_t length);

/**
 * Sets the given SPI as a master
 *
 * @param spi The SPI port to set as the master.
 */
void SPI_Set_Master(SPI_TypeDef* spi);

/**
 * Sets the given SPI as a slave
 *
 * @param spi The SPI port to set as a slave.
 */
void SPI_Set_Slave(SPI_TypeDef* spi);

/**
 * Sends data over the given SPI port
 * This function uses polling to send data. It will stall until the current
 *  data transmission is finished and the data transmission bit is set.
 *
 * @param port The SPI port to send data over
 * @param data The data to send over SPI
 */
void SPI_Transmit(SPI_TypeDef* port, uint32_t data);

/**
 * Gets data from an SPI data receive register
 *
 * @param port The SPI port to pull received data from
 * @return Unsigned integer value recieved from the SPI master
 */
uint32_t SPI_Receive(SPI_TypeDef* port);

#endif // SPI_H
