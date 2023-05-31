/* 
	Pete Hubbard 2019
	Loughborough University
	WSC055 Lab 1
	V.2.0
	
	The following 'c' code presents an outline for you to adapt during the laboratory
	
	*/

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
		delay(20000);
		GPIOE->BSRRH = (counter << 8); 
		delay(20000);
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
