/*
 * motor.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: ASHRY
 */
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "../../../utils/utils.h"
#include "./motor.h"

void motorVidinit(motorInitTypeDef*motor){
	//variables declaration
    GPIO_InitTypeDef gpioPinInitStructure;
    TIM_TimeBaseInitTypeDef timerBaseInitStructure;
    TIM_OCInitTypeDef timerOCInitStruct;
    static void(*TIMOCFunctions[])(TIM_TypeDef*, TIM_OCInitTypeDef*) = {TIM_OC1Init,TIM_OC2Init,TIM_OC3Init,TIM_OC4Init};
    /*
     * init GPIO PINS
     * IN1 PIN as output and reset it
    */
    gpioPinInitStructure.GPIO_Pin = motor->in1GPIOxPin;
    gpioPinInitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    gpioPinInitStructure.GPIO_Mode = GPIO_Mode_OUT;
    gpioPinInitStructure.GPIO_OType = GPIO_OType_PP;
    gpioPinInitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(motor->in1GPIOx , &gpioPinInitStructure );
    GPIO_ResetBits(motor->in1GPIOx,motor->in1GPIOxPin);
    // IN2 PIN as output and reset it
    gpioPinInitStructure.GPIO_Pin = motor->in2GPIOxPin;
    GPIO_Init(motor->in2GPIOx , &gpioPinInitStructure );
    GPIO_ResetBits(motor->in2GPIOx,motor->in2GPIOxPin);
    // EN as AF
    gpioPinInitStructure.GPIO_Pin = motor->enGPIOxPin;
    gpioPinInitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(motor->enGPIOx , &gpioPinInitStructure );
    GPIO_PinAFConfig(motor->enGPIOx,PinSource(motor->enGPIOxPin),motor->GPIOEnPinAF);
    // init basic timer
    timerBaseInitStructure.TIM_Period = RESET_VALUE ;
    timerBaseInitStructure.TIM_Prescaler = SET_PSC();
    timerBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    timerBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(motor->TIMxEnable, &timerBaseInitStructure);
    // init Output Compare Timer
    timerOCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    timerOCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    timerOCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    timerOCInitStruct.TIM_Pulse = SET_ARR(HANDLE_FAULT_MOTOR_RPM_SPEED);
    TIMOCFunctions[GET_OC_INDEX(motor->TIMxEnableChannel)](motor->TIMxEnable, &timerOCInitStruct);
    TIM_ARRPreloadConfig(motor->TIMxEnable,ENABLE);
}
void motorVidStart(motorInitTypeDef*motor, uint8_t motorSpeed,direction motorDirection){
	// set direction
	motorVidSetMotorDirection(motor, motorDirection);
	//set speed
	motorVidSetSpeed(motor, motorSpeed);
	// enable TIMER
	TIM_CtrlPWMOutputs(motor->TIMxEnable, ENABLE);
	TIM_Cmd(motor->TIMxEnable, ENABLE);
}
void motorVidSetSpeed(motorInitTypeDef*motor, uint8_t motorSpeed){
	if(motorSpeed <= 97){
		TIM_SetAutoreload(motor->TIMxEnable, SET_ARR(motorSpeed) );
	}else{
		TIM_SetAutoreload(motor->TIMxEnable, SET_ARR(HANDLE_FAULT_MOTOR_RPM_SPEED) );
	}
}
void motorVidSetMotorDirection(motorInitTypeDef*motor,direction motorDirection){
	//reset bit first the control direction
	GPIO_ResetBits(motor->in1GPIOx, motor->in1GPIOxPin);
	GPIO_ResetBits(motor->in2GPIOx, motor->in2GPIOxPin);
	while(GPIO_ReadOutputDataBit(motor->in1GPIOx, motor->in1GPIOxPin) && GPIO_ReadOutputDataBit(motor->in2GPIOx, motor->in2GPIOxPin));
	if(motorDirection == CW){
		GPIO_SetBits(motor->in1GPIOx, motor->in1GPIOxPin);
		GPIO_ResetBits(motor->in2GPIOx, motor->in2GPIOxPin);
	}else if(motorDirection == CCW){
		GPIO_SetBits(motor->in2GPIOx, motor->in2GPIOxPin);
		GPIO_ResetBits(motor->in1GPIOx, motor->in1GPIOxPin);
	}
}
void motorVidStop(motorInitTypeDef*motor){
	GPIO_ResetBits(motor->in1GPIOx, motor->in1GPIOxPin);
	GPIO_ResetBits(motor->in2GPIOx, motor->in2GPIOxPin);
	TIM_Cmd(motor->TIMxEnable, DISABLE);
}
