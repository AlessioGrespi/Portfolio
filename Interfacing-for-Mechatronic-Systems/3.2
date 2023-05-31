#include "stm32f3xx.h" 

void SysConfig(void);
void EXTI0_IRQHandler(void);

int test = 0;
		
int main(void)
{
	SysConfig();

	while(1);
}

void SysConfig()
{
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	EXTI->IMR |= EXTI_IMR_MR0;
	EXTI->RTSR |= EXTI_RTSR_TR0;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;
		
	//TIM1->DIER |= TIM_DIER_UIE; 
	NVIC_EnableIRQ(EXTI0_IRQn); // Enable Timer ‘x’ interrupt request in NVIC
	NVIC_SetPriority(EXTI0_IRQn, 0x00);
}

void EXTI0_IRQHandler()
{
	if (EXTI->PR & EXTI_PR_PR0) // check source
	{
		EXTI->PR |= EXTI_PR_PR0; // clear flag*
		test++;
	}
}
