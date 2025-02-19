/*
 * reception.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: ASHRY
 */
#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"
#include "../../../communication/communication.h"
#include "reception.h"

uint16_t receptionHalfWordReceiveCommand(){
	while(communicationCharGetTriggerPinValue() == RESET);
	communicationVidSelectSlave();
	while(SPI_I2S_GetFlagStatus(COMMUNICATION_SPI,SPI_I2S_FLAG_RXNE) != SET);
	uint16_t command = SPI_I2S_ReceiveData(COMMUNICATION_SPI);
	communicationVidDeselectSlave();
	return command;
}
