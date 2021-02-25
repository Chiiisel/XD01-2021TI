/*
 * my_uart.h
 *
 *  Created on: 2021年1月26日
 *      Author: 27321
 */

#ifndef INC_MY_UART_H_
#define INC_MY_UART_H_

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "main.h"
#include "usart.h"
#include "esp8266_at.h"



//选择使能串口BUFF
#define	UART1_BUFF_EN	0
#define	UART2_BUFF_EN	1
#define	UART3_BUFF_EN	1
#define	UART4_BUFF_EN	0
#define	UART5_BUFF_EN	0
#define	UART6_BUFF_EN	0
#define	UART7_BUFF_EN	0
#define	UART8_BUFF_EN	0

//定义BUFF大小
#define UART_RX_BUF_SIZE	1024
extern	char RxDMABuff2[UART_RX_BUF_SIZE];

//DMA_IDLE方式开始函数，放在主函数MX_USARTx_UART_Init()后
void UART1_DMA_IDLE_Start(void);
void UART2_DMA_IDLE_Start(void);
void UART3_DMA_IDLE_Start(void);
void UART4_DMA_IDLE_Start(void);
void UART5_DMA_IDLE_Start(void);
void UART6_DMA_IDLE_Start(void);
void UART7_DMA_IDLE_Start(void);
void UART8_DMA_IDLE_Start(void);

//函数声明
void UART_IDLE_Callback(UART_HandleTypeDef *uart);	//串口IDLE中断回调函数

void UartSendString(UART_HandleTypeDef *uart, char string[]);	//发送任意长度字符串


void printf3(char * fmt,...);
#endif /* INC_MY_UART_H_ */


