################################################################################
# �Զ����ɵ��ļ�����Ҫ�༭��
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Mycode/UART_BUFF/my_uart.c 

OBJS += \
./Mycode/UART_BUFF/my_uart.o 

C_DEPS += \
./Mycode/UART_BUFF/my_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Mycode/UART_BUFF/my_uart.o: ../Mycode/UART_BUFF/my_uart.c Mycode/UART_BUFF/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I"D:/Studio/STM32CubeIDEworkspace/Tess/Mycode/Include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Studio/STM32CubeIDEworkspace/Tess/Mycode/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Mycode/UART_BUFF/my_uart.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

