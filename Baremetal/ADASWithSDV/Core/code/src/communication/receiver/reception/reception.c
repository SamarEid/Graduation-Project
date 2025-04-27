/*
 * reception.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: ASHRY
 */
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_spi.h"
#include "../../communication.h"
#include "./reception.h"
extern SPI_HandleTypeDef hspi2 ;
uint8_t checkValidityFrame = {START_FRAME,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,END_FRAME};
void receptionVidReceiveCommand(uint8_t*command){
	HAL_SPI_TransmitReceive(&hspi2, checkValidityFrame, command, FRAME_SIZE, HAL_MAX_DELAY);
}
