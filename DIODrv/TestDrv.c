/*

* TestDrv.c

 *
 *  Created on: Apr 15, 2021
 *      Author: Mohamed
 */
#include "StdTypes.h"
#include "DIODrv.h"

int main ()
{
	DIO_vidSetPortDir(B,OUTPUT);
	while (1)
	{
		DIO_vidWriteOnPort(B,50);
	}
	return 0;
}

