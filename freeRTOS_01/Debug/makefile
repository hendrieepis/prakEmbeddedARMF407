################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
freeRTOS_01.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
freeRTOS_01.list \

OBJCOPY_BIN += \
freeRTOS_01.bin \


# All Target
all: freeRTOS_01.elf secondary-outputs

# Tool invocations
freeRTOS_01.elf: $(OBJS) $(USER_OBJS) /home/hendri/MyWorkspace/workspaceAC6/freeRTOS_01/LinkerScript.ld
	arm-none-eabi-gcc -o "freeRTOS_01.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/home/hendri/MyWorkspace/workspaceAC6/freeRTOS_01/LinkerScript.ld" --specs=nosys.specs -Wl,-Map="freeRTOS_01.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

freeRTOS_01.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "freeRTOS_01.list"
	@echo 'Finished building: $@'
	@echo ' '

freeRTOS_01.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "freeRTOS_01.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
