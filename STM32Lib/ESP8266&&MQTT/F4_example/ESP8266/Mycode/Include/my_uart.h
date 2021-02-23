/*
 * my_uart.h
 *
 *  Created on: 2021��1��26��
 *      Author: 27321
 */

#ifndef INC_MY_UART_H_
#define INC_MY_UART_H_

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "main.h"
#include "usart.h"
#include "esp8266_at.h"



//ѡ��ʹ�ܴ���BUFF
#define	UART1_BUFF_EN	0
#define	UART2_BUFF_EN	1
#define	UART3_BUFF_EN	1
#define	UART4_BUFF_EN	0
#define	UART5_BUFF_EN	0
#define	UART6_BUFF_EN	0
#define	UART7_BUFF_EN	0
#define	UART8_BUFF_EN	0

//����BUFF��С
#define UART_RX_BUF_SIZE	1024
extern	char RxDMABuff2[UART_RX_BUF_SIZE];

//DMA_IDLE��ʽ��ʼ����������������MX_USARTx_UART_Init()��
void UART1_DMA_IDLE_Start(void);
void UART2_DMA_IDLE_Start(void);
void UART3_DMA_IDLE_Start(void);
void UART4_DMA_IDLE_Start(void);
void UART5_DMA_IDLE_Start(void);
void UART6_DMA_IDLE_Start(void);
void UART7_DMA_IDLE_Start(void);
void UART8_DMA_IDLE_Start(void);

//��������
void UART_IDLE_Callback(UART_HandleTypeDef *uart);	//����IDLE�жϻص�����

void UartSendString(UART_HandleTypeDef *uart, char string[]);	//�������ⳤ���ַ���


void printf3(char * fmt,...);
#endif /* INC_MY_UART_H_ */


