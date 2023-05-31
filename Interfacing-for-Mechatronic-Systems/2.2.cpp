
/*
  Pete Hubbard 2019
  Loughborough University
  WSC055 Lab 1
  V.2.0
  The following 'c' code presents an outline for you to adapt during the laboratory
*/#include "stm32f3xx.h" // Device header
#include <stdlib.h>
int ADCValue;
int count = 0;
void delay(int a); // prototype for delay function
void ADCSetup(void); //adc function
void ADCRead(void);
void LEDINTSetup(void);
void DACSetup(void);
void GPIOSetup(void);
void OpAmpStartUp(void);


int main(void)
{
	LEDINTSetup();
  ADCSetup();
	DACSetup();
	GPIOSetup();
	OpAmpStartUp();
  
	//GPIOE->BSRRH = (0xFFFF); 
	
	while (1)
  {
		ADCRead();
  }
} 

void GPIOSetup()
{
		  //GPIOE Clock
  RCC->AHBENR |= RCC_AHBENR_GPIOEEN;
	GPIOA->MODER |= 0x00000F00;

	
	GPIOE->PUPDR &= ~(0x00030000); // Set Pull up/Pull down resistor configuration for Port E
  GPIOE->MODER |= 0x55550000; //MAKE PINS 8 TO 15 OUTPUTS
  GPIOE->OTYPER &= ~(0x00000000); // make pins 8 to 15 push/pull
  // Main programme loop - make LED 4 (attached to pin PE.0) turn on and off

}

void OpAmpStartUp()
{
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; //OpAmp clock
	GPIOA->MODER |= 0x00000300;
	GPIOA->MODER |= 0x0000030;
	GPIOA->MODER |= 0x00000C00;
	//pin congig -> PA2 Analog, PA5, Input
	
	OPAMP1->CSR |= 0x00000001; //OpAmp enable
	OPAMP1->CSR |= 0x00000004; // PA.5 as non-inv. Input
	OPAMP1->CSR |= 0x00000040; // Set VM_SEL to 0b10 to enable PGA mode
	OPAMP1->CSR |= 0x0000C000; //PGA_GAIN bit value set
}

void DACSetup()
{
	 //DIGITAL TO ANALOGUE CONVERSION SETUP
  RCC->APB1ENR |= RCC_APB1ENR_DAC1EN; //connect the DAC to the system clock via the APB1 peripheral clock bus
  //configure PA4, PA5 or PA6 to 'analogue mode'

  //CHANNEL 1
  DAC1->CR |= DAC_CR_BOFF1; //disable the 'buffer' function in the DAC control register
  DAC1->CR |= DAC_CR_EN1; //enable DAC peripheral
  //CHANNEL 2
  //RCC->APB1ENR |= RCC_APB1ENR_DAC2EN; //connect the DAC to the system clock via the APB1 peripheral clock bus
  //DAC2->CR |= DAC_CR_BOFF2; //disable the 'buffer' function in the DAC control register
  //DAC2->CR |= DAC_CR_EN2; //enable DAC peripheral
  //make pin 8 has an open drain arrangement and pin 12 has the push/pull arrangement
}

void LEDINTSetup()
{
//LED Timer and interrup setup 
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;//Direct clock pulses to the timer
  TIM3->PSC = 79; // prescalor value in Timer ‘3’ as 99
  TIM3->ARR = 9999; // Auto-Reset Register of Timer ‘3’ set to 7999 counts
  TIM3->CR1 |= TIM_CR1_CEN;  // timer start
  
	//Timer Interrupt setup
	TIM3->DIER |= TIM_DIER_UIE; // Set DIER register to watch out for an ‘Update’ Interrupt Enable (UIE) – or 0x00000001
  NVIC_EnableIRQ(TIM3_IRQn); // Enable Timer ‘x’ interrupt request in NVIC
}

