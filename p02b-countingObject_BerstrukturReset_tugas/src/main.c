
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include  "hardwareinit.h"
#include  "sensor.h"
#include  "counter.h"
			
UART_HandleTypeDef huart2;
int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	while(1){
        counterShow();
        if(sensorDetected()){
        	CounterUpdate();
        }
        if(resetDetected()){
            CounterZero();
        }
	}
}





