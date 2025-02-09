/*
 * ultraSonic.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ASHRY
 */
#ifndef PERCEPTION_HAL_ULTRASONIC_H_
#define PERCEPTION_HAL_ULTRASONIC_H_

#define SOUND_SPEED  				(uint8_t)340
#define TIMER_FREQUENCY 			84000000 			//84 MHz
#define TRIGGER_FREQUENCY 			25		 			//25Hz
#define TICK_FREQUENCY 				1000000  			//1MHz
#define PWM_HIGH_TIME				0.00001	 			//10us
#define PWM_FULL_TIME				0.04     			//40ms
#define DIGITAL_FILTER				0x0
#define FIRST_CAPTURE				(uint8_t)0
#define SECOND_CAPTURE				(uint8_t)1
#define CLOCK_DIVISON				TIM_CKD_DIV1
#define TRIGGER_CHANNEL_1 			TIM_Channel_1
#define TRIGGER_CHANNEL_2 			TIM_Channel_2
#define TRIGGER_CHANNEL_3 			TIM_Channel_3
#define TRIGGER_CHANNEL_4 			TIM_Channel_4
#define ECHO_CHANNEL 				TIM_Channel_1
#define IT_CC_CHANNEL				TIM_IT_CC1
#define GET_PSC()					(uint16_t)(((TIMER_FREQUENCY)/(TICK_FREQUENCY))-1)
#define GET_ARR()   				(uint32_t)(((PWM_HIGH_TIME)*(TICK_FREQUENCY))-1)
#define GET_RESET_VALUE()			(uint32_t)(((PWM_FULL_TIME)*(TICK_FREQUENCY))-1)
#define GET_OC_INDEX(channel)		(channel/4)
typedef struct{
	GPIO_TypeDef* GPIOxTrigger;
	GPIO_TypeDef* GPIOxEcho;
	TIM_TypeDef*  TIMxTrigger;
	TIM_TypeDef*  TIMxEcho;
	uint32_t GPIOxTriggerPin;
	uint32_t GPIOxEchoPin;
	uint8_t  GPIOxTriggerPinAF;
	uint8_t  GPIOxEchoPinAF;
	uint16_t TIMxTrigger_Channel;
	IRQn_Type EchoIRQ;
}ultraSonicInitTypeDef;
void ultraSonicVidInit(ultraSonicInitTypeDef*);
void ultraSonicVidStart(ultraSonicInitTypeDef*);
void ultraSonicInputCaptureHandler(TIM_TypeDef*,uint32_t*,uint32_t*,float*,uint8_t*);
float ultraSonicFloatGetDistance(uint32_t*,uint32_t*);
void ultraSonicCheckOverFlow(TIM_TypeDef* , uint8_t*);

#endif /* PERCEPTION_HAL_ULTRASONIC_H_ */
