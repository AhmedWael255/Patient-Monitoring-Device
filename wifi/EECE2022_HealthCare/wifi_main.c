/*
 * main.c

 *
 *  Created on: ??þ/??þ/????
 *      Author: Askar
 */

#define F_CPU 8000000UL
#define RESET_PORT PORTA
#define RESET_PIN PIN0
#include"std_types.h"
#include"bit_math.h"
#include"DIO_interface.h"
#include"USART_interface.h"
#include<avr/delay.h>

void ESP8266_VidInit();
void ESP8266_VidConnectToWiFi(u8* SSID, u8* Password);
void ESP8266_VidConnectToSrvTcp(u8* Copy_u8Domain, u8* Copy_u8Port);
u8 ESP8266_u8GetHB(u8* arr);
u8 ESP8266_u8GetPR(u8* arr);
void ESP8266_VidSendHB(u8 Copy_u8HB);
void ESP8266_VidSendPR(u8 Copy_u8PR);

void main(void)
{

	//here put your transmitted data//
	volatile u8 heart_beat_sensor=100;
	volatile u8 heat_sensor=200;


	//here you will get the recived data
	volatile u8 z[100]={0};
	volatile u8 m[100]={0};
	volatile u8 heart_beat=0;
	volatile u8 heat=0;


	////Initialization////
	DIO_SetPinDir( PORTD,  PIN0,  INPUT); //Rx
	DIO_SetPinDir( PORTD,  PIN1,  OUTPUT); //Tx
	DIO_SetPinDir( RESET_PORT,  RESET_PIN,  OUTPUT); //Reset pin
	USART_inti();
	DIO_SetPinVal(RESET_PORT,RESET_PIN,LOW);
	_delay_ms( 100 );
	DIO_SetPinVal(RESET_PORT,RESET_PIN,HIGH);
	_delay_ms( 1000 );
	ESP8266_VidInit();
	/////////////////////////////////////////////////////////////////////////

	//connect
	ESP8266_VidConnectToWiFi("sayed","11112222"); //put your name and password of your hotspots mobile ,the name should be characters only and password is numbers only





	//transmit
	ESP8266_VidSendPR(heat_sensor);
	ESP8266_VidSendHB(heart_beat_sensor);





	//receive
	heat=ESP8266_u8GetPR(z);
	heart_beat=ESP8266_u8GetHB(m);






	while(1);
}









void ESP8266_VidInit()
{
	//disable echo
	USART_SendStr( (u8 *)"ATE0\r\n" );
	_delay_ms( 1000 );

	/* Sending AT Command To Check ESP8266 Is Working Or Not  */
	USART_SendStr( (u8 *)"AT\r\n" );
	_delay_ms( 1000 );

	USART_SendStr( (u8 *)"AT+CWMODE=1\r\n" );
	_delay_ms( 1000 );

	USART_SendStr( (u8 *) "AT+CIPMODE=0\r\n" );
	_delay_ms( 1000 );

	USART_SendStr( (u8 *) "AT+CIPMUX=0\r\n" );
	_delay_ms( 1000 );

}

void ESP8266_VidConnectToWiFi(u8* SSID, u8* Password)
{
	USART_SendStr( (u8 *) "AT+CWJAP_CUR=\"" );
	USART_SendStr( (u8 *) SSID );
	USART_SendStr( (u8 *) "\",\"" );
	USART_SendStr( (u8 *) Password);
	USART_SendStr( (u8 *) "\"\r\n");
	_delay_ms( 1000 );
	_delay_ms( 1000 );
	_delay_ms( 1000 );
	_delay_ms( 1000 );
	_delay_ms( 1000 );
	_delay_ms( 1000 );
	_delay_ms( 1000 );
	_delay_ms( 1000 );
	_delay_ms( 1000 );
	_delay_ms( 1000 );
	_delay_ms( 1000 );
	_delay_ms( 1000 );
	_delay_ms( 1000 );

}

void ESP8266_VidConnectToSrvTcp(u8* Copy_u8Domain, u8* Copy_u8Port)
{
	USART_SendStr( (u8 *) "AT+CIPSTART=\"TCP\",\"" );
	USART_SendStr( (u8 *) Copy_u8Domain );
	USART_SendStr( (u8 *) "\"," );
	USART_SendStr( (u8 *) Copy_u8Port );
	USART_SendStr( (u8 *) "\r\n" );
	_delay_ms( 1000 );

}

u8 ESP8266_u8GetHB(u8* arr)
{
	u8 result=0;
	u8 i=0;
	ESP8266_VidConnectToSrvTcp ("162.253.155.226", "80" );
	USART_SendStr( (u8 *) "AT+CIPSEND=55\r\n" );
	_delay_ms( 100 );
	_delay_ms( 100 );

	USART_SendStr( (u8 *) "GET http://eece2023.freevar.com/RecieverHB.php?line=0\r\n");

	for(i=0;i<45;i++)
	{
		arr[i]=USART_ReceiveDataPolling();
	}
	result = (arr[38]-48)*10+(arr[39]-48);
	if(arr[40]>47 && arr[40]<58)
	{
		result = (arr[38]-48)*100+(arr[39]-48)*10+(arr[40]-48);
	}
	return result;
}
u8 ESP8266_u8GetPR(u8* arr)
{
	u8 result=0;
	u8 i=0;
	ESP8266_VidConnectToSrvTcp ("162.253.155.226", "80" );
	USART_SendStr( (u8 *) "AT+CIPSEND=55\r\n" );
	_delay_ms( 100 );
	_delay_ms( 100 );

	USART_SendStr( (u8 *) "GET http://eece2023.freevar.com/RecieverPR.php?line=0\r\n");

	for(i=0;i<45;i++)
	{
		arr[i]=USART_ReceiveDataPolling();
	}
	result = (arr[38]-48)*10+(arr[39]-48);
	if(arr[40]>47 && arr[40]<58)
	{
		result = (arr[38]-48)*100+(arr[39]-48)*10+(arr[40]-48);
	}
	return result;
}

void ESP8266_VidSendHB(u8 Copy_u8HB)
{
	ESP8266_VidConnectToSrvTcp ("162.253.155.226", "80" );
	if(((Copy_u8HB/10)/10)==0)
	{
		USART_SendStr( (u8 *) "AT+CIPSEND=59\r\n" );
	}
	else
	{
		USART_SendStr( (u8 *) "AT+CIPSEND=60\r\n" );
	}
	_delay_ms( 100 );

	USART_SendStr( (u8 *) "GET http://eece2023.freevar.com/TransmitterHB.php?data=");
	USART_SendInteger(Copy_u8HB);
	USART_SendStr((u8 *)"\r\n");
	_delay_ms( 1000 );
	_delay_ms( 1000 );


}
void ESP8266_VidSendPR(u8 Copy_u8PR)
{
	ESP8266_VidConnectToSrvTcp ("162.253.155.226", "80" );
	if(((Copy_u8PR/10)/10)==0)
	{
		USART_SendStr( (u8 *) "AT+CIPSEND=59\r\n" );
	}
	else
	{
		USART_SendStr( (u8 *) "AT+CIPSEND=60\r\n" );
	}
	_delay_ms( 100 );

	USART_SendStr( (u8 *) "GET http://eece2023.freevar.com/TransmitterPR.php?data=");
	USART_SendInteger(Copy_u8PR);
	USART_SendStr((u8 *)"\r\n");
	_delay_ms( 1000 );
	_delay_ms( 1000 );


}
