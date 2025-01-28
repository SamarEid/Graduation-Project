/*
 * serialization.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: ASHRY
 */
#include <stdint.h>
#include "../../typesDefinition/types.h"
#include "./serialization.h"
uint16_t* serializeSensorData(sensorTypeDef* sensorData){
	uint16_t* serializedData = (uint16_t*) sensorData;
	return serializedData;
}
