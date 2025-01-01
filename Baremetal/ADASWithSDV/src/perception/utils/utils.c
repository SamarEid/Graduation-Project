#include <stdint.h>
#include "stm32f4xx.h"
#include "./utils.h"
uint8_t PinSource(uint32_t pin) {
    uint8_t pinSource = 0;
    while (pin >>= 1  )
    	pinSource++;
    return pinSource;
}
void perceptionRCCInit(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
}
