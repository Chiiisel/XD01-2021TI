/*
 * my_adc.c
 *
 *  Created on: Feb 17, 2021
 *      Author: 27321
 */



/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "my_adc.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "hmi.h"

/* Private define ------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/


/* Private user code ---------------------------------------------------------*/
/*
 *	使用TIM7溢出中断触发ADC采样
 *	配置ADC为单次转换、扫描模式，使用ADC1的14、15两个通道
 */
//uint32_t ADC_Buff[ADC_SAMPLE_POINT];
uint8_t	ADC_Channel1[ADC_SAMPLE_POINT/2] = {0}, ADC_Channel2[ADC_SAMPLE_POINT/2] = {0};
uint32_t ADC_Value[2];
void ADC_GetValue(uint32_t *ADC_Value){
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)ADC_Value, 2);
	//等待DMA传输完成
	//while(__HAL_DMA_GET_FLAG(&hdma_adc1, DMA_FLAG_TCIF0_4) == RESET);
}

void ADC_GetValueToBuff(uint32_t ADC_Buff[ADC_SAMPLE_POINT]){
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)ADC_Buff, ADC_SAMPLE_POINT);
	//等待DMA传输完成
	//while(__HAL_DMA_GET_FLAG(&hdma_adc1, DMA_FLAG_TCIF0_4) == RESET);
}

void ADC_ShowTwoChannel(uint32_t ADC_Buff[ADC_SAMPLE_POINT]){
	int cnt = 0;
	for(cnt = 0; cnt < ADC_SAMPLE_POINT; cnt++){
		if(cnt%2 == 0){
			ADC_Channel1[cnt/2] = ADC_Buff[cnt]/16;
		}
		else{
			ADC_Channel2[(cnt-1)/2] = ADC_Buff[cnt]/16;
		}
	}
	HMI_DrawCurve(1, 0, ADC_Channel1, ADC_SAMPLE_POINT/2);
	HAL_Delay(40);
	HMI_DrawCurve(1, 1, ADC_Channel2, ADC_SAMPLE_POINT/2);
}


uint32_t ADC_Buff[ADC_SAMPLE_POINT] = {0};
void ADC_DSOStart(void){
	if(__HAL_TIM_GET_FLAG(&htim7, TIM_FLAG_UPDATE)){
		ADC_GetValueToBuff(ADC_Buff);
		HAL_Delay(20);
		ADC_ShowTwoChannel(ADC_Buff);
		__HAL_TIM_CLEAR_FLAG(&htim7, TIM_FLAG_UPDATE);
	}

}
