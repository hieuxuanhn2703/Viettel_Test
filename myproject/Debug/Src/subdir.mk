################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc.c \
../Src/core_clock.c \
../Src/flash.c \
../Src/interrupt.c \
../Src/lcd.c \
../Src/main.c \
../Src/matrix_key.c \
../Src/pwm.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/systick.c \
../Src/uart.c 

OBJS += \
./Src/adc.o \
./Src/core_clock.o \
./Src/flash.o \
./Src/interrupt.o \
./Src/lcd.o \
./Src/main.o \
./Src/matrix_key.o \
./Src/pwm.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/systick.o \
./Src/uart.o 

C_DEPS += \
./Src/adc.d \
./Src/core_clock.d \
./Src/flash.d \
./Src/interrupt.d \
./Src/lcd.d \
./Src/main.d \
./Src/matrix_key.d \
./Src/pwm.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/systick.d \
./Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/adc.cyclo ./Src/adc.d ./Src/adc.o ./Src/adc.su ./Src/core_clock.cyclo ./Src/core_clock.d ./Src/core_clock.o ./Src/core_clock.su ./Src/flash.cyclo ./Src/flash.d ./Src/flash.o ./Src/flash.su ./Src/interrupt.cyclo ./Src/interrupt.d ./Src/interrupt.o ./Src/interrupt.su ./Src/lcd.cyclo ./Src/lcd.d ./Src/lcd.o ./Src/lcd.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/matrix_key.cyclo ./Src/matrix_key.d ./Src/matrix_key.o ./Src/matrix_key.su ./Src/pwm.cyclo ./Src/pwm.d ./Src/pwm.o ./Src/pwm.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/systick.cyclo ./Src/systick.d ./Src/systick.o ./Src/systick.su ./Src/uart.cyclo ./Src/uart.d ./Src/uart.o ./Src/uart.su

.PHONY: clean-Src

