/*
 * adc.h
 *
 *  Created on: Feb 17, 2021
 *      Author: 27321
 */

#ifndef APP_MY_ADC_H_
#define APP_MY_ADC_H_

#define ADC_SAMPLE_POINT	720

extern uint8_t ADC_Channel1[ADC_SAMPLE_POINT/2], ADC_Channel2[ADC_SAMPLE_POINT/2];

void ADC_GetValue(uint32_t *ADC_Value);
void ADC_GetValueToBuff(uint32_t *ADC_Buff);
void ADC_ShowTwoChannel(uint32_t ADC_Buff[ADC_SAMPLE_POINT]);
void ADC_DSOStart(void);

#endif /* APP_MY_ADC_H_ */
