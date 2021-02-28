/*
 * HMI.h
 *
 *  Created on: 2021年2月11日
 *      Author: 27321
 */

#ifndef APP_HMI_H_
#define APP_HMI_H_

/*
 * 	通用控件结构体定义
 * 	适用于文本、数字、开关、按钮等基础控件
 */
typedef struct{
	char 		objname[8];		//控件名称
	uint32_t	val;			//控件val属性
	char		txt[32];		//控件txt属性
}HMI_UniversalControl;

/*
 * 	虚拟浮点数结构体定义
 * 	eg.		2021.20
 * 			val	->202120
 * 			vvs0->0
 * 			vvs1->2
 */
typedef struct{
	char 		objname[8];		//控件名称
	int32_t		val;			//控件val属性
	uint8_t		vvs0;			//整数位数，0为自动，最大10位
	uint8_t		vvs1;			//小数位数，0为自动，最大8位
}HMI_UnrealFloatControl;

/*
 * 	HMI页面（page）宏定义
 */
#define MAIN_MENU_PAGE	0
#define MPU6050_PAGE	1
#define DSO_PAGE		2

/*
 * 	HMI接收数据指令结构体定义
 */
typedef struct{
	uint8_t page;				//该指令来自pagex
	uint8_t label;				//该指令的标号
	uint32_t cmd;				//指令内容
}HMI_CommandTypeDef;

/*
 * 	函数声明
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
