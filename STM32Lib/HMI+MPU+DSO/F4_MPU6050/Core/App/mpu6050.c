/*
 * mpu6050.c
 *
 *  Created on: 2021年2月7日
 *      Author: DW
 *     	Description:
 *
 *		功能：		MPU6050驱动，移植自正点原子
 *   	使用方法：		将eMPL文件夹和mpu5060.c\.h复制到需要的工程，并在include path中添加eMPL文件夹
 *   				具体函数使用方法见示例程序
 *   	注意事项：		1.可在mpu6050.h中选择使用的IIC接口
 *   				2.请保证MPU6050上电时水平，否则mpu_dmp_init()会返回5()，陀螺仪方向设置失败
 *   				3.初始化MPU6050时建议直接while(mpu_dmp_init())，如果mpu_dmp_init()正常，会返回0，从而跳出while
 */

#include "mpu6050.h"

/*
 * 	函数功能：	MPU6050初始化
 * 	输入参数：	无
 * 	返  回  值：	0:	正常
 * 	说	明：	直接调用mpu_dmp_init()即可，不必调用此函数
 */
uint8_t MPU_Init(void)
{ 
	uint8_t res;
	MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X80);	//复位MPU6050
    HAL_Delay(100);
	MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X00);	//唤醒MPU6050
	MPU_Set_Gyro_Fsr(3);					//陀螺仪传感器,±2000dps
	MPU_Set_Accel_Fsr(0);					//加速度传感器,±2g
	MPU_Set_Rate(50);						//设置采样率50Hz
	MPU_Write_Byte(MPU_INT_EN_REG,0X00);	//关闭所有中断
	MPU_Write_Byte(MPU_USER_CTRL_REG,0X00);	//I2C主模式关闭
	MPU_Write_Byte(MPU_FIFO_EN_REG,0X00);	//关闭FIFO
	MPU_Write_Byte(MPU_INTBP_CFG_REG,0X80);	//INT引脚低电平有效
	res=MPU_Read_Byte(MPU_DEVICE_ID_REG); 
	if(res==MPU_ADDR)//器件ID正确
	{
		MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X01);	//设置CLKSEL,PLL X轴为参考
		MPU_Write_Byte(MPU_PWR_MGMT2_REG,0X00);	//加速度与陀螺仪都工作
		MPU_Set_Rate(50);						//设置采样率为50Hz
 	}else return 1;
	return 0;
}

/*
 * 	函数功能：	设置陀螺仪传感器满量程范围
 * 	输入参数：	@arg fsr	0,±250dps;	1,±500dps;	2,±1000dps;	3,±2000dps
 * 	返  回  值：	0:	正常
 * 	说	明：	无
 */
uint8_t MPU_Set_Gyro_Fsr(uint8_t fsr)
{
	return MPU_Write_Byte(MPU_GYRO_CFG_REG,fsr<<3);//设置陀螺仪满量程范围
}

/*
 * 	函数功能：	设置加速度传感器满量程范围
 * 	输入参数：	@arg fsr	0,±2g;	1,±4g;	2,±8g;	3,±16g
 * 	返  回  值：	0:	正常
 * 	说	明：	无
 */
uint8_t MPU_Set_Accel_Fsr(uint8_t fsr)
{
	return MPU_Write_Byte(MPU_ACCEL_CFG_REG,fsr<<3);//设置加速度传感器满量程范围
}

/*
 * 	函数功能：	设置MPU6050的数字低通滤波器
 * 	输入参数：	@arg lpf	数字低通滤波频率(Hz)
 * 	返  回  值：	0:	正常
 * 	说	明：	无
 */
uint8_t MPU_Set_LPF(uint16_t lpf)
{
	uint8_t data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	return MPU_Write_Byte(MPU_CFG_REG,data);//设置数字低通滤波器
}

/*
 * 	函数功能：	设置MPU6050的采样率
 * 	输入参数：	@arg rate	4~1000(Hz)
 * 	返  回  值：	0:	正常
 * 	说	明：	无
 */
uint8_t MPU_Set_Rate(uint16_t rate)
{
	uint8_t data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=MPU_Write_Byte(MPU_SAMPLE_RATE_REG,data);	//设置数字低通滤波器
 	return MPU_Set_LPF(rate/2);	//自动设置LPF为采样率的一半
}

/*
 * 	函数功能：	获取温度传感器
 * 	输入参数：	无
 * 	返  回  值：	温度值
 * 	说	明：	温度值原始数据为float型，为方便串口打印，这里放大100倍并转为short
 */
