/*
 * HMI.c
 *	HMI������ͨ�ų������my_uart.c���ڽ���ʹ��
 *  Created on: 2021��2��11��
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
 * 	�Ӵ��ڽ���һ��Byte�������жϴ���͸��״̬
 */
//uint8_t TransmitAvailableFlag = 0;	//����͸����־λ
//void HMI_ReceiveByte(uint8_t *Byte){
//	//����͸����ʼ�����
//	if(*Byte == 0xFE){
//		TransmitAvailableFlag = 1;
//	}
//	//����͸������
//	if(*Byte == 0xFD){
//		TransmitAvailableFlag = 0;
//	}
//}

/*
 * 	����HMI����ָ�������ÿ��ָ�Ϊ6���ֽ�
 * 	��ʽ	: page label cmd
 * 		   1B	1B	  4B
 * 	������ɺ�ִ��HMI_UserFunction
 */
HMI_CommandTypeDef revCmd;
uint8_t TransmitAvailableFlag = 0;	//����͸����־λ
void HMI_ReceiveCommand(uint8_t Command[6]){
	//���ж��ǲ��Ǵ���͸��ָ��
	if(Command[0] == 0xFE){
		TransmitAvailableFlag = 1;
	}
	else if(Command[0] == 0xFD){
		TransmitAvailableFlag = 0;
	}
	//�����Ǵ���͸��ָ��
	else{
		revCmd.page = Command[0];
		revCmd.label = Command[1];
		//HMI���������ǵ�λ��ǰ����λ�ں�����uint32����1023(0x00 00 03 FF),��Ƭ�����յ��� (0xFF 03 00 00)
		revCmd.cmd &= 0;
		revCmd.cmd |= Command[5];
		revCmd.cmd <<= 8;
		revCmd.cmd |= Command[4];
		revCmd.cmd <<= 8;
		revCmd.cmd |= Command[3];
		revCmd.cmd <<= 8;
		revCmd.cmd |= Command[2];
		//����HMI_UserFunction
		HMI_UserFunction(revCmd);
	}
}

/*
 * 	����ָ���page���ԣ����뵽��ͬҳ��Ĵ�����
 * 	����Ϊ�˴���ɶ��ԣ��ٸ���ָ���page��һ�η�װ����ͬpage��ָ���д��һ������
 * 	���ָ���ٵĻ�Ҳ����ֱ�������������д
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
 * 	�ؼ���ʼ��
 *	ע��ʹ��ʱҪ���ڶ�Ӧ���ļ���extern
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
 * 	ˢ��HMI��ʾҳ��
 * 	���������	pageID��	ҳ��ID��ҳ������
 * 	��  ��  ֵ��	��
 */
void HMI_RefreshPage(uint32_t pageID){
	char cmd[10];
	sprintf(cmd, "page %d", pageID);
	HMI_SendCommand(cmd);
}

/*
 * 	�޸�ͨ�ÿؼ���val��txt����
 * 	���������	Control����Ҫ�޸ĵĿؼ���
 * 			val���ؼ���val����ֵ��0xFFFF��ʾ���޸�
 * 			txt���ؼ���txt�������ݣ�NULL��ʾ���޸�
 * 	��  ��  ֵ��	1��������0������
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
 * 	�޸����⸡�����ؼ�����
 * 	���������	Control����Ҫ�޸ĵĿؼ���
 * 			val���ؼ���val����ֵ��0xFFFF��ʾ���޸�
 * 			vss0���ؼ���vss0�������ݣ�0XFF��ʾ���޸�
 * 			vss1���ؼ���vss1�������ݣ�0XFF��ʾ���޸�
 * 	��  ��  ֵ��	1��������0������
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
 * 	����͸��
 * 	���ݴ�С0-255�������1024Byte
 */
uint8_t HMI_DrawCurve(uint8_t CurveID, uint8_t Channel, uint8_t *Data, uint16_t Quantity){
	char cmd[20] = {0};
	sprintf(cmd, "addt %d,%d,%d", CurveID, Channel, Quantity);
	HMI_SendCommand(cmd);
	//�ȴ�����͸����ʼ�����
	while(TransmitAvailableFlag == 0);
	HAL_UART_Transmit(&huart_hmi, Data, Quantity, 0xFFFF);
}

/*
 * 	��HMI����ָ��
 * 	���������
 */
void HMI_SendCommand(char *command){
	UartSendString(&huart_hmi, command);
	UartSendString(&huart_hmi,"\xff\xff\xff");
}

void HMI_SendEnd(void){
	UartSendString(&huart_hmi,"\xff\xff\xff");
}
