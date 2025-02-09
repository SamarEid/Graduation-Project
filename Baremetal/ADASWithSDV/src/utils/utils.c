/*
 * utils.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: ASHRY
 */
#include <stdint.h>
#include "stm32f4xx.h"
#include "./utils.h"
uint8_t PinSource(uint32_t pin) {
    uint8_t pinSource = 0;
    while (pin >>= 1  )
    	pinSource++;
    return pinSource;
}
