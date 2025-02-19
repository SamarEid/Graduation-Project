/*
 * communication.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ASHRY
 */

#ifndef COMMUNICATION_COMMUNICATION_H_
#define COMMUNICATION_COMMUNICATION_H_

#define COMMUNICATION_SPI 			SPI2
#define SPI_PORT         			GPIOB
#define SPI_ALTERNATE_FUNCTION		GPIO_AF_SPI2
#define MOSI_PIN 					GPIO_Pin_15
#define MISO_PIN					GPIO_Pin_14
#define SCLK_PIN 					GPIO_Pin_13
#define SS_PIN						GPIO_Pin_12
#define TRIGGER_PIN					GPIO_Pin_5
#define DATA_SIZE					SPI_DataSize_16b
#define BAUD_RATE_PRESCALER			SPI_BaudRatePrescaler_2
#define ENDIAN						SPI_FirstBit_MSB

void communicationVidInit();
void communicationVidSelectSlave();
void communicationVidDeselectSlave();
uint8_t communicationCharGetTriggerPinValue();
#endif /* COMMUNICATION_COMMUNICATION_H_ */
