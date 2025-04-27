/*
 * communication.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: ASHRY
 */
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_spi.h"
#include "stm32f4xx_hal_dma.h"
#include "./communication.h"
#include "cmsis_os2.h"
SPI_HandleTypeDef hspi2 = {0};
osMutexId_t spiMutexHandle;
const osMutexAttr_t spiMutex_attributes = {
  .name = "spiMutex"
};
void communicationVidInit(){
	// initialize GPIO PINS to its alternate function
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin =  SS_PIN | SCLK_PIN | MISO_PIN | MOSI_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = SPI_ALTERNATE_FUNCTION;
	HAL_GPIO_Init(SPI_PORT, &GPIO_InitStruct);
	//congigure spi as slave
	hspi2.Instance = COMMUNICATION_SPI;
	hspi2.Init.Mode = SPI_MODE_SLAVE;
	hspi2.Init.Direction = SPI_DIRECTION_2LINES;
	hspi2.Init.DataSize = DATA_SIZE;
	hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi2.Init.NSS = SPI_NSS_HARD_INPUT;
	hspi2.Init.FirstBit = ENDIAN;
	hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi2.Init.CRCPolynomial = 10;
	HAL_SPI_Init(&hspi2);
	__HAL_SPI_ENABLE(&hspi2);
	spiMutexHandle = osMutexNew(&spiMutex_attributes);

}
