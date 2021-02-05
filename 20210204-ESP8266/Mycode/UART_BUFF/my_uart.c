/*
 * my_uart.c
 *
 *  Created on: 2021��1��26��
 *      Author: 27321
 *     	Description:
 *
 *		���ܣ�		ͨ������IDLE�жϺ�DMAʵ�����ⳤ�����ݽ���
 *   	ʹ�÷�����	CubeMX����ʱ���ִ���DMA����Ĭ�ϡ�
 *					��my_uart.h��ʹ����Ҫʹ�õĴ��ڣ�
 *     				���ص�����UART_IDLE_Callback(&huartx)�����stm32fxxx_it.c��USARTx_IRQHandler()�У�
 *     				��������while(1)֮ǰ����UARTx_DMA_IDLE_Start()��
 *					�ڶ�Ӧ��UARTx_rxFunction()�б�д�Լ����û�������
 *
 */



/* Includes ------------------------------------------------------------------*/

#include "my_uart.h"

/* Private define ------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
/*
 * 	ѡ�񴮿ڽ��ջ���������
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

uint32_t rxLenth = 0;	//������Ϣ�ĳ���

/* Private function prototypes -----------------------------------------------*/


/* Private user code ---------------------------------------------------------*/

/*
 * Function		: UartSendString
 * Description	: �������ⳤ�ȵ��ַ���
 */
void UartSendString(UART_HandleTypeDef *uart, char string[]){
	uint16_t lenth = 0;
	lenth = strlen(string);
	HAL_UART_Transmit(uart, string, lenth, 1000);

	while(__HAL_UART_GET_FLAG(uart,	UART_FLAG_TC) == RESET);
}

/*
 * Function		: UARTx_DMA_IDLE_Start
 * Description	: UARTx��DMA_IDLE��ʽ���ճ�ʼ������������MX_USARTx_UART_Init()��
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
 * Description	:	UARTx�������ݺ���û�����
 */
#if UART1_BUFF_EN == 1
static void UART1_rxFunction(void){

	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	HAL_UART_Receive_DMA(&huart1, RxDMABuff1, UART_RX_BUF_SIZE);	//����DMA����
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
	HAL_UART_Receive_DMA(&huart2, RxDMABuff2, UART_RX_BUF_SIZE);	//����DMA����
}
#endif

#if UART3_BUFF_EN == 1
static void UART3_rxFunction(void){

	/* USER CODE BEGIN 3 */
	//ESP8266_SendString(1, RxDMABuff3, 0, 0);    //͸��ģʽͨ������3�����ַ���
	UartSendString(&huart2, RxDMABuff3);
	/* USER CODE END 3 */
	HAL_UART_Receive_DMA(&huart3, RxDMABuff3, UART_RX_BUF_SIZE);	//����DMA����
}
#endif

#if UART4_BUFF_EN == 1
static void UART4_rxFunction(void){

	/* USER CODE BEGIN 4 */

	/* USER CODE END 4 */
	HAL_UART_Receive_DMA(&huart4, RxDMABuff4, UART_RX_BUF_SIZE);	//����DMA����
}
#endif

#if UART5_BUFF_EN == 1
static void UART5_rxFunction(void){

	/* USER CODE BEGIN 5 */

	/* USER CODE END 5 */
	HAL_UART_Receive_DMA(&huart5, RxDMABuff5, UART_RX_BUF_SIZE);	//����DMA����
}
#endif

#if UART6_BUFF_EN == 1
static void UART6_rxFunction(void){

	/* USER CODE BEGIN 6 */

	/* USER CODE END 6 */
	HAL_UART_Receive_DMA(&huart6, RxDMABuff6, UART_RX_BUF_SIZE);	//����DMA����
}
#endif

#if UART7_BUFF_EN == 1
static void UART7_rxFunction(void){

	/* USER CODE BEGIN 7 */

	/* USER CODE END 7 */
	HAL_UART_Receive_DMA(&huart7, RxDMABuff7, UART_RX_BUF_SIZE);	//����DMA����
}
#endif

#if UART8_BUFF_EN == 1
static void UART8_rxFunction(void){

	/* USER CODE BEGIN 8 */

	/* USER CODE END 8 */
	HAL_UART_Receive_DMA(&huart8, RxDMABuff8, UART_RX_BUF_SIZE);	//����DMA����
}
#endif

/*
 * Function		:	UART_UserFunction
 * Description	:	����IDLE�жϷ������ж����ĸ����ڽ��յ����ݣ����������Ӧ���û�����
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
	 * Description	: UART�Խ��ص���������Ҫ����stm32f1xx_it.c��USARTx_IRQHandler�У�
	 */
void UART_IDLE_Callback(UART_HandleTypeDef *uart){
	uint32_t tmp_flag = 0;
	uint32_t temp;
	tmp_flag = __HAL_UART_GET_FLAG(uart, UART_FLAG_IDLE);	//��ȡIDLE��־λ
	if(tmp_flag != RESET){
		__HAL_UART_CLEAR_IDLEFLAG(uart);			//���IDLE��־λ
		temp = uart->Instance->SR;					//��ȡSR�Ĵ����������SR�Ĵ�����ֵ
		temp = uart->Instance->DR;					//��ȡDR�Ĵ���������
		HAL_UART_DMAStop(uart);						//��ʱ�ر�DMA�������
		/*  F4ϵ��ʹ��NDTR   ����ʹ��CNDTR */
		temp = uart->hdmarx->Instance->NDTR;		//��ȡDMA��δ��������ݸ���
		rxLenth = UART_RX_BUF_SIZE - temp;			//�õ����յ����ݵĳ���
		UART_UserFunction(uart);					//�ж����ĸ����ڽ��յ����ݣ���������Ӧ���û�����
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
