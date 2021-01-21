/**
  ******************************************************************************
  * @file           : ad5293.c
  * @brief          : AD5293 Drive
  * @Author			: DW
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "gpio.h"
#include "AD5293.h"
#include "ATK_sys.h"
#include "delay.h"

/* Private define ------------------------------------------------------------*/
#define SYNC_SET()		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET)
#define SYNC_RESET()	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET)
#define RST_SET()		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET)
#define RST_RESET()		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET)
/* Private variables ---------------------------------------------------------*/
unsigned int AD5293RdacValue;
unsigned int AD5293ControlRegisterValue;
unsigned int AD5293Command;
/* Private function prototypes -----------------------------------------------*/


/* Private user code ---------------------------------------------------------*/
/*
 * Use SPI1: SPI Mode 1, 16Bits, SPI PSC 16, NSS Software, MSV first, CRC Disable
 * SYNC-->PB4
 * RESET-->PB12
 * RDY-->PB6
 */
void AD5293_Init(void){
	RST_RESET();
	HAL_Delay(3);
	AD5293_Reset();
	SYNC_RESET();
}

void AD5293_Reset(void){
	RST_RESET();
	HAL_Delay(3);
	RST_SET();
	HAL_Delay(3);
}

void AD5293_writeEnable(void){
	AD5293Command = CMD_WRITE_TO_CONTROL_REG | (ALLOW_UPDATE | NORMAL_MODE);
	SYNC_RESET();
	HAL_SPI_Transmit(&hspi1, &AD5293Command, 1, 1000);
	SYNC_SET();
	HAL_Delay(1);
}

void AD5293_writeToRDAC(unsigned int AD5293RdacValue){
	AD5293Command = CMD_WRITE_TO_RDAC | (AD5293RdacValue & 0x3FF);
	SYNC_RESET();
	HAL_SPI_Transmit(&hspi1, &AD5293Command, 1, 1000);
	SYNC_SET();
	HAL_Delay(1);
}

unsigned int AD5293_readFromRDAC(void){
	AD5293Command = CMD_READ_FROM_RDAC;
	SYNC_RESET();
	HAL_SPI_Transmit(&hspi1, &AD5293Command, 1, 1000);
	HAL_SPI_Receive(&hspi1, &AD5293RdacValue, 1, 1000);
	SYNC_SET();

	return AD5293RdacValue;
}
