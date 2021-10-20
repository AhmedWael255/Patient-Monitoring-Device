################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIODrv.c \
../LCD.c \
../Rx.c \
../Tx.c \
../USART_prog.c \
../sensors.c \
../wifi.c 

OBJS += \
./DIODrv.o \
./LCD.o \
./Rx.o \
./Tx.o \
./USART_prog.o \
./sensors.o \
./wifi.o 

C_DEPS += \
./DIODrv.d \
./LCD.d \
./Rx.d \
./Tx.d \
./USART_prog.d \
./sensors.d \
./wifi.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


