/*
 * MCP3202.h
 *
 *  Created on: Apr 2, 2021
 *      Author: kai staud
 */

#ifndef INC_MCP320N_MCP3202_H_
#define INC_MCP320N_MCP3202_H_

#include "stdint.h"
#include "main.h"

namespace MCP320X {

class MCP3202 {

private:
	SPI_HandleTypeDef* spi;
	GPIO_TypeDef* CS_Port;
	uint16_t CS_Pin;
	uint8_t txData[3] = {0x01,0xA0,0x00};
	uint8_t rxData[3] = {0x00,0x00,0x00};
	uint16_t channels[2] = {0xFFFF,0xFFFF}; // start with invalid readout!
	HAL_StatusTypeDef err;
public:
	MCP3202();
	uint8_t Init(GPIO_TypeDef* cs_port, uint8_t cs_pin,SPI_HandleTypeDef* spi_controller);
	uint16_t Read(uint8_t channel);
	HAL_StatusTypeDef Read_DMA(uint8_t channel);
	uint16_t Get_Channel(uint8_t channel);
};

} /* namespace MCP320X */

#endif /* INC_MCP320N_MCP3202_H_ */
