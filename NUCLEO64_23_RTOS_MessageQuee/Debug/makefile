################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include Src/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
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
NUCLEO64_23_RTOS_MessageQuee.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
NUCLEO64_23_RTOS_MessageQuee.list \

OBJCOPY_BIN += \
NUCLEO64_23_RTOS_MessageQuee.bin \


# All Target
all: NUCLEO64_23_RTOS_MessageQuee.elf secondary-outputs

# Tool invocations
NUCLEO64_23_RTOS_MessageQuee.elf: $(OBJS) $(USER_OBJS) ../STM32F446RETx_FLASH.ld
	arm-none-eabi-gcc -o "NUCLEO64_23_RTOS_MessageQuee.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"../STM32F446RETx_FLASH.ld" --specs=nosys.specs -Wl,-Map="NUCLEO64_23_RTOS_MessageQuee.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

NUCLEO64_23_RTOS_MessageQuee.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "NUCLEO64_23_RTOS_MessageQuee.list"
	@echo 'Finished building: $@'
	@echo ' '

NUCLEO64_23_RTOS_MessageQuee.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "NUCLEO64_23_RTOS_MessageQuee.bin"
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
