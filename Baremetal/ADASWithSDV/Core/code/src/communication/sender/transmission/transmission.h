/*
 * transmission.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ASHRY
 */

#ifndef COMMUNICATION_SENDER_TRANSMISSION_TRANSMISSION_H_
#define COMMUNICATION_SENDER_TRANSMISSION_TRANSMISSION_H_


#define SENSOR_DATA_SIZE 			8
void transmissionVidSendSensorData(sensorTypeDef*);
void transmissionVidSendSingleValue(uint8_t value);
void transmissionVidSendStart();
void transmissionVidSendEnd();
#endif /* COMMUNICATION_SENDER_TRANSMISSION_TRANSMISSION_H_ */
