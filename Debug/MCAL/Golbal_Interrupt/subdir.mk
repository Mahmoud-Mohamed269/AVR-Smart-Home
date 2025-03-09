################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/Golbal_Interrupt/M_GLOBAL_INTERRUPT.c 

OBJS += \
./MCAL/Golbal_Interrupt/M_GLOBAL_INTERRUPT.o 

C_DEPS += \
./MCAL/Golbal_Interrupt/M_GLOBAL_INTERRUPT.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/Golbal_Interrupt/%.o: ../MCAL/Golbal_Interrupt/%.c MCAL/Golbal_Interrupt/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


