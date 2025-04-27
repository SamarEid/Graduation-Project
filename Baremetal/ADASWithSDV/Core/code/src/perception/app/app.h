/*
 * app.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ASHRY
 */

#ifndef PERCEPTION_APP_APP_H_
#define PERCEPTION_APP_APP_H_

void sendDataToQueue(uint32_t, float);
void perceptionVidTriggerSensorsTask(void* pvParameters);
//void perceptionVidCheckOverFlowTask(void*pvParameters);
void perceptionVidSendSensorDataTask(void* pvParameters);
void perceptionVidInit(void);
void perceptionVidBegin(void);

#endif /* PERCEPTION_APP_APP_H_ */
