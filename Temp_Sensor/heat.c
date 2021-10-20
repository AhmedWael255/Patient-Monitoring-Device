/*
 * main.c
 *
 *  Created on: Apr 19, 2021
 *      Author: Mohamed
 */

#include <avr/io.h>
#include <avr/delay.h>

#define Temp_Channel 0

#define SetBit(Var,BitNum) (Var|=(1<<BitNum))
#define ClrBit(Var,BitNum) (Var&=~(1<<BitNum))

void ADC_Temp_Init(void);
int ADC_Read(char channel);


int main() {
	int temp ;


	ADC_Temp_Init();   //this is want to call when i start

	DDRB=0xFF;

	while (1)
	{
	temp=ADC_Read(Temp_Channel)*2.5; // 2.5 is the step size 2.5mV
	temp/=10; // LM35 return 10mv / celsius
	PORTB=temp;  // display the heat on the leds
	_delay_ms(100);
	}

}

void ADC_Temp_Init(void)
{
	ClrBit(DDRA,Temp_Channel);  // make ADC channel pin input
	ADCSRA=0x87;  // enable ADC with frequency 8M/128
	ADMUX=0xC0; //set reference 2.56v
}

int ADC_Read(char channel)
{
	ADMUX = 0xC0 | (channel & 0x07);   // set input channel to read
	ADCSRA |= (1<<ADSC);               // Start ADC conversion
	while (!(ADCSRA & (1<<ADIF)));     // Wait until end of conversion
	ADCSRA |= (1<<ADIF);               // Clear interrupt flag
	_delay_ms(1);
	return ADCL;                       // Return ADC value
}




