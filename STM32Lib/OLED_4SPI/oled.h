#ifndef __OLED_H
#define __OLED_H 


#include "stm32f4xx_hal.h"


#define u16 unsigned short
#define u8 unsigned char
#define u32 unsigned int
//-----------------OLED端口定义----------------


#define OLED_RST_Clr() HAL_GPIO_WritePin(OLED_RST_GPIO_Port,OLED_RST_Pin,GPIO_PIN_RESET)//RST
#define OLED_RST_Set() HAL_GPIO_WritePin(OLED_RST_GPIO_Port,OLED_RST_Pin,GPIO_PIN_SET)

#define OLED_DC_Clr() HAL_GPIO_WritePin(OLED_DC_GPIO_Port,OLED_DC_Pin,GPIO_PIN_RESET)//DC
#define OLED_DC_Set() HAL_GPIO_WritePin(OLED_DC_GPIO_Port,OLED_DC_Pin,GPIO_PIN_SET)
 		     
#define OLED_CS_Clr()  HAL_GPIO_WritePin(OLED_CS_GPIO_Port,OLED_CS_Pin,GPIO_PIN_RESET)//CS
#define OLED_CS_Set()  HAL_GPIO_WritePin(OLED_CS_GPIO_Port,OLED_CS_Pin,GPIO_PIN_SET)

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

#define WHICH_SPI &hspi1	//根据使用的SPI更改


/***********************函数声明********************************/
void OLED_WR_Byte(u8 dat,u8 cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);

void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size);
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1,u8 mode);
void OLED_WR_BP(u8 x,u8 y);
void OLED_ShowPicture(u8 x0,u8 y0,u8 x1,u8 y1,u8 BMP[]);
void OLED_UserInit();

#endif		/*__OLED_H*/
