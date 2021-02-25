################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/App/HMI.c \
../Core/App/app.c \
../Core/App/esp8266_at.c \
../Core/App/mpu6050.c \
../Core/App/my_adc.c \
../Core/App/my_uart.c 

OBJS += \
./Core/App/HMI.o \
./Core/App/app.o \
./Core/App/esp8266_at.o \
./Core/App/mpu6050.o \
./Core/App/my_adc.o \
./Core/App/my_uart.o 

C_DEPS += \
./Core/App/HMI.d \
./Core/App/app.d \
./Core/App/esp8266_at.d \
./Core/App/mpu6050.d \
./Core/App/my_adc.d \
./Core/App/my_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/App/HMI.o: ../Core/App/HMI.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I"G:/CubeIDEworkspace/F4_MPU6050/Core/App" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"G:/CubeIDEworkspace/F4_MPU6050/Core/App/eMPL" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/App/HMI.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/App/app.o: ../Core/App/app.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I"G:/CubeIDEworkspace/F4_MPU6050/Core/App" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"G:/CubeIDEworkspace/F4_MPU6050/Core/App/eMPL" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/App/app.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/App/esp8266_at.o: ../Core/App/esp8266_at.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I"G:/CubeIDEworkspace/F4_MPU6050/Core/App" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"G:/CubeIDEworkspace/F4_MPU6050/Core/App/eMPL" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/App/esp8266_at.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/App/mpu6050.o: ../Core/App/mpu6050.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I"G:/CubeIDEworkspace/F4_MPU6050/Core/App" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"G:/CubeIDEworkspace/F4_MPU6050/Core/App/eMPL" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/App/mpu6050.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/App/my_adc.o: ../Core/App/my_adc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I"G:/CubeIDEworkspace/F4_MPU6050/Core/App" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"G:/CubeIDEworkspace/F4_MPU6050/Core/App/eMPL" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/App/my_adc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/App/my_uart.o: ../Core/App/my_uart.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I"G:/CubeIDEworkspace/F4_MPU6050/Core/App" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"G:/CubeIDEworkspace/F4_MPU6050/Core/App/eMPL" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/App/my_uart.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

