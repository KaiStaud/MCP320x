/*
 * MCP320N.h
 *
 *  Created on: 26.03.2021
 *      Author: kai-s
 */

#ifndef INC_MCP320N_H_
#define INC_MCP320N_H_
#include "stdint.h"
#include "main.h"


typedef struct
{
	uint16_t channels[4];
	SPI_HandleTypeDef* spi;
	GPIO_TypeDef* CS_Port;
	uint16_t CS_Pin;
}MCP320N;

void MCP320N_read(uint8_t channel,MCP320N* adc);

void MCP320N_DMA_read(uint8_t channel,MCP320N* adc);

void MCP320N_init(MCP320N* adc,GPIO_TypeDef* cs_port, uint8_t cs_pin,SPI_HandleTypeDef* spi_controller);


#endif /* INC_MCP320N_H_ */
