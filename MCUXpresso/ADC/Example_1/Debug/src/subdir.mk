################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Example_1.c \
../src/cr_startup_lpc13xx.c \
../src/crp.c \
../src/ocf_lpc134x_lib.c 

OBJS += \
./src/Example_1.o \
./src/cr_startup_lpc13xx.o \
./src/crp.o \
./src/ocf_lpc134x_lib.o 

C_DEPS += \
./src/Example_1.d \
./src/cr_startup_lpc13xx.d \
./src/crp.d \
./src/ocf_lpc134x_lib.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC13xx -D__LPC13XX__ -D__REDLIB__ -I"Y:\LPC1343-Tutorial-Examples\MCUXpresso\ADC\CMSIS_CORE_LPC13xx\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


