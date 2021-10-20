################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
wifi_code.lss \

FLASH_IMAGE += \
wifi_code.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: wifi_code.elf secondary-outputs

# Tool invocations
wifi_code.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,wifi_code.map -mmcu=atmega32 -o "wifi_code.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

wifi_code.lss: wifi_code.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S wifi_code.elf  >"wifi_code.lss"
	@echo 'Finished building: $@'
	@echo ' '

wifi_code.hex: wifi_code.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex wifi_code.elf  "wifi_code.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: wifi_code.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 wifi_code.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) wifi_code.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
