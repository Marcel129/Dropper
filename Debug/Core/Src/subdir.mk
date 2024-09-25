################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/HW_logic.c \
../Core/Src/UART_communication.c \
../Core/Src/box.c \
../Core/Src/dcMotor.c \
../Core/Src/dropper.c \
../Core/Src/gpio.c \
../Core/Src/main.c \
../Core/Src/pusher.c \
../Core/Src/sensor.c \
../Core/Src/stm32g4xx_hal_msp.c \
../Core/Src/stm32g4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32g4xx.c \
../Core/Src/tim.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/HW_logic.o \
./Core/Src/UART_communication.o \
./Core/Src/box.o \
./Core/Src/dcMotor.o \
./Core/Src/dropper.o \
./Core/Src/gpio.o \
./Core/Src/main.o \
./Core/Src/pusher.o \
./Core/Src/sensor.o \
./Core/Src/stm32g4xx_hal_msp.o \
./Core/Src/stm32g4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32g4xx.o \
./Core/Src/tim.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/HW_logic.d \
./Core/Src/UART_communication.d \
./Core/Src/box.d \
./Core/Src/dcMotor.d \
./Core/Src/dropper.d \
./Core/Src/gpio.d \
./Core/Src/main.d \
./Core/Src/pusher.d \
./Core/Src/sensor.d \
./Core/Src/stm32g4xx_hal_msp.d \
./Core/Src/stm32g4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32g4xx.d \
./Core/Src/tim.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G491xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/HW_logic.d ./Core/Src/HW_logic.o ./Core/Src/HW_logic.su ./Core/Src/UART_communication.d ./Core/Src/UART_communication.o ./Core/Src/UART_communication.su ./Core/Src/box.d ./Core/Src/box.o ./Core/Src/box.su ./Core/Src/dcMotor.d ./Core/Src/dcMotor.o ./Core/Src/dcMotor.su ./Core/Src/dropper.d ./Core/Src/dropper.o ./Core/Src/dropper.su ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/pusher.d ./Core/Src/pusher.o ./Core/Src/pusher.su ./Core/Src/sensor.d ./Core/Src/sensor.o ./Core/Src/sensor.su ./Core/Src/stm32g4xx_hal_msp.d ./Core/Src/stm32g4xx_hal_msp.o ./Core/Src/stm32g4xx_hal_msp.su ./Core/Src/stm32g4xx_it.d ./Core/Src/stm32g4xx_it.o ./Core/Src/stm32g4xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32g4xx.d ./Core/Src/system_stm32g4xx.o ./Core/Src/system_stm32g4xx.su ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su

.PHONY: clean-Core-2f-Src

