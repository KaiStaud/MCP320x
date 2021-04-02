/*
 * MCP3202.cpp
 *
 *  Created on: Apr 2, 2021
 *      Author: kai staud
 */

#include <MCP320N/MCP3202.h>

namespace MCP320X {

MCP3202::MCP3202() {

}
/*
 * @ brief: Initializes the ADC
 * @ param: Pointers to CS Port,CS Pin and SPI struct
 * @ param: Success (0), Error (0)
 */
uint8_t MCP3202::Init(GPIO_TypeDef* cs_port, uint8_t cs_pin,SPI_HandleTypeDef* spi_controller)
{
	CS_Pin = cs_pin;
	CS_Port = cs_port;
	spi = spi_controller;
	return 0;
}
/*
 * @ brief: Reads single-sided input channel
 * @ param: Channel number
 * @ return: Channel readout in LSB fullscale
 */
uint16_t MCP3202::Read(uint8_t channel)
{
	txData[2] = 0xA0 | (channel << 6);
	HAL_GPIO_WritePin(CS_Port, CS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(CS_Port, CS_Pin, GPIO_PIN_RESET);
	err = HAL_SPI_TransmitReceive(spi, txData, rxData, 3, 10);
	HAL_GPIO_WritePin(CS_Port, CS_Pin, GPIO_PIN_SET);
	channels[channel] = (rxData[1]<<8 | rxData[2])&0x0FFF;
	if(err != 0)
	{
		return err <<14; // error doesn't appear as valid readout,since ADC is 12 bit!
	}
	else
		return channels[channel];
}
/*
 * @ brief: Reads single-sided input channel in DMA mode
 * @ param: Channel number
 * @ return: Error code
 */
HAL_StatusTypeDef MCP3202::Read_DMA(uint8_t channel)
{
	txData[2] = 0xA0 | (channel << 6);
	HAL_GPIO_WritePin(CS_Port, CS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(CS_Port, CS_Pin, GPIO_PIN_RESET);
	channels[channel] = (rxData[1]<<8 | rxData[2])&0x0FFF;
	return HAL_SPI_TransmitReceive_DMA(spi, txData, rxData, 3);
}
/*
 * @ brief: Returns channel readout
 * @ param: channel number
 * @ return: channel readout
 */
uint16_t MCP3202::Get_Channel(uint8_t channel)
{
	return channels[channel];
}

} /* namespace MCP320X */
