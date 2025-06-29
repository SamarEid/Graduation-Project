/*
 * serialization.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: ASHRY
 */
#include <stdint.h>
#include "../typesdefinition/typedefinitions.h"
#include "./serialization.h"
uint8_t* serializeSensorData(sensorTypeDef* sensorData){
	uint8_t* serializedData = (uint8_t*) sensorData;
	return serializedData;
}
