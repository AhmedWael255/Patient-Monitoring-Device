/*
 * sensors.h
 *
 *  Created on: Apr 24, 2021
 *      Author: Mohamed
 */

#define Temp_Channel 1
#define Heart_Channel 0

#define SetBit(Var,BitNum) (Var|=(1<<BitNum))
#define ClrBit(Var,BitNum) (Var&=~(1<<BitNum))

extern void ADC_Init();
extern int ADC_Read(char channel);
