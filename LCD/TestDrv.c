/*
 * TestDrv.c
 *
 *  Created on: Apr 24, 2021
 *      Author: Mohamed
 */
#include "StdTypes.h"
#undef F_CPU
#define F_CPU 8000000U
//#include <util/delay.h>
#include "DIODrv.h"
#include "LCD.h"

int main()
{
	LCD_vidInit();
	/*DIO_vidSetPinDir(B , PIN0 , OUTPUT);
	DIO_vidWriteOnPin(B , PIN0 , HIGH);*/

	LCD_vidDispString((uint8 *)"Hello World!");
	LCD_vidCmd(CMD_SECONED_LINE);
	LCD_vidDispString((uint8 *)"Hello");
	while (1)
	{

	}

}

