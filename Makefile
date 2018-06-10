# put your *.o targets here, make should handle the rest!

HEADERS = FreeRTOS/Demo/CORTEX_M4F_STM32F407ZG-SK/FreeRTOSConfig.h

SRCS = main.c \
       stm32f4xx_it.c \
       system_stm32f4xx.c \
       FreeRTOS/Source/croutine.c \
       FreeRTOS/Source/list.c \
       FreeRTOS/Source/queue.c \
       FreeRTOS/Source/event_groups.c \
       FreeRTOS/Source/timers.c \
       FreeRTOS/Source/tasks.c \
       FreeRTOS/Source/stream_buffer.c \
       FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c \
       FreeRTOS/Source/portable/MemMang/heap_1.c

# all the files will be generated with this name (main.elf, main.bin, main.hex, etc)

PROJ_NAME=main

# that's it, no need to change anything below this line!

###################################################

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

CFLAGS  = -g -O2 -Wall -Tstm32_flash.ld 
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16

###################################################

vpath %.c src
vpath %.a lib

ROOT=$(shell pwd)

CFLAGS += -Iinc -Ilib -Ilib/inc 
CFLAGS += -Ilib/inc/core -Ilib/inc/peripherals 
CFLAGS += -IFreeRTOS/Source/include
CFLAGS += -IFreeRTOS/Demo/CORTEX_M4F_STM32F407ZG-SK
CFLAGS += -IFreeRTOS/Source/portable/GCC/ARM_CM4F

SRCS += lib/startup_stm32f4xx.s # add startup file to build

OBJS = $(SRCS:.c=.o)

###################################################

.PHONY: lib proj

all: lib proj

lib:
	$(MAKE) -C lib

proj: 	$(PROJ_NAME).elf

$(PROJ_NAME).elf: $(HEADERS) $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@ -Llib -lstm32f4
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin

clean:
	$(MAKE) -C lib clean
	rm -f $(PROJ_NAME).elf
	rm -f $(PROJ_NAME).hex
	rm -f $(PROJ_NAME).bin
