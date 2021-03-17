#include <stm32f4xx.h>
#include <stdint.h>

void Delaym(__IO uint32_t delaypar);
void RCC_config(void) {
  SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN); // enable the IO port A clock
  SET_BIT(RCC->APB1ENR, RCC_APB1ENR_DACEN);   // enable the DAC clock
}

// GPIO setting
void GPIOA_config(void) {
  SET_BIT(GPIOA->MODER, GPIO_MODER_MODER4);   // PA4 = Analog
}

void DAC_config(void) {
  SET_BIT(DAC->CR, DAC_CR_EN1);
}

int main(void) {
  RCC_config();
  GPIOA_config();
  DAC_config();
  while(1)
  {
	  for (__IO uint16_t i=0;i<4095;i++)
	  {
		  DAC->DHR12R1 = i;
		  Delaym(0xF);
	  }

  }

}

void Delaym(__IO uint32_t delaypar)
{
	while(delaypar--);
}
