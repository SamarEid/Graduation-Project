/*
 * app.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ASHRY
 */

#ifndef ACTUATING_APP_APP_H_
#define ACTUATING_APP_APP_H_

#define INITIAL_SPEED 		30
typedef enum {
	START,
	FORWARD,
	REVERSE,
	TURNRIGHT,
	TURNLEFT,
	STOP
}commands;

void actuatingVidRCCInit(void);
void actuatingVidInit(void);
void actuatingVidExecuteCommandTask(void*pvParameters);
void actuatingVidBegin(void);
#endif /* ACTUATING_APP_APP_H_ */
