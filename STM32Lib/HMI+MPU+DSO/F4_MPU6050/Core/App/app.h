/*
 * app.h
 *
 *  Created on: 2021年2月14日
 *      Author: 27321
 */

#ifndef APP_APP_H_
#define APP_APP_H_

/*
 * 	系统状态机
 */
typedef enum{
	START = 0,			//初始化状态
	MAIN_MENU = 1,		//主菜单
	MPU6050_MODE = 2,	//MPU6050模式
	DSO_MODE = 3,		//DSO模式
	SLEEP_MODE = 4		//睡眠模式
}System_Status_TypeDef;



void SystemStartTask(void);
void MainMenuTask(void);
void MPU6050Task(void);
void DSOTask(void);

#endif /* APP_APP_H_ */
