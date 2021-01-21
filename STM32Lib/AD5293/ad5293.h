/*
 * ad5293.h
 *
 *  Created on: Jan 19, 2021
 *      Author: 27321
 */
#include "ATK_sys.h"

#ifndef INC_AD5293_H_
#define INC_AD5293_H_

/*
 * Commands Table
 */
#define CMD_NOP						0x0000

#define CMD_WRITE_TO_RDAC			0x0400
#define CMD_READ_FROM_RDAC			0x0800		//需连接SDO

#define CMD_RESET					0x1000

#define CMD_WRITE_TO_CONTROL_REG	0x1800
#define CMD_READ_FROM_CONTROL_REG	0x1C00		//需连接SDO
#define ALLOW_UPDATE 0x02
#define LOCK_WIPER 0x00
#define NORMAL_MODE 0x04
#define RESISTOR_PERFORMANCE_MODE 0x00
/*
 * Functions Declarations
 */
void AD5293_Reset();
void AD5293_Init();
void AD5293_writeEnable(void);
void AD5293_writeToRDAC(unsigned int AD5293RdacValue);
unsigned int AD5293_readFromRDAC(void);			//未测试

#endif /* INC_AD5293_H_ */
