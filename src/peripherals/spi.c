/*
 * @file spi.c
 * SPI library function bodies
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

#include "spi.h"

/********************
 * STATIC FUNCTIONS *
 ********************/

void _SPI_I2SDiv(SPI_TypeDef* spi, char div)
{
    spi->I2SCFGR &= ~(SPI_I2SCFGR_I2SDIV); // clear I2S DIV
    spi->I2SCFGR |= (div << SPI_I2SCFGR_I2SDIV_Pos); //set I2S to div
}

void _SPI_I2S_ODD(SPI_TypeDef* spi, uint32_t val)
{
    if (val)
        spi->I2SCFGR |= SPI_I2SCFGR_ODD; // set ODD high
    else
        spi->I2SCFGR &= ~(SPI_I2SCFGR_ODD); // clear ODD

}

void _SPI_I2S_MCKOE(SPI_TypeDef* spi, uint32_t val)
{
    if (val)
        spi->I2SCFGR |= SPI_I2SCFGR_MCKOE; // set MCKOE
    else
        spi->I2SCFGR &= ~(SPI_I2SCFGR_MCKOE); // clear MCKOE
}

/********************
 * PUBLIC FUNCTIONS *
 ********************/

void SPI_Set_DataLength(SPI_TypeDef* spi, uint32_t length)
{
    spi->CFG1 &= ~(31); // clear DSIZE
    spi->CFG1 |= ((length-1) & 31); // set DSIZE
}

void SPI_Set_Master(SPI_TypeDef* spi)
{
    spi->CFG2 |= SPI_CFG2_MASTER;
}

void SPI_Set_Slave(SPI_TypeDef* spi)
{
    spi->CFG2 &= ~(SPI_CFG2_MASTER);
}

void SPI_Set_FIFO_Threshold(SPI_TypeDef* spi, uint32_t length)
{
    spi->CFG1 &= ~(SPI_CFG1_FTHLV);
    spi->CFG1 |= ((length-1) << SPI_CFG1_FTHLV_Pos);
}

void SPI_Init(SPI_TypeDef* spi)
{
    // TODO make a function for this/come up with a better system
    //  for now we will assume it's not set (VERY BAD)
    //spi->CR1 &= ~SPI_CR1_SPE; // disable SPI to set registers

    /* Enable SPI clocks */
    RCC->APB2ENR |= RCC_APB1LENR_SPI2EN & 
                    RCC_APB1LENR_SPI3EN &
                    RCC_APB2ENR_SPI1EN  &
                    RCC_APB2ENR_SPI4EN  &
                    RCC_APB2ENR_SPI5EN  &
                    RCC_APB4ENR_SPI6EN  ;

    spi->CR1 |= SPI_CR1_SPE; // disable SPI to set registers
}


void SPI_Transmit(SPI_TypeDef* spi, uint32_t data)
{
    // wait for transmission to be complete
    while(!(spi->SR & SPI_SR_TXC) && !(spi->SR & SPI_SR_TXP));
    spi->TXDR = data;
}

uint32_t SPI_Receive(SPI_TypeDef* spi)
{
    // wait for recieve to be ready
    while(!(spi->SR & SPI_SR_RXP));
    return spi->RXDR;
}
