#include "stm32f3xx.h" 



void TIM3_IRQHandler();
	int counter;
int main(void)
{

	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	
	TIM3->PSC = 799; // prescalor value in Timer ‘x’ as 100
TIM3->ARR = 9999; // Auto-Reset Register of Timer ‘x’ set to 1000 counts
	
	TIM3->CR1 |= TIM_CR1_CEN; // timer start

	TIM3->DIER |= TIM_DIER_UIE; // Set DIER register to watch out for an ‘Update’ Interrupt Enable (UIE) – or 0x00000001
	NVIC_EnableIRQ(TIM3_IRQn); // Enable Timer ‘x’ interrupt request in NVIC


	
	// Enable clock on GPIO port E
	RCC->AHBENR |= RCC_AHBENR_GPIOEEN;
	
	// GPIOE is a structure defined in stm32f303xc.h file
	// Define settings for each output pin using GPIOE structure
	GPIOE->MODER |= 0x55550000; // Set mode of each pin in port E
	GPIOE->OTYPER &= ~(0x00000000); // Set output type for each pin required in Port E
	GPIOE->PUPDR &= ~(0xffff0000); // Set Pull up/Pull down resistor configuration for Port E
	

	
	
	while (1)
  {
		GPIOE->BSRRL = (counter << 8); //shifts bits left by 8 spots, auto converts from decimal to hex

	}

}

void TIM3_IRQHandler()
{

if ((TIM3->SR & TIM_SR_UIF) !=0) // Check interrupt source is from  the ‘Update’ interrupt flag
{
		GPIOE->BSRRH = (counter << 8); 

		counter++;
}

TIM3->SR &= ~TIM_SR_UIF; // Reset ‘Update’ interrupt flag in the SR register

}




/*




#include "stm32f3xx.h"                  // Device header


void delay(int a); // prototype for delay function

int main(void)
{
	// Enable clock on GPIO port E
	RCC->AHBENR |= RCC_AHBENR_GPIOEEN;
	
	// GPIOE is a structure defined in stm32f303xc.h file
	// Define settings for each output pin using GPIOE structure
	GPIOE->MODER |= 0x55550000; // Set mode of each pin in port E
	GPIOE->OTYPER &= ~(0x00000000); // Set output type for each pin required in Port E
	GPIOE->PUPDR &= ~(0xffff0000); // Set Pull up/Pull down resistor configuration for Port E
	
	int counter;
	
	// Main programme loop - make LED 4 (attached to pin PE.0) turn on and off	
	while (1)
  {
		GPIOE->BSRRL = (counter << 8); //shifts bits left by 8 spots, auto converts from decimal to hex
		delay(1000000);
		GPIOE->BSRRH = (counter << 8); 
		delay(1000000);
		counter++;
	}

}

// Delay function to occupy processor
void delay (int a)
{
    volatile int i,j;

    for (i=0 ; i < a ; i++)
    {
        j++;
    }

    return;
}

*/
