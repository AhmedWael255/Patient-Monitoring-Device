/*
 * USART_interface.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Askar
 */

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

void USART_inti(); //initialization of USART comm. protocol
uint8 USART_ReceiveDataPolling(); // receive data polling on RXC flag
uint8 USART_ReceiveDataINT(); // receive data with RXC interrupt, WARNING ENABLE RXC INT
void USART_ReceieveStr(uint8* str_data, uint8 number);
void USART_SendStr(uint8* str_data);
void USART_SendInteger(volatile uint16 Copy_u16Number);
void USART_SendDataPolling(uint8 data); // send data polling on UDRE flag
void USART_SendDataINT(uint8 data); // send data with UDRE interrupt, WARNING ENABLE UDRE INT
void USART_EnableRx(); // enable rx during runtime
void USART_DisableRx(); // disable rx during runtime
void USART_EnableTx(); // enable tx during runtime
void USART_DisableTx(); // disable tx during runtime
void USART_SendStr(uint8* str_data); // send string or array

#endif /* USART_INTERFACE_H_ */
