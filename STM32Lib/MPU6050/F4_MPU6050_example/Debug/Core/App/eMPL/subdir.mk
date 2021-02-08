################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/App/eMPL/inv_mpu.c \
../Core/App/eMPL/inv_mpu_dmp_motion_driver.c 

OBJS += \
./Core/App/eMPL/inv_mpu.o \
./Core/App/eMPL/inv_mpu_dmp_motion_driver.o 

C_DEPS += \
./Core/App/eMPL/inv_mpu.d \
./Core/App/eMPL/inv_mpu_dmp_motion_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Core/App/eMPL/inv_mpu.o: ../Core/App/eMPL/inv_mpu.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I"G:/CubeIDEworkspace/F4_MPU6050/Core/App" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"G:/CubeIDEworkspace/F4_MPU6050/Core/App/eMPL" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/App/eMPL/inv_mpu.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/App/eMPL/inv_mpu_dmp_motion_driver.o: ../Core/App/eMPL/inv_mpu_dmp_motion_driver.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I"G:/CubeIDEworkspace/F4_MPU6050/Core/App" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"G:/CubeIDEworkspace/F4_MPU6050/Core/App/eMPL" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/App/eMPL/inv_mpu_dmp_motion_driver.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

