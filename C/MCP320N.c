/*
 * MCP320N.c
 *
 *  Created on: 26.03.2021
 *      Author: kai-s
 */

#include "MCP320N.h"
/*
 * @ brief: Reads single-sided input channel
 * @ param: Channel number
 * @ return: transmission error code
 */
HAL_StatusTypeDef MCP320N_read(uint8_t channel,MCP320N* adc)
{
	HAL_StatusTypeDef err;
	uint8_t txData[3] = {0x01,0xA0 | (channel << 6),0x00};
	uint8_t rxData[3] = {0x00,0x00,0x00};
	HAL_GPIO_WritePin(adc->CS_Port, adc->CS_Pin, GPIO_PIN_SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(adc->CS_Port, adc->CS_Pin, GPIO_PIN_RESET);
	err = HAL_SPI_TransmitReceive(adc->spi, txData, rxData, 3, 10);
	HAL_GPIO_WritePin(adc->CS_Port, adc->CS_Pin, GPIO_PIN_SET);
	adc->channels[channel] = (rxData[1]<<8 | rxData[2])&0x0FFF;
	return err;
}
/*
 * @ brief: Reads single-sided input channel in DMA mode
 * @ param: Channel number
 * @ return: transmission error code
 */
HAL_StatusTypeDef MCP320N_read_DMA(uint8_t channel,MCP320N* adc)
{
	uint8_t txData[3] = {0x01,0xA0 | (channel << 6),0x00};
	static uint8_t rxData[3] = {0x00,0x00,0x00};
	HAL_GPIO_WritePin(adc->CS_Port, adc->CS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(adc->CS_Port, adc->CS_Pin, GPIO_PIN_RESET);
	adc->channels[channel] = (rxData[1]<<8 | rxData[2])&0x0FFF;
	return HAL_SPI_TransmitReceive_DMA(adc->spi, txData, rxData, 3);
}
/*
 * @ brief: Initializes the ADC
 * @ param: Pointers to adc instance ,CS Port,CS Pin and SPI struct
 * @ param: Success (0), Error (0)
 */
void MCP320N_init(MCP320N* adc,GPIO_TypeDef* cs_port, uint8_t cs_pin,SPI_HandleTypeDef* spi_controller)
{
adc->CS_Pin = cs_pin;
adc->CS_Port = cs_port;
adc->spi = spi_controller;
}

