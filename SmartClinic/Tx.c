/*
 * Tx.c
 *
 *  Created on: Apr 24, 2021
 *      Author: Mohamed
 */
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "string.h"
#include "StdTypes.h"
#include "DIODrv.h"
#include "LCD.h"
#include "sensors.h"
#include "wifi.h"

int main ()
{
	unsigned int temp , bpm , thresh=350 , time_limit=10 ,HrtVal;
	float sampling_rate=100; // frequency
	unsigned int avg;


	ADC_Init(Temp_Channel);
	ADC_Init(Heart_Channel);
	LCD_vidInit();


	//Initialization
		DIO_vidSetPinDir( PORTD,  PIN0,  INPUT); //Rx
		DIO_vidSetPinDir( PORTD,  PIN1,  OUTPUT); //Tx
		DIO_vidSetPinDir( RESET_PORT,  RESET_PIN,  OUTPUT); //Reset pin
	  USART_inti();
	  DIO_vidWriteOnPin(RESET_PORT,RESET_PIN,LOW);
	  _delay_ms( 100 );
	  DIO_vidWriteOnPin(RESET_PORT,RESET_PIN,HIGH);
	  _delay_ms( 1000 );

	  ESP8266_VidInit();


	  //connect
	  ESP8266_VidConnectToWiFi("OPPO Reno2","11112222");



	while (1)
	{
		/*Heart Beat Sensor Part*/
		bpm=0;
		avg=0;

		char test1[3]={0,0,0};
		char test2[3]={0,0,0};

		LCD_vidDispString((uint8 *)"Please Wait");

		for(int i=0 ; i<10000; i++)
		{
			HrtVal = ADC_Read(Heart_Channel);  //read from channel zero
			avg+=HrtVal;
			if(HrtVal>29)
			{
				bpm+=1; //peak counting , it counts every time it reaches to peak
			}


			_delay_ms(1);

		}

		avg/=1000;
		bpm*=6;
		LCD_vidCmd(CMD_CLEAR);
		LCD_vidCmd(CMD_HOME);


		/*Send bpm value */
		ESP8266_VidSendPR(bpm);



		/*Temp Sensor part */

		temp=ADC_Read(Temp_Channel)*4.88; // 4.88 is the step size 4.88mV
		temp/=10; // LM35 return 10mv / celsius

		/* Send Temprature value*/
		ESP8266_VidSendHB(temp);


		/*test using lcd*/

		LCD_vidDispString((uint8 *)"bpm = ");
		itoa(ADC_Read(Heart_Channel),test1,10);
		LCD_vidDispString((uint8*)test1);

		LCD_vidCmd(0xC0);

		LCD_vidDispString((uint8 *)"avg =");
		itoa(avg,test2,10);
		LCD_vidDispString((uint8*)test2);

		_delay_ms(1000);
		LCD_vidCmd(CMD_CLEAR);
		LCD_vidCmd(CMD_HOME);

	}

}



