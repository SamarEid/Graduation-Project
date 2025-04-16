/*
 * motor.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: ASHRY
 */
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_tim.h"
#include "./motor.h"

void motorVidinit(motorInitTypeDef*motor){
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};
    /*
     * init GPIO PINS
     * IN1 PIN as output and reset it
    */
    GPIO_InitStruct.Pin = motor->in1GPIOxPin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(motor->in1GPIOx, &GPIO_InitStruct);
    HAL_GPIO_WritePin(motor->in1GPIOx,motor->in1GPIOxPin , GPIO_PIN_RESET);
    // IN2 PIN as output and reset it
    GPIO_InitStruct.Pin = motor->in2GPIOxPin;
    HAL_GPIO_Init(motor->in2GPIOx, &GPIO_InitStruct);
    HAL_GPIO_WritePin(motor->in2GPIOx,motor->in2GPIOxPin , GPIO_PIN_RESET);
    // EN pin to its alternate function
    GPIO_InitStruct.Pin = motor->enGPIOxPin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = motor->GPIOEnPinAF;
    HAL_GPIO_Init(motor->enGPIOx, &GPIO_InitStruct);

    // Timer Base for PWM (enable)
    motor->htim->Instance = motor->TIMxEnable;
    motor->htim->Init.Prescaler = SET_PSC();
    motor->htim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    motor->htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    motor->htim->Init.CounterMode  = TIM_COUNTERMODE_UP;
    motor->htim->Init.Period = RESET_VALUE;
    HAL_TIM_PWM_Init(motor->htim);

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = SET_ARR(HANDLE_FAULT_MOTOR_RPM_SPEED);
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(motor->htim, &sConfigOC, motor->TIMxEnableChannel);
}
void motorVidStart(motorInitTypeDef*motor, uint8_t motorSpeed,direction motorDirection){
	// set direction
	motorVidSetMotorDirection(motor, motorDirection);
	//set speed
	motorVidSetSpeed(motor, motorSpeed);
	// enable TIMER
	HAL_TIM_PWM_Start(motor->htim,motor->TIMxEnableChannel);
}
void motorVidSetSpeed(motorInitTypeDef*motor, uint8_t motorSpeed){
	if(motorSpeed <= MAXIMUM_MOTOR_RPM_SPEED){
		__HAL_TIM_SET_AUTORELOAD(motor->htim,SET_ARR(motorSpeed) );
	}else{
		__HAL_TIM_SET_AUTORELOAD(motor->htim,SET_ARR(HANDLE_FAULT_MOTOR_RPM_SPEED) );
	}
}
void motorVidSetMotorDirection(motorInitTypeDef*motor,direction motorDirection){
	//reset bit first the control direction
	HAL_GPIO_WritePin(motor->in1GPIOx, motor->in1GPIOxPin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(motor->in2GPIOx, motor->in2GPIOxPin, GPIO_PIN_RESET);

	while(HAL_GPIO_ReadPin(motor->in1GPIOx, motor->in1GPIOxPin) || HAL_GPIO_ReadPin(motor->in2GPIOx, motor->in2GPIOxPin));
	if(motorDirection == CW){
		HAL_GPIO_WritePin(motor->in1GPIOx, motor->in1GPIOxPin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(motor->in2GPIOx, motor->in2GPIOxPin, GPIO_PIN_RESET);
	}else if(motorDirection == CCW){
		HAL_GPIO_WritePin(motor->in1GPIOx, motor->in1GPIOxPin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(motor->in2GPIOx, motor->in2GPIOxPin, GPIO_PIN_SET);
	}
}
void motorVidStop(motorInitTypeDef*motor){
	HAL_GPIO_WritePin(motor->in1GPIOx, motor->in1GPIOxPin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(motor->in2GPIOx, motor->in2GPIOxPin, GPIO_PIN_RESET);
	HAL_TIM_PWM_Stop(motor->htim, motor->TIMxEnableChannel);

}
