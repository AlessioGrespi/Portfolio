#include "stm32f3xx.h" 

void PWMStartUp(void);

int main(void)
{
	PWMStartUp();

	while (1);
}

void PWMStartUp ()
{
	RCC->AHBENR |= RCC_AHBENR_GPIOEEN;
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	GPIOE->MODER |= 0X00080000;
	GPIOE->AFR[1] |= 0X00000020;
	TIM1->PSC = 99;
	TIM1->ARR = 79;
	TIM1->CCMR1 |= 0x00000060;
	TIM1->CCR1 = 10; // ONTIME FOR CLOCK PULES // THIS AFFECTS THE BRIGHTENESS
	//SET gpio PIN TO OUTPUT MOE IN TIMx_BDTR
	TIM1->BDTR |= TIM_BDTR_MOE;
	//enable channel to output in TIMx_CCER
	TIM1->CCER |= TIM_CCER_CC1E;
	//ENABLE TIMER
	TIM1->CR1 |= TIM_CR1_CEN;

	

	//Configure the required pin to be ‘alternate function’ with suitable transistor and resistor arrangements. Remember to connect the port to a system clock to activate it.
	//make pin that uses tim1 from afr register, look at afr tables GPIOE->AFR[0]|=0x00000200;

// use the arr and psc thingies for this new timer to make a 100Hz freq.

}

