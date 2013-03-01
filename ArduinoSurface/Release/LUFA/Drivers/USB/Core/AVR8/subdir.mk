################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LUFA/Drivers/USB/Core/AVR8/Device_AVR8.c \
../LUFA/Drivers/USB/Core/AVR8/EndpointStream_AVR8.c \
../LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c \
../LUFA/Drivers/USB/Core/AVR8/PipeStream_AVR8.c \
../LUFA/Drivers/USB/Core/AVR8/Pipe_AVR8.c \
../LUFA/Drivers/USB/Core/AVR8/USBController_AVR8.c \
../LUFA/Drivers/USB/Core/AVR8/USBInterrupt_AVR8.c 

OBJS += \
./LUFA/Drivers/USB/Core/AVR8/Device_AVR8.o \
./LUFA/Drivers/USB/Core/AVR8/EndpointStream_AVR8.o \
./LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.o \
./LUFA/Drivers/USB/Core/AVR8/PipeStream_AVR8.o \
./LUFA/Drivers/USB/Core/AVR8/Pipe_AVR8.o \
./LUFA/Drivers/USB/Core/AVR8/USBController_AVR8.o \
./LUFA/Drivers/USB/Core/AVR8/USBInterrupt_AVR8.o 

C_DEPS += \
./LUFA/Drivers/USB/Core/AVR8/Device_AVR8.d \
./LUFA/Drivers/USB/Core/AVR8/EndpointStream_AVR8.d \
./LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.d \
./LUFA/Drivers/USB/Core/AVR8/PipeStream_AVR8.d \
./LUFA/Drivers/USB/Core/AVR8/Pipe_AVR8.d \
./LUFA/Drivers/USB/Core/AVR8/USBController_AVR8.d \
./LUFA/Drivers/USB/Core/AVR8/USBInterrupt_AVR8.d 


# Each subdirectory must supply rules for building sources it contributes
LUFA/Drivers/USB/Core/AVR8/%.o: ../LUFA/Drivers/USB/Core/AVR8/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/Users/shawn/Documents/workspace/depot/ArduinoSurface/Config" -I"/Users/shawn/Documents/workspace/depot/ArduinoSurface" -I"/Users/shawn/Documents/workspace/arduino/cores/arduino" -I"/Users/shawn/Documents/workspace/arduino/variants/standard" -D__AVR_LIBC_DEPRECATED_ENABLE__ -DBOARD=BOARD_USER -DARCH=ARCH_AVR8 -DF_CPU=16000000UL -DF_USB=16000000UL -DUSE_LUFA_CONFIG_HEADER -Wall -g2 -gstabs -Os -fpack-struct -fshort-enums -pipe -fno-inline-small-functions -fno-strict-aliasing -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -g -mmcu=atmega8u2 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


