Embedded playground.

Based on:

* [FreeRTOS][freertos], snapshot 2543 (repo [clone with demo][clone])
* [STM32 templates][templates] from Jeremy Herbert

[clone]:https://github.com/cjlano/freertos/tree/master/FreeRTOS/Demo/CORTEX_M4F_STM32F407ZG-SK
[freertos]:https://www.freertos.org/a00104.html
[templates]:https://github.com/jeremyherbert/stm32-templates

# Tools

    sudo apt-get install \
      gcc-arm-none-eabi \
	  gdb-arm-none-eabi \
	  libnewlib-arm-none-eabi

OpenOCD configurations from https://github.com/arduino/OpenOCD

# Commands

OpenOCD server:

	openocd -f ./OpenOCD/tcl/board/stm32f4discovery.cfg

OpenOCD client:

	telnet localhost 4444
	reset halt
	flash write_image erase main.bin 0x08000000
	reset run

debugger:

	arm-none-eabi-gdb
	target remote localhost:3333
	file main.elf
