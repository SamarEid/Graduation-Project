#ifndef __HAL_ULTRASONIC__
#define __HAL_ULTRASONIC__
typedef struct{
	GPIO_TypeDef* GPIOxTrigger;
	GPIO_TypeDef* GPIOxEcho;
	uint16_t GPIOxTriggerPin;
	uint16_t GPIOxEchoPin;
	TIM_TypeDef* TIMxTrigger;
	TIM_TypeDef* TIMxEcho;
	uint16_t TIMxTrigger_Channel;
	uint16_t TIMxEcho_Channel;
}ultraSonicInitTypeDef;
void ultraSonicVidInit(ultraSonicInitTypeDef*);
void ultraSonicVidStart(ultraSonicInitTypeDef*);
void ultraSonicInputCaptureHandler(TIM_TypeDef*,uint16_t*,uint16*t,float_t*);
float_t ultraSonicFloatGetDistance(uint16_t*,uint16t*);
#endif
