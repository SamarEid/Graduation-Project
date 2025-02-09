/*
 * app.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ASHRY
 */

#ifndef PERCEPTION_APP_APP_H_
#define PERCEPTION_APP_APP_H_

void perceptionVidRCCInit(void);
void perceptionVidCheckOverFlowTask(void*pvParameters);
void perceptionVidSendSensorsDataTask(void*pvParameters);
void perceptionVidInit(void);
void perceptionVidBegin(void);

#endif /* PERCEPTION_APP_APP_H_ */
