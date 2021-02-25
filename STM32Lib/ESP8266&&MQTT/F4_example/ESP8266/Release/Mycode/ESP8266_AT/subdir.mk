################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Mycode/ESP8266_AT/esp8266_at.c 

OBJS += \
./Mycode/ESP8266_AT/esp8266_at.o 

C_DEPS += \
./Mycode/ESP8266_AT/esp8266_at.d 


# Each subdirectory must supply rules for building sources it contributes
Mycode/ESP8266_AT/esp8266_at.o: ../Mycode/ESP8266_AT/esp8266_at.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Studio/STM32CubeIDEworkspace/ESP8266/Mycode/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Mycode/ESP8266_AT/esp8266_at.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

