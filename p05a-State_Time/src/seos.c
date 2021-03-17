#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "seos.h"
#include "device.h"
#include "task.h"
TIM_HandleTypeDef TIM_Handle;

void TIM4_IRQHandler(void)
{
	if (__HAL_TIM_GET_FLAG(&TIM_Handle, TIM_FLAG_UPDATE) != RESET)      //In case other interrupts are also running
	{
		if (__HAL_TIM_GET_ITSTATUS(&TIM_Handle, TIM_IT_UPDATE) != RESET)
		{
			__HAL_TIM_CLEAR_FLAG(&TIM_Handle, TIM_FLAG_UPDATE);
			/*put your code here */
			HAL_GPIO_TogglePin(led0_GPIO_Port,led0_Pin);
			Task_Run();
		}
	}
}

void SCH_init(uint32_t Periode){
	/*  SAMPLING is not equal to freq.
	 *  APB1 Timer clock = 84MHz
	 *	Prescaller = 42000
	 *	Tick=42000/84Mhz=0.5ms
	 *	if interval timer 1ms
	 *	then interval timer= periode*tick
	 *	Periode= IntervalTimer/Tick
	 *	Periode= 1ms/0.5ms
	 *	Periode=2
	 */
		__TIM4_CLK_ENABLE();
		TIM_Handle.Init.Prescaler = 42000-1;
		TIM_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
		TIM_Handle.Init.Period = (Periode*2)-1;
		TIM_Handle.Instance = TIM4;   //Same timer whose clocks we enabled
		HAL_TIM_Base_Init(&TIM_Handle);     // Init timer
		HAL_TIM_Base_Start_IT(&TIM_Handle); // start timer interrupts
		HAL_NVIC_SetPriority(TIM4_IRQn, 0, 1);
		HAL_NVIC_EnableIRQ(TIM4_IRQn);
}
