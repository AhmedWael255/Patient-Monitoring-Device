/*
 * wifi.h
 *
 *  Created on: Apr 27, 2021
 *      Author: Mohamed
 */

#ifndef WIFI_H_
#define WIFI_H_


#define RESET_PORT PORTA
#define RESET_PIN PIN0


extern void ESP8266_VidInit(void);
extern void ESP8266_VidConnectToWiFi( uint8* SSID,  uint8* Password);
extern void ESP8266_VidConnectToSrvTcp( uint8* Copy_u8Domain,  uint8* Copy_u8Port);
extern uint8 ESP8266_u8GetHB( uint8* arr);
extern uint8 ESP8266_u8GetPR( uint8* arr);
extern void ESP8266_VidSendHB( uint8 Copy_u8HB);
extern void ESP8266_VidSendPR( uint8 Copy_u8PR);


#endif /* WIFI_H_ */
