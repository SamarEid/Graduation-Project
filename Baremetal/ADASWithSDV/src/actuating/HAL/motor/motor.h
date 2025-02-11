/*
 * motor.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ASHRY
 */

#ifndef ACTUATING_HAL_MOTOR_MOTOR_H_
#define ACTUATING_HAL_MOTOR_MOTOR_H_

#define TIMER_FREQ                     84000000   // 84 MHz Timer Frequency
#define TICK_FREQ                      1000000    // 1 MHz Base Tick Frequency
#define MAXIMUM_MOTOR_RPM_SPEED        97
#define HANDLE_FAULT_MOTOR_RPM_SPEED   10
#define MAXIMUM_COUNT_NUMBER           0xFFFF     // 16-bit timer max value
#define PWM_FREQ                       1000       // 1 kHz PWM frequency

// Compute Reset Value
#define RESET_VALUE                    ((TICK_FREQ / PWM_FREQ) - 1)

// Compute ARR dynamically based on speed
#define SET_ARR(SPEED)                  ((uint32_t)( ((float)(SPEED) / MAXIMUM_MOTOR_RPM_SPEED) * RESET_VALUE))

// Compute PSC to set the base tick frequency (TICK_FREQ)
#define SET_PSC()                        ((uint16_t)((TIMER_FREQ / TICK_FREQ) - 1))

typedef struct {
	GPIO_TypeDef* in1GPIOx;
	uint32_t in1GPIOxPin;
	GPIO_TypeDef* in2GPIOx;
	uint32_t in2GPIOxPin;
	GPIO_TypeDef* enGPIOx;
	uint32_t enGPIOxPin;
	TIM_TypeDef* TIMxEnable;
	uint16_t TIMxEnableChannel;
	uint8_t	GPIOEnPinAF;
}motorInitTypeDef;
typedef enum{
	CW,
	CCW
}direction;
void motorVidinit(motorInitTypeDef*);
void motorVidStart(motorInitTypeDef*, uint8_t,direction);
void motorVidSetSpeed(motorInitTypeDef*, uint8_t );
void motorVidSetMotorDirection(motorInitTypeDef*,direction);
void motorVidStop(motorInitTypeDef*);
#endif /* ACTUATING_HAL_MOTOR_MOTOR_H_ */
