################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Mycode/HMAC/utils_hmac.c \
../Mycode/HMAC/utils_md5.c \
../Mycode/HMAC/utils_sha1.c 

OBJS += \
./Mycode/HMAC/utils_hmac.o \
./Mycode/HMAC/utils_md5.o \
./Mycode/HMAC/utils_sha1.o 

C_DEPS += \
./Mycode/HMAC/utils_hmac.d \
./Mycode/HMAC/utils_md5.d \
./Mycode/HMAC/utils_sha1.d 


# Each subdirectory must supply rules for building sources it contributes
Mycode/HMAC/utils_hmac.o: ../Mycode/HMAC/utils_hmac.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Studio/STM32CubeIDEworkspace/ESP8266/Mycode/Include" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Mycode/HMAC/utils_hmac.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Mycode/HMAC/utils_md5.o: ../Mycode/HMAC/utils_md5.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Studio/STM32CubeIDEworkspace/ESP8266/Mycode/Include" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Mycode/HMAC/utils_md5.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Mycode/HMAC/utils_sha1.o: ../Mycode/HMAC/utils_sha1.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Studio/STM32CubeIDEworkspace/ESP8266/Mycode/Include" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Mycode/HMAC/utils_sha1.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

