################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sensors/ADXL345.c \
../sensors/itg3200.c 

OBJS += \
./sensors/ADXL345.o \
./sensors/itg3200.o 

C_DEPS += \
./sensors/ADXL345.d \
./sensors/itg3200.d 


# Each subdirectory must supply rules for building sources it contributes
sensors/%.o: ../sensors/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-gcc -I"C:\altera\16.0\embedded\ip\altera\hps\altera_hps\hwlib\include" -I"H:\Git\template_speedy\hps_workspace\saber\sensors" -I"H:\Git\template_speedy\hps_workspace\saber\actuators" -O0 -g -Wall -c -fmessage-length=0 -Dsoc_cv_av -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