short MPU_Get_Temperature(void)
{
    uint8_t buf[2];
    short raw;
	float temp;
	MPU_Read_Len(MPU_READ,MPU_TEMP_OUTH_REG,2,buf);
    raw=((uint16_t)buf[0]<<8)|buf[1];
    temp=36.53+((double)raw)/340;  
    return temp*100;;
}

/*
 * 	函数功能：	获取陀螺仪传感器原始值
 * 	输入参数：	@arg	gx,gy,gz	陀螺仪x,y,z轴的原始读数(带符号)
 * 	返  回  值：	0	正常
 * 	说	明：	需要先声明gx,gy,gz
 */
uint8_t MPU_Get_Gyroscope(short *gx,short *gy,short *gz)
{
    uint8_t buf[6],res;
	res=MPU_Read_Len(MPU_READ,MPU_GYRO_XOUTH_REG,6,buf);
	if(res==0)
	{
		*gx=((uint16_t)buf[0]<<8)|buf[1];
		*gy=((uint16_t)buf[2]<<8)|buf[3];
		*gz=((uint16_t)buf[4]<<8)|buf[5];
	} 	
    return res;;
}

/*
 * 	函数功能：	获取加速度传感器原始值
 * 	输入参数：	@arg	ax,ay,az	加速度仪x,y,z轴的原始读数(带符号)
 * 	返  回  值：	0	正常
 * 	说	明：	需要先声明ax,ay,az
 */
uint8_t MPU_Get_Accelerometer(short *ax,short *ay,short *az)
{
    uint8_t buf[6],res;
	res=MPU_Read_Len(MPU_READ,MPU_ACCEL_XOUTH_REG,6,buf);
	if(res==0)
	{
		*ax=((uint16_t)buf[0]<<8)|buf[1];
		*ay=((uint16_t)buf[2]<<8)|buf[3];
		*az=((uint16_t)buf[4]<<8)|buf[5];
	} 	
    return res;
}
/*
 * 	函数功能：	从MPU6050的寄存器连续写入多个字节
 * 	输入参数：	@arg addr	器件地址
 * 			@arg reg 	需要写入的寄存器
 * 			@arg len	需要写入的长度
 * 			@arg *buf	缓冲区地址
 * 	返  回  值：	0
 * 	说	明：	无
 */
uint8_t MPU_Write_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{
	HAL_I2C_Mem_Write(&hi2c_mpu, addr, reg, I2C_MEMADD_SIZE_8BIT, buf, len, 0xffff);
	HAL_Delay(1);

	return 0;
} 

/*
 * 	函数功能：	从MPU6050的寄存器连续读取多个字节，并存到缓冲区
 * 	输入参数：	@arg addr	器件地址
 * 			@arg reg 	需要读取的寄存器
 * 			@arg len	需要读取的长度
 * 			@arg *buf	缓冲区地址
 * 	返  回  值：	0
 * 	说	明：	无
 */
uint8_t MPU_Read_Len(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{ 
	HAL_I2C_Mem_Read(&hi2c_mpu, addr, reg, I2C_MEMADD_SIZE_8BIT, buf, len, 0xffff);
	HAL_Delay(1);

	return 0;
}

/*
 * 	函数功能：	向MPU6050的寄存器写入一个字节
 * 	输入参数：	@arg reg 	需要写入的寄存器
 * 			@arg data	需要写入的数据
 * 	返  回  值：	0
 * 	说	明：	无
 */
uint8_t MPU_Write_Byte(uint8_t reg,uint8_t data)
{ 
	unsigned char wrtByte = 0;
	HAL_I2C_Mem_Write(&hi2c_mpu, MPU_WRITE, reg, I2C_MEMADD_SIZE_8BIT, &wrtByte, 1, 0xffff);
	HAL_Delay(1);

	return 0;
}

/*
 * 	函数功能：	从MPU6050的寄存器读取一个字节
 * 	输入参数：	@arg reg 需要读取的寄存器
 * 	返  回  值：	读取到的值
 * 	说	明：	无
 */
uint8_t MPU_Read_Byte(uint8_t reg)
{
	unsigned char recByte = 0;
	HAL_I2C_Mem_Read(&hi2c_mpu, MPU_READ, reg, I2C_MEMADD_SIZE_8BIT, &recByte, 1, 0xffff);
	HAL_Delay(1);

	return recByte;
}


