/*
 * HMI.c
 *	HMI串口屏通信程序，配合my_uart.c串口接收使用
 *  Created on: 2021年2月11日
 *      Author: 27321
 */



/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private define ------------------------------------------------------------*/
#define huart_hmi	huart2

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/


/* Private user code ---------------------------------------------------------*/
/*
 * 	从串口接收一个Byte，用于判断串口透传状态
 */
//uint8_t TransmitAvailableFlag = 0;	//串口透传标志位
//void HMI_ReceiveByte(uint8_t *Byte){
//	//串口透传初始化完成
//	if(*Byte == 0xFE){
//		TransmitAvailableFlag = 1;
//	}
//	//串口透传结束
//	if(*Byte == 0xFD){
//		TransmitAvailableFlag = 0;
//	}
//}

/*
 * 	接收HMI发送指令并解析，每个指令都为6个字节
 * 	格式	: page label cmd
 * 		   1B	1B	  4B
 * 	解析完成后执行HMI_UserFunction
 */
HMI_CommandTypeDef revCmd;
uint8_t TransmitAvailableFlag = 0;	//串口透传标志位
void HMI_ReceiveCommand(uint8_t Command[6]){
	//先判断是不是串口透传指令
	if(Command[0] == 0xFE){
		TransmitAvailableFlag = 1;
	}
	else if(Command[0] == 0xFD){
		TransmitAvailableFlag = 0;
	}
	//若不是串口透传指令
	else{
		revCmd.page = Command[0];
		revCmd.label = Command[1];
		//HMI发的数据是低位在前，高位在后，如以uint32发送1023(0x00 00 03 FF),单片机接收的是 (0xFF 03 00 00)
		revCmd.cmd &= 0;
		revCmd.cmd |= Command[5];
		revCmd.cmd <<= 8;
		revCmd.cmd |= Command[4];
		revCmd.cmd <<= 8;
		revCmd.cmd |= Command[3];
		revCmd.cmd <<= 8;
		revCmd.cmd |= Command[2];
		//进入HMI_UserFunction
		HMI_UserFunction(revCmd);
	}
}

/*
 * 	解析指令的page属性，进入到不同页面的处理函数
 * 	这里为了代码可读性，再根据指令的page做一次封装，不同page的指令单独写成一个函数
 * 	如果指令少的话也可以直接在这个函数里写
 */
void HMI_UserFunction(HMI_CommandTypeDef revCmd){
	switch(revCmd.page){
	case 0:	PAGE0_Function(revCmd);		break;
	case 1: PAGE1_Function(revCmd);		break;
	case 2: PAGE2_Function(revCmd);		break;
	default:	break;
	}
}

/*
 * 	PAGEx_Function
 */
#define b0	1
#define b1 	2
#define sw0	3
#define h0	4
extern System_Status_TypeDef sysStatus;
void PAGE0_Function(HMI_CommandTypeDef revCmd){
	switch(revCmd.label){
	case b0:	sysStatus = MPU6050_MODE;		break;
	case b1:	sysStatus = DSO_MODE;			break;
	default:	break;
	}
}

void PAGE1_Function(HMI_CommandTypeDef revCmd){
	switch(revCmd.label){
	case b0:	sysStatus = MAIN_MENU;			break;
	default:	break;
	}
}

void PAGE2_Function(HMI_CommandTypeDef revCmd){
	switch(revCmd.label){
	case b0:	sysStatus = MAIN_MENU;			break;
	default:	break;
	}
}

/*
 * 	控件初始化
 *	注意使用时要先在对应的文件里extern
 */
HMI_UniversalControl 	p1_txt0;
HMI_UnrealFloatControl 	p1_pitch;
HMI_UnrealFloatControl	p1_roll;
HMI_UnrealFloatControl	p1_yaw;

void HMI_ControlInit(void){
	/*p1_txt0*/
	strcpy(p1_txt0.objname, "g0");
	/*pitch*/
	strcpy(p1_pitch.objname, "x0");
	p1_pitch.val = 0;
	p1_pitch.vvs0 = 0;
	p1_pitch.vvs1 = 1;
	/*roll*/
	strcpy(p1_roll.objname, "x1");
	p1_roll.val = 0;
	p1_roll.vvs0 = 0;
	p1_roll.vvs1 = 1;
	/*yaw*/
	strcpy(p1_yaw.objname, "x2");
	p1_yaw.val = 0;
	p1_yaw.vvs0 = 0;
	p1_yaw.vvs1 = 1;
}

/*
 * 	刷新HMI显示页面
 * 	输入参数：	pageID：	页面ID或页面名称
 * 	返  回  值：	无
 */
void HMI_RefreshPage(uint32_t pageID){
	char cmd[10];
	sprintf(cmd, "page %d", pageID);
	HMI_SendCommand(cmd);
}

/*
 * 	修改通用控件的val、txt属性
 * 	输入参数：	Control：需要修改的控件名
 * 			val：控件的val属性值，0xFFFF表示不修改
 * 			txt：控件的txt属性内容，NULL表示不修改
 * 	返  回  值：	1：正常；0：错误
 */
uint8_t HMI_ModifyControl(HMI_UniversalControl Control, int32_t val, char txt[32]){
	char cmd[50];
	if(val != 0xFFFF){
		sprintf(cmd, "%s.val=%d", Control.objname, val);
		HMI_SendCommand(cmd);
	}
	if(strcmp(txt, "NULL")){
		sprintf(cmd, "%s.txt=\"%s\"", Control.objname, txt);
		HMI_SendCommand(cmd);
	}
	return 1;
}

/*
 * 	修改虚拟浮点数控件属性
 * 	输入参数：	Control：需要修改的控件名
 * 			val：控件的val属性值，0xFFFF表示不修改
 * 			vss0：控件的vss0属性内容，0XFF表示不修改
 * 			vss1：控件的vss1属性内容，0XFF表示不修改
 * 	返  回  值：	1：正常；0：错误
 */
uint8_t HMI_ModifyUnrealFloat(HMI_UnrealFloatControl Control, int32_t val, uint8_t vss0, uint8_t vss1){
	char cmd[50];
	if(val != 0xFFFF){
		sprintf(cmd, "%s.val=%d", Control.objname, val);
		HMI_SendCommand(cmd);
	}
	if(vss0 != 0xFF){
		sprintf(cmd, "%s.vss0=%d", Control.objname, vss0);
		HMI_SendCommand(cmd);
	}
	if(vss1 != 0xFF){
		sprintf(cmd, "%s.vss1=%d", Control.objname, vss1);
		HMI_SendCommand(cmd);
	}
	return 1;
}

/*
 * 	曲线透传
 * 	数据大小0-255，最大传输1024Byte
 */
uint8_t HMI_DrawCurve(uint8_t CurveID, uint8_t Channel, uint8_t *Data, uint16_t Quantity){
	char cmd[20] = {0};
	sprintf(cmd, "addt %d,%d,%d", CurveID, Channel, Quantity);
	HMI_SendCommand(cmd);
	//等待串口透传初始化完成
	while(TransmitAvailableFlag == 0);
	HAL_UART_Transmit(&huart_hmi, Data, Quantity, 0xFFFF);
}

/*
 * 	向HMI发送指令
 * 	输入参数：
 */
void HMI_SendCommand(char *command){
	UartSendString(&huart_hmi, command);
	UartSendString(&huart_hmi,"\xff\xff\xff");
}

void HMI_SendEnd(void){
	UartSendString(&huart_hmi,"\xff\xff\xff");
}
