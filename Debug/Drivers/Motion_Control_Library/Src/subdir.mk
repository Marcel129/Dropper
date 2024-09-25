################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Motion_Control_Library/Src/HardwareLogic.c \
../Drivers/Motion_Control_Library/Src/dcMotor.c \
../Drivers/Motion_Control_Library/Src/sensor.c 

OBJS += \
./Drivers/Motion_Control_Library/Src/HardwareLogic.o \
./Drivers/Motion_Control_Library/Src/dcMotor.o \
./Drivers/Motion_Control_Library/Src/sensor.o 

C_DEPS += \
./Drivers/Motion_Control_Library/Src/HardwareLogic.d \
./Drivers/Motion_Control_Library/Src/dcMotor.d \
./Drivers/Motion_Control_Library/Src/sensor.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Motion_Control_Library/Src/%.o Drivers/Motion_Control_Library/Src/%.su: ../Drivers/Motion_Control_Library/Src/%.c Drivers/Motion_Control_Library/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G491xx -c -I"C:/Users/Marcel/STM32CubeIDE/workspace_1.11.2/siewnik_15_09_2024_Opatow/Drivers/Motion_Control_Library/Inc" -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Motion_Control_Library-2f-Src

clean-Drivers-2f-Motion_Control_Library-2f-Src:
	-$(RM) ./Drivers/Motion_Control_Library/Src/HardwareLogic.d ./Drivers/Motion_Control_Library/Src/HardwareLogic.o ./Drivers/Motion_Control_Library/Src/HardwareLogic.su ./Drivers/Motion_Control_Library/Src/dcMotor.d ./Drivers/Motion_Control_Library/Src/dcMotor.o ./Drivers/Motion_Control_Library/Src/dcMotor.su ./Drivers/Motion_Control_Library/Src/sensor.d ./Drivers/Motion_Control_Library/Src/sensor.o ./Drivers/Motion_Control_Library/Src/sensor.su

.PHONY: clean-Drivers-2f-Motion_Control_Library-2f-Src

