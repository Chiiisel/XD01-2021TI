/*
 * HMI.h
 *
 *  Created on: 2021��2��11��
 *      Author: 27321
 */

#ifndef APP_HMI_H_
#define APP_HMI_H_

/*
 * 	ͨ�ÿؼ��ṹ�嶨��
 * 	�������ı������֡����ء���ť�Ȼ����ؼ�
 */
typedef struct{
	char 		objname[8];		//�ؼ�����
	uint32_t	val;			//�ؼ�val����
	char		txt[32];		//�ؼ�txt����
}HMI_UniversalControl;

/*
 * 	���⸡�����ṹ�嶨��
 * 	eg.		2021.20
 * 			val	->202120
 * 			vvs0->0
 * 			vvs1->2
 */
typedef struct{
	char 		objname[8];		//�ؼ�����
	int32_t		val;			//�ؼ�val����
	uint8_t		vvs0;			//����λ����0Ϊ�Զ������10λ
	uint8_t		vvs1;			//С��λ����0Ϊ�Զ������8λ
}HMI_UnrealFloatControl;

/*
 * 	HMIҳ�棨page���궨��
 */
#define MAIN_MENU_PAGE	0
#define MPU6050_PAGE	1
#define DSO_PAGE		2

/*
 * 	HMI��������ָ��ṹ�嶨��
 */
typedef struct{
	uint8_t page;				//��ָ������pagex
	uint8_t label;				//��ָ��ı��
	uint32_t cmd;				//ָ������
}HMI_CommandTypeDef;

/*
 * 	��������
 */
uint8_t HMI_ModifyControl(HMI_UniversalControl Control, int32_t val, char txt[32]);
uint8_t HMI_ModifyUnrealFloat(HMI_UnrealFloatControl Control, int32_t val, uint8_t vss0, uint8_t vss1);
void HMI_RefreshPage(uint32_t pageID);
void HMI_ControlInit(void);
uint8_t HMI_DrawCurve(uint8_t CurveID, uint8_t Channel, uint8_t *Data ,uint16_t Quantity);

void HMI_ReceiveCommand(uint8_t Command[6]);
void HMI_SendCommand(char *command);
void HMI_SendEnd(void);

void HMI_UserFunction(HMI_CommandTypeDef revCmd);
void PAGE0_Function(HMI_CommandTypeDef revCmd);
void PAGE1_Function(HMI_CommandTypeDef revCmd);
void PAGE2_Function(HMI_CommandTypeDef revCmd);

#endif /* APP_HMI_H_ */
