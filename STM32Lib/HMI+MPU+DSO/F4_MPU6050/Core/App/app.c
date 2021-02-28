/*
 * app.c
 *
 *  Created on: 2021��2��14��
 *      Author: 27321
 */



/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "HMI.h"
#include "mpu6050.h"
#include "my_adc.h"
#include "tim.h"

/* Private define ------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
extern System_Status_TypeDef sysStatus;

/* Private function prototypes -----------------------------------------------*/


/* Private user code ---------------------------------------------------------*/
void SystemStartTask(void){
	//����IDLE�жϽ��տ�ʼ
	UART2_DMA_IDLE_Start();
	UART3_DMA_IDLE_Start();
	//HMI�ؼ���ʼ��
	HMI_ControlInit();

	//��ʼ��������������˵�
	HMI_RefreshPage(MAIN_MENU_PAGE);
	sysStatus = MAIN_MENU;
}

/*
 * 	���˵�����
 */
void MainMenuTask(void){
	while(sysStatus == MAIN_MENU);
}


/*
 * 	MPU6050 ����
 */
float pitch, roll, yaw; 		//ŷ����
short pitch_s, roll_s, yaw_s;	//ŷ����ת��short�ͣ����㴮�ڴ�ӡ
short aacx, aacy, aacz;			//���ٶȴ�����ԭʼ����
short gyrox, gyroy, gyroz;		//������ԭʼ����
short temp;						//�¶�

/*	HMI�ؼ�����	*/
extern HMI_UniversalControl 	p1_txt0;
extern HMI_UnrealFloatControl 	p1_pitch;
extern HMI_UnrealFloatControl	p1_roll;
extern HMI_UnrealFloatControl	p1_yaw;

/*	MPU6050 Task	*/
void MPU6050Task(void){
	/*	DMP��ʼ�� 	*/
	uint8_t dmpInitSta = 0xFF;		//DMP��ʼ��״̬
	char info[40];
	while(dmpInitSta != 0){
		dmpInitSta = mpu_dmp_init();

		if(dmpInitSta != 0){
			sprintf(info, "MPU6050��ʼ�����󣬴��� :%d", dmpInitSta);
			HMI_ModifyControl(p1_txt0, 0xFFFF, info);
		}
		HAL_Delay(200);
	}
	HMI_ModifyControl(p1_txt0, 0xFFFF, "MPU6050��ʼ��OK");
	HAL_Delay(1000);

	/*��ʾ����*/
	while(sysStatus == MPU6050_MODE){
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0){
			/*��ʾpitch*/
			pitch_s=pitch*10;
	  		HMI_ModifyUnrealFloat(p1_pitch, pitch_s, 0xFF, 0xFF);
	  		/*��ʾroll*/
	  		roll_s=roll*10;
	  		HMI_ModifyUnrealFloat(p1_roll, roll_s, 0xFF, 0xFF);
	  		/*��ʾyaw*/
	  		yaw_s=yaw*10;
	  		HMI_ModifyUnrealFloat(p1_yaw, yaw_s, 0xFF, 0xFF);
		}
	}
}


/*
 * 	DSO����ʾ��������
 */
extern uint8_t ADC_Channel1[ADC_SAMPLE_POINT/2], ADC_Channel2[ADC_SAMPLE_POINT/2];

void DSOTask(void){
	//����tim3��tim7��tim3����ADC��ʱ������tim7����ʱˢ����Ļ����
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim7);
	while(sysStatus == DSO_MODE){

	}
}
