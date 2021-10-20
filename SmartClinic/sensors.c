/*
 * sensors.c
 *
 *  Created on: Apr 24, 2021
 *      Author: Mohamed
 */
#include <avr/io.h>
#include <util/delay.h>
#include "sensors.h"


void ADC_Init()
{
	ClrBit(DDRA,Temp_Channel);  // make ADC channel pin input for heat
	ClrBit(DDRA,Heart_Channel);  // make ADC channel pin input for heart
	ADCSRA=0x87;  // enable ADC with frequency 8M/128
	ADMUX=0x40; //set reference VCC
}

int ADC_Read(char channel){
	int Ain,AinLow;

	ADMUX=ADMUX|(channel & 0x0f);	/* Set input channel to read */

	ADCSRA |= (1<<ADSC);		/* Start conversion */
	while((ADCSRA&(1<<ADIF))==0);	/* Monitor end of conversion interrupt */
	_delay_us(10);
	AinLow = (int)ADCL;		/* Read lower byte*/
	ADCH&=(3);
	Ain = (int)(4<<ADCH);		/* Read higher 2 bits and Multiply with weight */
	Ain = Ain + AinLow;
	return(Ain);			/* Return digital value*/
}




