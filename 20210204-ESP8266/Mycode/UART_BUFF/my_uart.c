/*
 * my_uart.c
 *
 *  Created on: 2021年1月26日
 *      Author: 27321
 *     	Description:
 *
 *		功能：		通过串口IDLE中断和DMA实现任意长度数据接收
 *   	使用方法：	CubeMX配置时保持串口DMA设置默认。
 *					在my_uart.h中使能需要使用的串口；
 *     				将回调函数UART_IDLE_Callback(&huartx)添加在stm32fxxx_it.c的USARTx_IRQHandler()中；
 *     				在主函数while(1)之前调用UARTx_DMA_IDLE_Start()；
 *					在对应的UARTx_rxFunction()中编写自己的用户函数。
 *
 */



/* Includes ------------------------------------------------------------------*/

#include "my_uart.h"

/* Private define ------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
/*
 * 	选择串口接收缓冲区开关
 */
#if UART1_BUFF_EN == 1
	char RxDMABuff1[UART_RX_BUF_SIZE] = {0};
#endif

#if UART2_BUFF_EN == 1
	char RxDMABuff2[UART_RX_BUF_SIZE] = {0};
#endif

#if UART3_BUFF_EN == 1
	char RxDMABuff3[UART_RX_BUF_SIZE] = {0};
#endif

#if UART4_BUFF_EN == 1
	char RxDMABuff4[UART_RX_BUF_SIZE] = {0};
#endif

#if UART5_BUFF_EN == 1
	char RxDMABuff5[UART_RX_BUF_SIZE] = {0};
#endif

#if UART6_BUFF_EN == 1
	char RxDMABuff6[UART_RX_BUF_SIZE] = {0};
#endif

#if UART7_BUFF_EN == 1
	char RxDMABuff7[UART_RX_BUF_SIZE] = {0};
#endif

#if UART8_BUFF_EN == 1
	char RxDMABuff8[UART_RX_BUF_SIZE] = {0};
#endif

uint32_t rxLenth = 0;	//接收信息的长度

/* Private function prototypes -----------------------------------------------*/


/* Private user code ---------------------------------------------------------*/

/*
 * Function		: UartSendString
 * Description	: 发送任意长度的字符串
 */
void UartSendString(UART_HandleTypeDef *uart, char string[]){
	uint16_t lenth = 0;
	lenth = strlen(string);
	HAL_UART_Transmit(uart, string, lenth, 1000);

	while(__HAL_UART_GET_FLAG(uart,	UART_FLAG_TC) == RESET);
}

/*
 * Function		: UARTx_DMA_IDLE_Start
 * Description	: UARTx的DMA_IDLE方式接收初始化函数，放在MX_USARTx_UART_Init()后
 */
#if UART1_BUFF_EN == 1
void UART1_DMA_IDLE_Start(void){
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
	HAL_UART_Receive_DMA(&huart1, RxDMABuff1, UART_RX_BUF_SIZE);
}
#endif

#if UART2_BUFF_EN == 1
void UART2_DMA_IDLE_Start(void){
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);
	HAL_UART_Receive_DMA(&huart2, RxDMABuff2, UART_RX_BUF_SIZE);
}
#endif

#if UART3_BUFF_EN == 1
void UART3_DMA_IDLE_Start(void){
	__HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);
	HAL_UART_Receive_DMA(&huart3, RxDMABuff3, UART_RX_BUF_SIZE);
}
#endif

#if UART4_BUFF_EN == 1
void UART4_DMA_IDLE_Start(void){
	__HAL_UART_ENABLE_IT(&huart4, UART_IT_IDLE);
	HAL_UART_Receive_DMA(&huart4, RxDMABuff4, UART_RX_BUF_SIZE);
}
#endif

#if UART5_BUFF_EN == 1
void UART5_DMA_IDLE_Start(void){
	__HAL_UART_ENABLE_IT(&huart5, UART_IT_IDLE);
	HAL_UART_Receive_DMA(&huart5, RxDMABuff5, UART_RX_BUF_SIZE);
}
#endif

#if UART6_BUFF_EN == 1
void UART6_DMA_IDLE_Start(void){
	__HAL_UART_ENABLE_IT(&huart6, UART_IT_IDLE);
	HAL_UART_Receive_DMA(&huart6, RxDMABuff6, UART_RX_BUF_SIZE);
}
#endif

#if UART7_BUFF_EN == 1
void UART7_DMA_IDLE_Start(void){
	__HAL_UART_ENABLE_IT(&huart7, UART_IT_IDLE);
	HAL_UART_Receive_DMA(&huart7, RxDMABuff7, UART_RX_BUF_SIZE);
}
#endif

#if UART8_BUFF_EN == 1
void UART8_DMA_IDLE_Start(void){
	__HAL_UART_ENABLE_IT(&huart8, UART_IT_IDLE);
	HAL_UART_Receive_DMA(&huart8, RxDMABuff8, UART_RX_BUF_SIZE);
}
#endif



/*
 * Function		:	UARTx_rxFunction
 * Description	:	UARTx接收数据后的用户函数
 */
#if UART1_BUFF_EN == 1
static void UART1_rxFunction(void){

	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	HAL_UART_Receive_DMA(&huart1, RxDMABuff1, UART_RX_BUF_SIZE);	//重启DMA接收
}
#endif

