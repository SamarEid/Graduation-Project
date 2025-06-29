################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/code/src/communication/sender/formatter/serialization.c 

OBJS += \
./Core/code/src/communication/sender/formatter/serialization.o 

C_DEPS += \
./Core/code/src/communication/sender/formatter/serialization.d 


# Each subdirectory must supply rules for building sources it contributes
Core/code/src/communication/sender/formatter/%.o Core/code/src/communication/sender/formatter/%.su Core/code/src/communication/sender/formatter/%.cyclo: ../Core/code/src/communication/sender/formatter/%.c Core/code/src/communication/sender/formatter/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-code-2f-src-2f-communication-2f-sender-2f-formatter

clean-Core-2f-code-2f-src-2f-communication-2f-sender-2f-formatter:
	-$(RM) ./Core/code/src/communication/sender/formatter/serialization.cyclo ./Core/code/src/communication/sender/formatter/serialization.d ./Core/code/src/communication/sender/formatter/serialization.o ./Core/code/src/communication/sender/formatter/serialization.su

.PHONY: clean-Core-2f-code-2f-src-2f-communication-2f-sender-2f-formatter

