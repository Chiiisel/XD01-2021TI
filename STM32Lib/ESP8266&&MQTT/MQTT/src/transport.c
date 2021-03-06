/*
 * 		Name:	transport.c
 *
 *  	Created on: 2021年2月21日
 *      Author: cHisel
 *     	Description:
 *
 *		功	  能：	MQTT的函数库
 *   	使用方法：	该文件是MQTT协议中唯一需要修改的的地方，已经适配ESP8266
 *					transport_sendPacketBuffer和transport_getdata函数，这两个函数
 *					是MQTT操作单片机发送和接受数据的主要函数
 *					需要包含头文件esp8266.h
 *
 */

#include "transport.h"


/***********************函数定义********************************/




int transport_sendPacketBuffer(int sock, unsigned char* buf, int buflen)
{
	UsartType.RX_flag = 0;
	memset(UsartType.RX_pData, 0, UsartType.RX_Size);
	HAL_UART_Transmit(&EspUart, buf, buflen, 1000);
	return buflen;
}


int transport_getdata(unsigned char* buf, int count)
{
	while(1){
		if (UsartType.RX_flag == 1) {
			memcpy(buf,UsartType.RX_pData, count);
			memset(UsartType.RX_pData, 0, count);
			break;
		}
		HAL_Delay(10);
//		PC_printf("Waiting for backdata");
	}
	return count;
}

int transport_getdatanb(void *sck, unsigned char* buf, int count)
{

	return 0;
}
int transport_open(char* addr, char* port)
{
	ESP8266_Link_Server(enumTCP, addr, port, 5);
	return 0;
}

int transport_close(int sock)
{
	ESP8266_ExitUnvarnishSend();
	ESP8266_Cmd("AT+CIPSTATUS", "OK", NULL , 1000);
	ESP8266_Cmd("AT+CIPCLOSE", "OK", "CLOSED", 1000);

	return 0;
}
