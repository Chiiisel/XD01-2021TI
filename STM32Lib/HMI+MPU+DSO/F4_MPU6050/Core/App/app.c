/*
 * app.c
 *
 *  Created on: 2021年2月14日
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
	//串口IDLE中断接收开始
	UART2_DMA_IDLE_Start();
	UART3_DMA_IDLE_Start();
	//HMI控件初始化
	HMI_ControlInit();

	//初始化结束后进入主菜单
	HMI_RefreshPage(MAIN_MENU_PAGE);
	sysStatus = MAIN_MENU;
}

/*
 * 	主菜单任务
 */
void MainMenuTask(void){
	while(sysStatus == MAIN_MENU);
}


/*
 * 	MPU6050 任务
 */
float pitch, roll, yaw; 		//欧拉角
short pitch_s, roll_s, yaw_s;	//欧拉角转成short型，方便串口打印
short aacx, aacy, aacz;			//加速度传感器原始数据
short gyrox, gyroy, gyroz;		//陀螺仪原始数据
short temp;						//温度

/*	HMI控件声明	*/
extern HMI_UniversalControl 	p1_txt0;
extern HMI_UnrealFloatControl 	p1_pitch;
extern HMI_UnrealFloatControl	p1_roll;
extern HMI_UnrealFloatControl	p1_yaw;

/*	MPU6050 Task	*/
void MPU6050Task(void){
	/*	DMP初始化 	*/
	uint8_t dmpInitSta = 0xFF;		//DMP初始化状态
	char info[40];
	while(dmpInitSta != 0){
		dmpInitSta = mpu_dmp_init();

		if(dmpInitSta != 0){
			sprintf(info, "MPU6050初始化错误，代码 :%d", dmpInitSta);
			HMI_ModifyControl(p1_txt0, 0xFFFF, info);
		}
		HAL_Delay(200);
	}
	HMI_ModifyControl(p1_txt0, 0xFFFF, "MPU6050初始化OK");
	HAL_Delay(1000);

	/*显示部分*/
	while(sysStatus == MPU6050_MODE){
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0){
			/*显示pitch*/
			pitch_s=pitch*10;
	  		HMI_ModifyUnrealFloat(p1_pitch, pitch_s, 0xFF, 0xFF);
	  		/*显示roll*/
	  		roll_s=roll*10;
	  		HMI_ModifyUnrealFloat(p1_roll, roll_s, 0xFF, 0xFF);
	  		/*显示yaw*/
	  		yaw_s=yaw*10;
	  		HMI_ModifyUnrealFloat(p1_yaw, yaw_s, 0xFF, 0xFF);
		}
	}
}


/*
 * 	DSO数字示波器任务
 */
extern uint8_t ADC_Channel1[ADC_SAMPLE_POINT/2], ADC_Channel2[ADC_SAMPLE_POINT/2];

void DSOTask(void){
	//启动tim3和tim7，tim3负责ADC定时采样，tim7负责定时刷新屏幕曲线
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim7);
	while(sysStatus == DSO_MODE){

	}
}
