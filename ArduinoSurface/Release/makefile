################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include LUFA/Drivers/USB/Core/AVR8/subdir.mk
-include LUFA/Drivers/USB/Core/subdir.mk
-include LUFA/Drivers/USB/Class/Device/subdir.mk
-include LUFA/Drivers/USB/Class/Common/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
ArduinoSurface.lss \

FLASH_IMAGE += \
ArduinoSurface.hex \

EEPROM_IMAGE += \
ArduinoSurface.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: ArduinoSurface.elf secondary-outputs

# Tool invocations
ArduinoSurface.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-gcc -Wl,-Map,ArduinoSurface.map,--cref -lm -Wl,--gc-sections -Wl,--relax -mmcu=atmega8u2 -o "ArduinoSurface.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ArduinoSurface.lss: ArduinoSurface.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ArduinoSurface.elf  >"ArduinoSurface.lss"
	@echo 'Finished building: $@'
	@echo ' '

ArduinoSurface.hex: ArduinoSurface.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex ArduinoSurface.elf  "ArduinoSurface.hex"
	@echo 'Finished building: $@'
	@echo ' '

ArduinoSurface.eep: ArduinoSurface.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 --no-change-warnings -O ihex ArduinoSurface.elf  "ArduinoSurface.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ArduinoSurface.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8u2 ArduinoSurface.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EEPROM_IMAGE)$(ELFS)$(FLASH_IMAGE)$(LSS)$(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(CPP_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) ArduinoSurface.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
