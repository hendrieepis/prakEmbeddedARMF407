################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hardwareinit.c \
../src/main.c \
../src/sensor.c \
../src/seos.c \
../src/stm32f4xx_it.c \
../src/syscalls.c \
../src/system_stm32f4xx.c \
../src/task.c \
../src/uart.c 

OBJS += \
./src/hardwareinit.o \
./src/main.o \
./src/sensor.o \
./src/seos.o \
./src/stm32f4xx_it.o \
./src/syscalls.o \
./src/system_stm32f4xx.o \
./src/task.o \
./src/uart.o 

C_DEPS += \
./src/hardwareinit.d \
./src/main.d \
./src/sensor.d \
./src/seos.d \
./src/stm32f4xx_it.d \
./src/syscalls.d \
./src/system_stm32f4xx.d \
./src/task.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/hardwareinit.o: ../src/hardwareinit.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F407VGTx -DSTM32F4 -DSTM32F4DISCOVERY -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"/home/hendri/MyWorkspace/workspaceAC6/freeRTOS_01/inc" -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"src/hardwareinit.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/main.o: ../src/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F407VGTx -DSTM32F4 -DSTM32F4DISCOVERY -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"/home/hendri/MyWorkspace/workspaceAC6/freeRTOS_01/inc" -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/sensor.o: ../src/sensor.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F407VGTx -DSTM32F4 -DSTM32F4DISCOVERY -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"/home/hendri/MyWorkspace/workspaceAC6/freeRTOS_01/inc" -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"src/sensor.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/seos.o: ../src/seos.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F407VGTx -DSTM32F4 -DSTM32F4DISCOVERY -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"/home/hendri/MyWorkspace/workspaceAC6/freeRTOS_01/inc" -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"src/seos.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/stm32f4xx_it.o: ../src/stm32f4xx_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F407VGTx -DSTM32F4 -DSTM32F4DISCOVERY -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"/home/hendri/MyWorkspace/workspaceAC6/freeRTOS_01/inc" -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"src/stm32f4xx_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/syscalls.o: ../src/syscalls.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F407VGTx -DSTM32F4 -DSTM32F4DISCOVERY -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"/home/hendri/MyWorkspace/workspaceAC6/freeRTOS_01/inc" -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"src/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/system_stm32f4xx.o: ../src/system_stm32f4xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F407VGTx -DSTM32F4 -DSTM32F4DISCOVERY -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"/home/hendri/MyWorkspace/workspaceAC6/freeRTOS_01/inc" -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"src/system_stm32f4xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/task.o: ../src/task.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F407VGTx -DSTM32F4 -DSTM32F4DISCOVERY -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"/home/hendri/MyWorkspace/workspaceAC6/freeRTOS_01/inc" -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"src/task.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/uart.o: ../src/uart.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F407VGTx -DSTM32F4 -DSTM32F4DISCOVERY -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"/home/hendri/MyWorkspace/workspaceAC6/freeRTOS_01/inc" -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"src/uart.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

