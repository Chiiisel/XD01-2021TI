################################################################################
# 自动生成的文件。不要编辑！
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Mycode/MQTT/src/MQTTConnectClient.c \
../Mycode/MQTT/src/MQTTConnectServer.c \
../Mycode/MQTT/src/MQTTDeserializePublish.c \
../Mycode/MQTT/src/MQTTFormat.c \
../Mycode/MQTT/src/MQTTPacket.c \
../Mycode/MQTT/src/MQTTSerializePublish.c \
../Mycode/MQTT/src/MQTTSubscribeClient.c \
../Mycode/MQTT/src/MQTTSubscribeServer.c \
../Mycode/MQTT/src/MQTTUnsubscribeClient.c \
../Mycode/MQTT/src/MQTTUnsubscribeServer.c \
../Mycode/MQTT/src/cJSON.c 

OBJS += \
./Mycode/MQTT/src/MQTTConnectClient.o \
./Mycode/MQTT/src/MQTTConnectServer.o \
./Mycode/MQTT/src/MQTTDeserializePublish.o \
./Mycode/MQTT/src/MQTTFormat.o \
./Mycode/MQTT/src/MQTTPacket.o \
./Mycode/MQTT/src/MQTTSerializePublish.o \
./Mycode/MQTT/src/MQTTSubscribeClient.o \
./Mycode/MQTT/src/MQTTSubscribeServer.o \
./Mycode/MQTT/src/MQTTUnsubscribeClient.o \
./Mycode/MQTT/src/MQTTUnsubscribeServer.o \
./Mycode/MQTT/src/cJSON.o 

C_DEPS += \
./Mycode/MQTT/src/MQTTConnectClient.d \
./Mycode/MQTT/src/MQTTConnectServer.d \
./Mycode/MQTT/src/MQTTDeserializePublish.d \
./Mycode/MQTT/src/MQTTFormat.d \
./Mycode/MQTT/src/MQTTPacket.d \
./Mycode/MQTT/src/MQTTSerializePublish.d \
./Mycode/MQTT/src/MQTTSubscribeClient.d \
./Mycode/MQTT/src/MQTTSubscribeServer.d \
./Mycode/MQTT/src/MQTTUnsubscribeClient.d \
./Mycode/MQTT/src/MQTTUnsubscribeServer.d \
./Mycode/MQTT/src/cJSON.d 


# Each subdirectory must supply rules for building sources it contributes
Mycode/MQTT/src/MQTTConnectClient.o: ../Mycode/MQTT/src/MQTTConnectClient.c Mycode/MQTT/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I"D:/Studio/STM32CubeIDEworkspace/Tess/Mycode/Include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Studio/STM32CubeIDEworkspace/Tess/Mycode/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Mycode/MQTT/src/MQTTConnectClient.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Mycode/MQTT/src/MQTTConnectServer.o: ../Mycode/MQTT/src/MQTTConnectServer.c Mycode/MQTT/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I"D:/Studio/STM32CubeIDEworkspace/Tess/Mycode/Include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Studio/STM32CubeIDEworkspace/Tess/Mycode/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Mycode/MQTT/src/MQTTConnectServer.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Mycode/MQTT/src/MQTTDeserializePublish.o: ../Mycode/MQTT/src/MQTTDeserializePublish.c Mycode/MQTT/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I"D:/Studio/STM32CubeIDEworkspace/Tess/Mycode/Include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Studio/STM32CubeIDEworkspace/Tess/Mycode/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Mycode/MQTT/src/MQTTDeserializePublish.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Mycode/MQTT/src/MQTTFormat.o: ../Mycode/MQTT/src/MQTTFormat.c Mycode/MQTT/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I"D:/Studio/STM32CubeIDEworkspace/Tess/Mycode/Include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Studio/STM32CubeIDEworkspace/Tess/Mycode/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Mycode/MQTT/src/MQTTFormat.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Mycode/MQTT/src/MQTTPacket.o: ../Mycode/MQTT/src/MQTTPacket.c Mycode/MQTT/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I"D:/Studio/STM32CubeIDEworkspace/Tess/Mycode/Include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Studio/STM32CubeIDEworkspace/Tess/Mycode/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Mycode/MQTT/src/MQTTPacket.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Mycode/MQTT/src/MQTTSerializePublish.o: ../Mycode/MQTT/src/MQTTSerializePublish.c Mycode/MQTT/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I"D:/Studio/STM32CubeIDEworkspace/Tess/Mycode/Include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Studio/STM32CubeIDEworkspace/Tess/Mycode/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Mycode/MQTT/src/MQTTSerializePublish.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Mycode/MQTT/src/MQTTSubscribeClient.o: ../Mycode/MQTT/src/MQTTSubscribeClient.c Mycode/MQTT/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I"D:/Studio/STM32CubeIDEworkspace/Tess/Mycode/Include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Studio/STM32CubeIDEworkspace/Tess/Mycode/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Mycode/MQTT/src/MQTTSubscribeClient.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Mycode/MQTT/src/MQTTSubscribeServer.o: ../Mycode/MQTT/src/MQTTSubscribeServer.c Mycode/MQTT/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I"D:/Studio/STM32CubeIDEworkspace/Tess/Mycode/Include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Studio/STM32CubeIDEworkspace/Tess/Mycode/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Mycode/MQTT/src/MQTTSubscribeServer.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Mycode/MQTT/src/MQTTUnsubscribeClient.o: ../Mycode/MQTT/src/MQTTUnsubscribeClient.c Mycode/MQTT/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I"D:/Studio/STM32CubeIDEworkspace/Tess/Mycode/Include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Studio/STM32CubeIDEworkspace/Tess/Mycode/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Mycode/MQTT/src/MQTTUnsubscribeClient.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Mycode/MQTT/src/MQTTUnsubscribeServer.o: ../Mycode/MQTT/src/MQTTUnsubscribeServer.c Mycode/MQTT/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I"D:/Studio/STM32CubeIDEworkspace/Tess/Mycode/Include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Studio/STM32CubeIDEworkspace/Tess/Mycode/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Mycode/MQTT/src/MQTTUnsubscribeServer.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Mycode/MQTT/src/cJSON.o: ../Mycode/MQTT/src/cJSON.c Mycode/MQTT/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I"D:/Studio/STM32CubeIDEworkspace/Tess/Mycode/Include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Studio/STM32CubeIDEworkspace/Tess/Mycode/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Mycode/MQTT/src/cJSON.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

