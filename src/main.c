#include "FreeRTOS.h"
#include "task.h"
#include "stm32f4_discovery.h"
#include "stm32f4xx_conf.h"

#define ledSTACK_SIZE	configMINIMAL_STACK_SIZE
#define ledFLASH_RATE	( 125 )
#define ledPRIORITY		( tskIDLE_PRIORITY + 1UL )

GPIO_InitTypeDef  GPIO_InitStructure;
static void vLEDFlashTask( void *pvParameters );

void Delay (int i) {
	while (i > 0) {
		i--;
	}
}

typedef struct ledTaskParameters {
	uint16_t ledPin;
} ledTaskParameters_t;

int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f4xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
        system_stm32f4xx.c file
     */

  /* GPIOD Periph clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  /* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  // https://github.com/cjlano/freertos/blob/master/FreeRTOS/Demo/CORTEX_M4F_STM32F407ZG-SK/main.c
  /* Ensure all priority bits are assigned as preemption priority bits. */
  NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );

  // https://github.com/cjlano/freertos/blob/7745275fcde3121f1bab36a8d43eb5df28a31c3c/FreeRTOS/Demo/Common/Full/flash.c#L108
  GPIO_SetBits(GPIOD, GPIO_Pin_13);
  BaseType_t t;

  ledTaskParameters_t ledParams = {ledPin: GPIO_Pin_13};
  t = xTaskCreate( vLEDFlashTask, "LED1", ledSTACK_SIZE, ( void * ) &ledParams, ledPRIORITY, ( TaskHandle_t * ) NULL );

  GPIO_ResetBits(GPIOD, GPIO_Pin_12);

  vTaskStartScheduler();
  // Should never pass this point.

  for(;;) {
	  GPIO_SetBits(GPIOD, GPIO_Pin_12);
	  Delay(0x1FFFFF);
	  GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	  Delay(0x1FFFFF);
  }
}

static void vLEDFlashTask( void *pvParameters )
{
    for(;;)
    {
  	    GPIO_SetBits(GPIOD, GPIO_Pin_14);
        vTaskDelay( 10000 );
  	    GPIO_ResetBits(GPIOD, GPIO_Pin_14);
        vTaskDelay( 10000 );
    }
}


  //while (1)
  //{
  //  /* PD12 to be toggled */
  //  GPIO_SetBits(GPIOD, GPIO_Pin_12);
  //  
  //  /* Insert delay */
  //  Delay(0x3FFFFF);
  //  
  //  /* PD13 to be toggled */
  //  GPIO_SetBits(GPIOD, GPIO_Pin_13);
  //  
  //  /* Insert delay */
  //  Delay(0x3FFFFF);
  //
  //  /* PD14 to be toggled */
  //  GPIO_SetBits(GPIOD, GPIO_Pin_14);
  //  
  //  /* Insert delay */
  //  Delay(0x3FFFFF);
  //  
  //  /* PD15 to be toggled */
  //  GPIO_SetBits(GPIOD, GPIO_Pin_15);
  //  
  //  /* Insert delay */
  //  Delay(0x7FFFFF);

  //  GPIO_ResetBits(GPIOD, GPIO_Pin_15);
  //  Delay(0x7FFFFF);
  //  GPIO_ResetBits(GPIOD, GPIO_Pin_14);
  //  Delay(0x7FFFFF);
  //  GPIO_ResetBits(GPIOD, GPIO_Pin_13);
  //  Delay(0x7FFFFF);
  //  GPIO_ResetBits(GPIOD, GPIO_Pin_12);
  //  Delay(0x7FFFFF);

  //}

