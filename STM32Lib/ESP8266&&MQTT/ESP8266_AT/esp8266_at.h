/*
 * 	Name:esp8266_at.h
 *
 *  Created on: 2021年2月4日
 *      Author: cHisel
 *      PB11——Uart3Rx
 *      PD8	——Uart3Tx
 *      PD10——ESP_RST
 *      PA3	——ESP_Rx
 *      PA2	——ESP_Tx
 *      3V供电，EN接3V
 */

#ifndef __ESP8266_AT_H
#define __ESP8266_AT_H

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "my_uart.h"

/******************************* ESP8266 WIFI和服务器定义 ***************************/

#define WifiName			"TP-LINK_"
#define	 WifiPassword		"D2313..."
#define LocalAddress		"192.168.0.211"
#define LocalPort			"10666"
#define Iot_Address			"127.0.0.1"
#define Iot_Port			"1883"

#define IOT_DOMAIN_NAME "a1REnRPxsPv.iot-as-mqtt.cn-shanghai.aliyuncs.com"
#define IOT_PORTNUM 	"1883"
/******************************* ESP8266 数据类型定义 ***************************/

#define EspUart huart2	//配置ESP对应的串口号
#define PcUart huart3	//配置PC相连对应的串口号
#define RX_LEN 1024  //接收的数据不能大于RX_LEN
typedef struct
{
uint8_t  RX_flag;        //IDLE receive flag
uint16_t RX_Size;          //receive length
uint8_t  RX_pData[RX_LEN]; //DMA receive buffer
}ESP_RECEIVETYPE;			//接收数据的缓冲区定义

extern ESP_RECEIVETYPE UsartType;
extern uint8_t UartSendCmd_Flag;  //串口向esp8266发送指令的标志位

typedef enum{
  STA,
  AP,
  STA_AP
} ENUM_Net_ModeTypeDef;

typedef enum{
	OPEN = 0,
	WEP = 1,
	WPA_PSK = 2,
	WPA2_PSK = 3,
	WPA_WPA2_PSK = 4,
} ENUM_AP_PsdMode_TypeDef;

typedef enum{
	 enumTCP,
	 enumUDP,
} ENUM_NetPro_TypeDef;

typedef enum{
	Multiple_ID_0 = 0,
	Multiple_ID_1 = 1,
	Multiple_ID_2 = 2,
	Multiple_ID_3 = 3,
	Multiple_ID_4 = 4,
	Single_ID_0 = 5,
} ENUM_ID_NO_TypeDef;



/* Private defines -----------------------------------------------------------*/


/* 函数声明 */

bool ESP8266_Cmd ( char * cmd, char * reply1, char * reply2, uint32_t waittime );
bool ESP8266_AT_Test ( void );
bool ESP8266_Net_Mode_Choose ( ENUM_Net_ModeTypeDef enumMode );
bool ESP8266_JoinAP ( char * pSSID, char * pPassWord );
bool ESP8266_BuildAP ( char * pSSID, char * pPassWord, ENUM_AP_PsdMode_TypeDef enunPsdMode );
bool ESP8266_Enable_MultipleId ( FunctionalState enumEnUnvarnishTx );
bool ESP8266_Link_Server ( ENUM_NetPro_TypeDef enumE, char * ip, char * ComNum, ENUM_ID_NO_TypeDef id);
bool ESP8266_StartOrShutServer ( FunctionalState enumMode, char * pPortNum, char * pTimeOver );
bool ESP8266_UnvarnishSend ( void );
bool ESP8266_SendString ( FunctionalState enumEnUnvarnishTx, char * pStr, uint32_t ulStrLength, ENUM_ID_NO_TypeDef ucId );
uint8_t ESP8266_Get_LinkStatus ( void );
uint8_t ESP8266_Get_IdLinkStatus ( void );
uint8_t ESP8266_Inquire_ApIp ( char * pApIp, uint8_t ucArrayLength );
void ESP8266_Rst(void);
void ESP8266_ExitUnvarnishSend ( void );
bool ESP8266_Init(void);
void ESP8266_DefineValue(uint32_t rxLenth,char * RxDMABuffx);
void ESP_UartSendCmd(UART_HandleTypeDef *huart);
#endif  /* __ESP8266_AT_H */
