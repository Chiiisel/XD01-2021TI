/*
 * app.h
 *
 *  Created on: 2021��2��14��
 *      Author: 27321
 */

#ifndef APP_APP_H_
#define APP_APP_H_

/*
 * 	ϵͳ״̬��
 */
typedef enum{
	START = 0,			//��ʼ��״̬
	MAIN_MENU = 1,		//���˵�
	MPU6050_MODE = 2,	//MPU6050ģʽ
	DSO_MODE = 3,		//DSOģʽ
	SLEEP_MODE = 4		//˯��ģʽ
}System_Status_TypeDef;



void SystemStartTask(void);
void MainMenuTask(void);
void MPU6050Task(void);
void DSOTask(void);

#endif /* APP_APP_H_ */
