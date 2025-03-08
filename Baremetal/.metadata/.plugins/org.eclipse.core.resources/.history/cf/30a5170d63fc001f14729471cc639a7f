/*
 * trnsmission.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: ASHRY
 */
#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"
#include "../../typesDefinition/types.h"
#include "../formatter/serialization.h"
#include "./transmission.h"
#include "../../../communication/communication.h"


void transmissionVidSendSensorData(sensorTypeDef*sensorData){
	uint16_t* serialData = serializeSensorData(sensorData);
	communicationVidSelectSlave();
	for(int i = 0 ; i < sizeof(sensorTypeDef)/sizeof(uint16_t) ; i++){
		SPI_I2S_SendData(TRANSMISSION_PERIPHERAL , *(serialData + i));
	}
	communicationVidDeselectSlave();
}