void LEDtimerSetup()
{
	//LED Timer Setup
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; //timer for LEDs
	TIM3->PSC = 7999; // prescalor value in Timer ‘x’ as 100
	TIM3->ARR = 9999; // Auto-Reset Register of Timer ‘x’ set to 1000 counts
	TIM3->CR1 |= TIM_CR1_CEN; // timer start
	
	//Timer Interrupt setup
	TIM3->DIER |= TIM_DIER_UIE; // Set DIER register to watch out for an ‘Update’ Interrupt Enable (UIE) – or 0x00000001
	NVIC_EnableIRQ(TIM3_IRQn); // Enable Timer ‘x’ interrupt request in NVIC
}

// Delay function to occupy processor
void delay (int a)
{
		for (int i=0 ; i < a ; i++);

		return;
}

void ADCRead()
{
	  DAC1->DOR1 = DAC_DHR12R1_DACC1DHR; //8 bit right aligned holding register
    //start the adc by setting ADSTART bit high
    ADC1 -> CR |= 0x00000004;
    //check if EOC bit in ACD1_ISR register is high
    while (!(ADC1 -> ISR & ADC_ISR_EOC));
	
	ADC1->ISR &= ~(ADC_ISR_EOC); //not in kieran
    //read value from register
    ADCValue = ADC1->DR &= 0x000000FF;
}

void TIM3_IRQHandler()
{
  if ((TIM3->SR & TIM_SR_UIF) != 0) // Check interrupt source is from the ‘Update’ interrupt flag
  {
		if (count > 256){
			count = 0;
		}
		GPIOE->BSRRH |= (0xFFFF);
    count++;
    DAC1->DHR12R1 = count;
		GPIOE->BSRRL |= ADCValue << 8;
  }
  TIM3->SR &= ~TIM_SR_UIF; // Reset ‘Update’ interrupt flag in the SR register
} 

void ADCSetup(void)
{
  //START UP PROCEDURE FOR ADC
  //enable voltage regulator; 'reset' then enable by writing '0b00' then '0b01' to ADVREGEN part of ADCx_CR
  ADC1->CR &= ~(0x30000000);
  ADC1->CR |= 0x10000000;
  
	//wait 10 useconds, which can be done using a while loop that counts to 100
	delay(100);
	
  //calibrate the ADC using the ADC1_CR
  //adc define calibration setting (single or double ended)
  ADC1 -> CR |= 0x40000000; //double ended - sets the ADCALDIF bit to 1
  
	//to start calibration, write 1 to ADCAL bit
  ADC1-> CR |= 0x80000000;
  
	//enable clock connection - point peripherals clock to ADC1
  RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV2;
  RCC->AHBENR |= RCC_AHBENR_ADC12EN;
  ADC1_2_COMMON->CCR |= 0x00010000;
  
	//enable the clock to the appropriate GPIO port
  RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
  GPIOC -> MODER |= 0x0000000C; //sets channel ADC1_IN1 to analogue mode, corresponding to PC.1
  
	//configure ADC to 8bit resoltion, right hand alignment, not continuous operation
  ADC1 -> CFGR &= ~(0x2000); //sets to continuous
  ADC1 -> CFGR &= ~(0x0020); //sets to right aligned
  ADC1 -> CFGR |= 0x0010; //8bit resolution setting RES[1:0] to "0b10"
  
	//configure the multiplexing options
  //start by writing order of channels to be sampled in ADC1_SQR
  ADC1 -> SQR1 |= ADC_SQR1_SQ1_2 | ADC_SQR1_SQ1_1 | ADC_SQR1_SQ1_0 ; //channel 7 in SQ1 section
  //define sample time for each channel
  ADC1 -> SQR1 |= ADC_SQR1_L_0; //length of the sequence to be '1'
  //define sample time for the sampled channel by setting the value in SMP1 in the ADC1_SMPR1 register
  ADC1 ->SMPR1 |= ADC_SMPR1_SMP1_1 | ADC_SMPR1_SMP1_0; //sets channel as first and only input, at 7.5 ADC clock cycles
  
	//enable ADC
  ADC1 -> CR |= 0x00000001; //sets ADSTART bit high in ADC1_CR
  
	//wait for ARDDY flag to go high
  while (!ADC1 -> ISR & ADC_ISR_ADRD);  //sits in the while loop until the ISR is triggered return;
}


