#if UART2_BUFF_EN == 1
static void UART2_rxFunction(void){

	/* USER CODE BEGIN 2 */
	UsartType.RX_Size = rxLenth;
	UsartType.RX_flag =1;
	strcpy(UsartType.RX_pData,RxDMABuff2);
	UsartType.RX_pData[UsartType.RX_Size]='\0';
	UartSendString(&huart3, UsartType.RX_pData);
	/* USER CODE END 2 */
	HAL_UART_Receive_DMA(&huart2, RxDMABuff2, UART_RX_BUF_SIZE);	//重启DMA接收
}
#endif

#if UART3_BUFF_EN == 1
static void UART3_rxFunction(void){

	/* USER CODE BEGIN 3 */
	//ESP8266_SendString(1, RxDMABuff3, 0, 0);    //透传模式通过串口3发送字符串
	UartSendString(&huart2, RxDMABuff3);
	/* USER CODE END 3 */
	HAL_UART_Receive_DMA(&huart3, RxDMABuff3, UART_RX_BUF_SIZE);	//重启DMA接收
}
#endif

#if UART4_BUFF_EN == 1
static void UART4_rxFunction(void){

	/* USER CODE BEGIN 4 */

	/* USER CODE END 4 */
	HAL_UART_Receive_DMA(&huart4, RxDMABuff4, UART_RX_BUF_SIZE);	//重启DMA接收
}
#endif

#if UART5_BUFF_EN == 1
static void UART5_rxFunction(void){

	/* USER CODE BEGIN 5 */

	/* USER CODE END 5 */
	HAL_UART_Receive_DMA(&huart5, RxDMABuff5, UART_RX_BUF_SIZE);	//重启DMA接收
}
#endif

#if UART6_BUFF_EN == 1
static void UART6_rxFunction(void){

	/* USER CODE BEGIN 6 */

	/* USER CODE END 6 */
	HAL_UART_Receive_DMA(&huart6, RxDMABuff6, UART_RX_BUF_SIZE);	//重启DMA接收
}
#endif

#if UART7_BUFF_EN == 1
static void UART7_rxFunction(void){

	/* USER CODE BEGIN 7 */

	/* USER CODE END 7 */
	HAL_UART_Receive_DMA(&huart7, RxDMABuff7, UART_RX_BUF_SIZE);	//重启DMA接收
}
#endif

#if UART8_BUFF_EN == 1
static void UART8_rxFunction(void){

	/* USER CODE BEGIN 8 */

	/* USER CODE END 8 */
	HAL_UART_Receive_DMA(&huart8, RxDMABuff8, UART_RX_BUF_SIZE);	//重启DMA接收
}
#endif

/*
 * Function		:	UART_UserFunction
 * Description	:	串口IDLE中断发生后，判断是哪个串口接收的数据，进而进入对应的用户函数
 */
static void UART_UserFunction(UART_HandleTypeDef *uart){
#if UART1_BUFF_EN == 1
	if(uart == (&huart1)){
		UART1_rxFunction();
	}
#endif

#if UART2_BUFF_EN == 1
	if(uart == (&huart2)){
		UART2_rxFunction();
	}
#endif

#if UART3_BUFF_EN == 1
	if(uart == (&huart3)){
		UART3_rxFunction();
	}
#endif

#if UART4_BUFF_EN == 1
	if(uart == (&huart4)){
		UART4_rxFunction();
	}
#endif

#if UART5_BUFF_EN == 1
	if(uart == (&huart5)){
		UART5_rxFunction();
	}
#endif

#if UART6_BUFF_EN == 1
	if(uart == (&huart6)){
		UART6_rxFunction();
	}
#endif

#if UART7_BUFF_EN == 1
	if(uart == (&huart7)){
		UART7_rxFunction();
	}
#endif
}

#if UART8_BUFF_EN == 1
	if(uart == (&huart8)){
		UART8_rxFunction();
	}
#endif

	/*
	 * Function		: UART_IDLE_Callback
	 * Description	: UART自建回调函数，需要加在stm32f1xx_it.c的USARTx_IRQHandler中！
	 */
void UART_IDLE_Callback(UART_HandleTypeDef *uart){
	uint32_t tmp_flag = 0;
	uint32_t temp;
	tmp_flag = __HAL_UART_GET_FLAG(uart, UART_FLAG_IDLE);	//获取IDLE标志位
	if(tmp_flag != RESET){
		__HAL_UART_CLEAR_IDLEFLAG(uart);			//清除IDLE标志位
		temp = uart->Instance->SR;					//读取SR寄存器即可清空SR寄存器的值
		temp = uart->Instance->DR;					//读取DR寄存器的数据
		HAL_UART_DMAStop(uart);						//暂时关闭DMA方便计数
		/*  F4系列使用NDTR   其他使用CNDTR */
		temp = uart->hdmarx->Instance->NDTR;		//获取DMA中未传输的数据个数
		rxLenth = UART_RX_BUF_SIZE - temp;			//得到接收到数据的长度
		UART_UserFunction(uart);					//判断是哪个串口接收的数据，并进入相应的用户函数
		rxLenth = 0;
	}
}


void printf3(char * fmt,...)
{
    char buffer[100];
    uint16_t i=0;
    va_list arg_ptr;
    va_start(arg_ptr,fmt);
    vsnprintf(buffer,100,fmt,arg_ptr);
    while(i<99&&buffer[i])
    {
        HAL_UART_Transmit(&huart3,(uint8_t *)&buffer[i],1,0xFFFF);
        i++;
    }
    va_end(arg_ptr);
}
