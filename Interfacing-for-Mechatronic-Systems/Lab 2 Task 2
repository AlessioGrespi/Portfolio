#include "stm32f3xx.h" 

void TIM3_IRQHandler();
	int counter;
		void delay(int a); // prototype for delay function
		
int main(void)
{
	
	//LED Timer Setup
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; //timer for LEDs
	TIM3->PSC = 799; // prescalor value in Timer ‘x’ as 100
	TIM3->ARR = 999; // Auto-Reset Register of Timer ‘x’ set to 1000 counts
	TIM3->CR1 |= TIM_CR1_CEN; // timer start
	
	//Timer Interrupt setup
	TIM3->DIER |= TIM_DIER_UIE; // Set DIER register to watch out for an ‘Update’ Interrupt Enable (UIE) – or 0x00000001
	NVIC_EnableIRQ(TIM3_IRQn); // Enable Timer ‘x’ interrupt request in NVIC
	
	//GPIOE Clock
	RCC->AHBENR |= RCC_AHBENR_GPIOEEN; 	// Enable clock on GPIO port E
	
	//DAC Clock
	RCC->APB1ENR |= RCC_APB1ENR_DAC1EN; // enable APB1 clock
	
	//LEDS GPIOE
	
	GPIOE->MODER |= 0x55550000; // Set mode of each pin in port E
	GPIOE->OTYPER &= ~(0x00000000); // Set output type for each pin required in Port E
	GPIOE->PUPDR &= ~(0xffff0000); // Set Pull up/Pull down resistor configuration for Port E
	
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; 	// Enable clock on GPIO port A
	
	DAC1->CR |= DAC_CR_BOFF1; //disable buffer for DAC register
	DAC1->CR |= DAC_CR_EN1; //enable DAC peripheral
	
	//GPIOA DAC(4 Analog) + ADC(0 Analog) Setup
	GPIOA->MODER |= 0x00000303; // Set mode of each pin in port A
	GPIOA->OTYPER &= ~(0x00000000); // Set output type for each pin required in Port A
	GPIOA->PUPDR &= ~(0x00000000); // Set Pull up/Pull down resistor configuration for Port A
	
	while (1)
  {
		//GPIOE->BSRRL = (counter << 8); //shifts bits left by 8 spots, auto converts from decimal to hex
	}

	
	//ADC1 Setup
	ADC1->CR = 0x00000000; //reset
	ADC1->CR = 0x10000000; // enable voltage regulator

	delay(100);

	ADC1->CR = 0x50000000; //ADCALDIF = 1 and ADCAL = 1

	while(ADC1->CR == 0x50000000) //calibrate?
	{
		delay(10);
	}

	RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV2; //enable clock to adc?
	RCC->AHBENR |= RCC_AHBENR_ADC12EN;
	ADC1_2_COMMON->CCR |= 0x00010000;

}

void TIM3_IRQHandler()
{

if ((TIM3->SR & TIM_SR_UIF) !=0) // Check interrupt source is from  the ‘Update’ interrupt flag
{
	GPIOE->BSRRH = (0xFFFF); 
	counter++;
	DAC1->DHR12R1 = counter;
	GPIOE->BSRRL = DAC1->DHR12R1 << 8;
}

TIM3->SR &= ~TIM_SR_UIF; // Reset ‘Update’ interrupt flag in the SR register
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






















