#include "stm32f3xx.h" 

void LEDsetupGPIOE(void);
void SysConfig(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI1_TSC_IRQHandler(void);
void LEDUpdate(void);

int test = 0;
int encoderCount = 0;
		
int main(void)
{
	LEDsetupGPIOE();
	SysConfig();

	while (1);
}



void LEDupdate()
{
	encoderCount++;
	
	GPIOE->BSRRH = (0xFC00); //set to off
	
	if (encoderCount == 16)
	{
		encoderCount = 0;
	}
		
	GPIOE->BSRRL = encoderCount << 12; //11-14
}

void LEDsetupGPIOE()
{
	RCC->AHBENR |= RCC_AHBENR_GPIOEEN;	 // Enable clock on GPIO port E
	GPIOE->MODER |= 0x55550000; // Set mode of each pin in port E
	GPIOE->OTYPER &= ~(0x00000000); // Set output type for each pin required in Port E
	GPIOE->PUPDR &= ~(0xffff0000); // Set Pull up/Pull down resistor configuration for Port E
}

void SysConfig()
{
	//button config
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; //sysconfig connect to system clock so gpio interrupt work
	
	EXTI->IMR |= EXTI_IMR_MR0;
	EXTI->RTSR |= EXTI_RTSR_TR0;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;	//PA0
	
	//LEDA 
	EXTI->IMR |= EXTI_IMR_MR1;
	EXTI->RTSR |= EXTI_RTSR_TR1; //trigger on rise
	EXTI->FTSR |= EXTI_FTSR_TR1; //trigger on fall
	SYSCFG->EXTICR[1] |= SYSCFG_EXTICR1_EXTI1_PA;	//PA1
	
	//LEDB 
	EXTI->IMR |= EXTI_IMR_MR2;
	EXTI->RTSR |= EXTI_RTSR_TR2; //trigger on rise
	EXTI->FTSR |= EXTI_FTSR_TR2; //trigger on fall
	SYSCFG->EXTICR[2] |= SYSCFG_EXTICR1_EXTI2_PA;	//PA2
	
	NVIC_EnableIRQ(EXTI0_IRQn); // Enable Timer ‘x’ interrupt request in NVIC
	NVIC_SetPriority(EXTI0_IRQn, 0x00);
	
	NVIC_EnableIRQ(EXTI1_IRQn); // Enable Timer ‘x’ interrupt request in NVIC
	NVIC_SetPriority(EXTI1_IRQn, 0x00);
	
	NVIC_EnableIRQ(EXTI2_TSC_IRQn); // Enable Timer ‘x’ interrupt request in NVIC
	NVIC_SetPriority(EXTI2_TSC_IRQn, 0x00);
}


void EXTI0_IRQHandler()
{
	if (EXTI->PR & EXTI_PR_PR0) // check source
	{
				test++;
		EXTI->PR |= EXTI_PR_PR0; // clear flag*
		// ENTER FUNCTION HERE
		GPIOE->BSRRH = (0x300);
		switch(test)
		{
			case 1: //10
					GPIOE->BSRRL = (0x100);	
				break;
			case 2: //11
					GPIOE->BSRRL = (0x300);
				break;
			case 3:	//01
					GPIOE->BSRRL = (0x200);	
				break;
			case 4: //00
					test = 0;
					GPIOE->BSRRH = (0x300);
				break;
		}

	}
}


void EXTI1_IRQHandler()
{
	if (EXTI->PR & EXTI_PR_PR1) // check source
	{
		EXTI->PR |= EXTI_PR_PR1; // clear flag*
		// ENTER FUNCTION HERE	
		LEDupdate();
	}
};

void EXTI2_TSC_IRQHandler()
{
	if (EXTI->PR & EXTI_PR_PR2) // check source
	{
		EXTI->PR |= EXTI_PR_PR2; // clear flag*
		// ENTER FUNCTION HERE
		LEDupdate();
	}
};
