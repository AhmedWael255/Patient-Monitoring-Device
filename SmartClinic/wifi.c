/*
 * wifi.c
 *
 *  Created on: Apr 27, 2021
 *      Author: Mohamed
 */



#include"StdTypes.h"
#include "DIODrv.h"
#include"bit_math.h"
#include"USART_interface.h"
#include<util/delay.h>
#include "wifi.h"

void ESP8266_VidInit()
{
	//disable echo
	USART_SendStr( (uint8 *)"ATE0\r\n" );
	_delay_ms( 1000 );

	/* Sending AT Command To Check ESP8266 Is Working Or Not  */
	USART_SendStr( (uint8 *)"AT\r\n" );
	_delay_ms( 1000 );

	USART_SendStr( (uint8 *)"AT+CWMODE=1\r\n" );
	_delay_ms( 1000 );

	USART_SendStr( (uint8 *) "AT+CIPMODE=0\r\n" );
	_delay_ms( 1000 );

	USART_SendStr( (uint8 *) "AT+CIPMUX=0\r\n" );
	_delay_ms( 1000 );

}

void ESP8266_VidConnectToWiFi(uint8* SSID, uint8* Password)
{
	USART_SendStr( (uint8 *) "AT+CWJAP_CUR=\"" );
	USART_SendStr( (uint8 *) SSID );
	USART_SendStr( (uint8 *) "\",\"" );
	USART_SendStr( (uint8 *) Password);
	USART_SendStr( (uint8 *) "\"\r\n");
	_delay_ms( 11000 );
}

void ESP8266_VidConnectToSrvTcp(uint8* Copy_u8Domain, uint8* Copy_u8Port)
{
	USART_SendStr( (uint8 *) "AT+CIPSTART=\"TCP\",\"" );
	USART_SendStr( (uint8 *) Copy_u8Domain );
	USART_SendStr( (uint8 *) "\"," );
	USART_SendStr( (uint8 *) Copy_u8Port );
	USART_SendStr( (uint8 *) "\r\n" );
	_delay_ms( 1000 );

}

uint8 ESP8266_u8GetHB(uint8* arr)
{
	uint8 result=0;
	uint8 i=0;
	ESP8266_VidConnectToSrvTcp ("162.253.155.226", "80" );
	USART_SendStr( (uint8 *) "AT+CIPSEND=55\r\n" );
	_delay_ms( 10 );

	USART_SendStr( (uint8 *) "GET http://eece2022.freevar.com/RecieverHB.php?line=0\r\n");

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
uint8 ESP8266_u8GetPR(uint8* arr)
{
	uint8 result=0;
	uint8 i=0;
	ESP8266_VidConnectToSrvTcp ("162.253.155.226", "80" );
	USART_SendStr( (uint8 *) "AT+CIPSEND=55\r\n" );
	_delay_ms( 10 );

	USART_SendStr( (uint8 *) "GET http://eece2022.freevar.com/RecieverPR.php?line=0\r\n");

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

void ESP8266_VidSendHB(uint8 Copy_u8HB)
{
	ESP8266_VidConnectToSrvTcp ("162.253.155.226", "80" );
	if(((Copy_u8HB/10)/10)==0)
	{
		USART_SendStr( (uint8 *) "AT+CIPSEND=59\r\n" );
	}
	else
	{
		USART_SendStr( (uint8 *) "AT+CIPSEND=60\r\n" );
	}
	_delay_ms( 10 );

	USART_SendStr( (uint8 *) "GET http://eece2022.freevar.com/TransmitterHB.php?data=");
	USART_SendInteger(Copy_u8HB);
	USART_SendStr((uint8 *)"\r\n");
	_delay_ms( 1000 );

}
void ESP8266_VidSendPR(uint8 Copy_u8PR)
{
	ESP8266_VidConnectToSrvTcp ("162.253.155.226", "80" );
	if(((Copy_u8PR/10)/10)==0)
	{
		USART_SendStr( (uint8 *) "AT+CIPSEND=59\r\n" );
	}
	else
	{
		USART_SendStr( (uint8 *) "AT+CIPSEND=60\r\n" );
	}
	_delay_ms( 10 );

	USART_SendStr( (uint8 *) "GET http://eece2022.freevar.com/TransmitterPR.php?data=");
	USART_SendInteger(Copy_u8PR);
	USART_SendStr((uint8 *)"\r\n");
	_delay_ms( 1000 );

}

