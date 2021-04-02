# MCP320x
The repository supplies a C and C++ Library for uning Microchip SAR-ADCs (MCP3202,MCP3204  etc.)
with STM32 Microcontrollers. The libs are developed using STM32 HAL-Libraries, therefore an HAL-Setup is necessary
for using them.
The librarys provide the channel readout ranging from 0 = 0V to 0xFFE = VCC allowing different supply voltages to be easily used with 
the library. 5V Supply can be used when connecting the ADC to 5V tolerant MCU SPI Pins.

# C -How to use the library?
## Setting up the MCUs peripherals:
Before using the libray the following peripherals need to be enabled:
- One GPIO Pin attached to the ADC's CS Pin
- A SPI Peripheral configured as Full-Duplex Master.
- Optional: SPI RX DMA for streaming data between the ADC and CPU

## Using the library in your project
After creating initializing a spi port in your project, use the Init-Function to initialize the ADC. The library supports sampling data
via polling or DMA mode. If you are using the DMA functions, the callback functions needs to be implemented in your source code.
```
/* USER CODE BEGIN Includes */
#include "MCP320N.h"
/* USER CODE END Includes */
/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi2;
/* USER CODE BEGIN PV */
MCP320N adc;
/* USER CODE END 0 */
...
int main(void)
{
...
/* USER CODE BEGIN 2 */
  MCP320N_init(&adc, MCP320X_CS_GPIO_Port, MCP320X_CS_Pin, &hspi2);
  MCP320N_read(0,&adc);
  MCP320N_read_DMA(0, &adc); // change to any channel between 0-3
  /* USER CODE END 2 */
...
}
...
/* USER CODE BEGIN 4 */
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
MCP320N_read_DMA(1, &adc);
}

/* USER CODE END 4 */
```
# C++: Using the library
Development in progress...
