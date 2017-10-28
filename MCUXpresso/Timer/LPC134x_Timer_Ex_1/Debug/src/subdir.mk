################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/LPC134x_Timer_Ex_1.cpp \
../src/cr_cpp_config.cpp \
../src/cr_startup_lpc13xx.cpp 

C_SRCS += \
../src/crp.c 

OBJS += \
./src/LPC134x_Timer_Ex_1.o \
./src/cr_cpp_config.o \
./src/cr_startup_lpc13xx.o \
./src/crp.o 

CPP_DEPS += \
./src/LPC134x_Timer_Ex_1.d \
./src/cr_cpp_config.d \
./src/cr_startup_lpc13xx.d 

C_DEPS += \
./src/crp.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC13xx -DCPP_USE_HEAP -D__LPC13XX__ -I"Y:\LPC1343-Tutorial-Examples\MCUXpresso\Timer\CMSIS_CORE_LPC13xx\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC13xx -DCPP_USE_HEAP -D__LPC13XX__ -I"Y:\LPC1343-Tutorial-Examples\MCUXpresso\Timer\CMSIS_CORE_LPC13xx\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


