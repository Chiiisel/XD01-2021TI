/*
 * mpu6050.c
 *
 *  Created on: 2021��2��7��
 *      Author: DW
 *     	Description:
 *
 *		���ܣ�		MPU6050��������ֲ������ԭ��
 *   	ʹ�÷�����		��eMPL�ļ��к�mpu5060.c\.h���Ƶ���Ҫ�Ĺ��̣�����include path�����eMPL�ļ���
 *   				���庯��ʹ�÷�����ʾ������
 *   	ע�����		1.����mpu6050.h��ѡ��ʹ�õ�IIC�ӿ�
 *   				2.�뱣֤MPU6050�ϵ�ʱˮƽ������mpu_dmp_init()�᷵��5()�������Ƿ�������ʧ��
 *   				3.��ʼ��MPU6050ʱ����ֱ��while(mpu_dmp_init())�����mpu_dmp_init()�������᷵��0���Ӷ�����while
 */

#include "mpu6050.h"

/*
 * 	�������ܣ�	MPU6050��ʼ��
 * 	���������	��
 * 	��  ��  ֵ��	0:	����
 * 	˵	����	ֱ�ӵ���mpu_dmp_init()���ɣ����ص��ô˺���
 */
uint8_t MPU_Init(void)
{ 
	uint8_t res;
	MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X80);	//��λMPU6050
    HAL_Delay(100);
	MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X00);	//����MPU6050
	MPU_Set_Gyro_Fsr(3);					//�����Ǵ�����,��2000dps
	MPU_Set_Accel_Fsr(0);					//���ٶȴ�����,��2g
	MPU_Set_Rate(50);						//���ò�����50Hz
	MPU_Write_Byte(MPU_INT_EN_REG,0X00);	//�ر������ж�
	MPU_Write_Byte(MPU_USER_CTRL_REG,0X00);	//I2C��ģʽ�ر�
	MPU_Write_Byte(MPU_FIFO_EN_REG,0X00);	//�ر�FIFO
	MPU_Write_Byte(MPU_INTBP_CFG_REG,0X80);	//INT���ŵ͵�ƽ��Ч
	res=MPU_Read_Byte(MPU_DEVICE_ID_REG); 
	if(res==MPU_ADDR)//����ID��ȷ
	{
		MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X01);	//����CLKSEL,PLL X��Ϊ�ο�
		MPU_Write_Byte(MPU_PWR_MGMT2_REG,0X00);	//���ٶ��������Ƕ�����
		MPU_Set_Rate(50);						//���ò�����Ϊ50Hz
 	}else return 1;
	return 0;
}

/*
 * 	�������ܣ�	���������Ǵ����������̷�Χ
 * 	���������	@arg fsr	0,��250dps;	1,��500dps;	2,��1000dps;	3,��2000dps
 * 	��  ��  ֵ��	0:	����
 * 	˵	����	��
 */
uint8_t MPU_Set_Gyro_Fsr(uint8_t fsr)
{
	return MPU_Write_Byte(MPU_GYRO_CFG_REG,fsr<<3);//���������������̷�Χ
}

/*
 * 	�������ܣ�	���ü��ٶȴ����������̷�Χ
 * 	���������	@arg fsr	0,��2g;	1,��4g;	2,��8g;	3,��16g
 * 	��  ��  ֵ��	0:	����
 * 	˵	����	��
 */
uint8_t MPU_Set_Accel_Fsr(uint8_t fsr)
{
	return MPU_Write_Byte(MPU_ACCEL_CFG_REG,fsr<<3);//���ü��ٶȴ����������̷�Χ
}

/*
 * 	�������ܣ�	����MPU6050�����ֵ�ͨ�˲���
 * 	���������	@arg lpf	���ֵ�ͨ�˲�Ƶ��(Hz)
 * 	��  ��  ֵ��	0:	����
 * 	˵	����	��
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
	return MPU_Write_Byte(MPU_CFG_REG,data);//�������ֵ�ͨ�˲���
}

/*
 * 	�������ܣ�	����MPU6050�Ĳ�����
 * 	���������	@arg rate	4~1000(Hz)
 * 	��  ��  ֵ��	0:	����
 * 	˵	����	��
 */
uint8_t MPU_Set_Rate(uint16_t rate)
{
	uint8_t data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=MPU_Write_Byte(MPU_SAMPLE_RATE_REG,data);	//�������ֵ�ͨ�˲���
 	return MPU_Set_LPF(rate/2);	//�Զ�����LPFΪ�����ʵ�һ��
}

/*
 * 	�������ܣ�	��ȡ�¶ȴ�����
 * 	���������	��
 * 	��  ��  ֵ��	�¶�ֵ
 * 	˵	����	�¶�ֵԭʼ����Ϊfloat�ͣ�Ϊ���㴮�ڴ�ӡ������Ŵ�100����תΪshort
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
 * 	�������ܣ�	��ȡ�����Ǵ�����ԭʼֵ
 * 	���������	@arg	gx,gy,gz	������x,y,z���ԭʼ����(������)
 * 	��  ��  ֵ��	0	����
 * 	˵	����	��Ҫ������gx,gy,gz
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
 * 	�������ܣ�	��ȡ���ٶȴ�����ԭʼֵ
 * 	���������	@arg	ax,ay,az	���ٶ���x,y,z���ԭʼ����(������)
 * 	��  ��  ֵ��	0	����
 * 	˵	����	��Ҫ������ax,ay,az
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
 * 	�������ܣ�	��MPU6050�ļĴ�������д�����ֽ�
 * 	���������	@arg addr	������ַ
 * 			@arg reg 	��Ҫд��ļĴ���
 * 			@arg len	��Ҫд��ĳ���
 * 			@arg *buf	��������ַ
 * 	��  ��  ֵ��	0
 * 	˵	����	��
 */
uint8_t MPU_Write_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{
	HAL_I2C_Mem_Write(&hi2c_mpu, addr, reg, I2C_MEMADD_SIZE_8BIT, buf, len, 0xffff);
	HAL_Delay(1);

	return 0;
} 

/*
 * 	�������ܣ�	��MPU6050�ļĴ���������ȡ����ֽڣ����浽������
 * 	���������	@arg addr	������ַ
 * 			@arg reg 	��Ҫ��ȡ�ļĴ���
 * 			@arg len	��Ҫ��ȡ�ĳ���
 * 			@arg *buf	��������ַ
 * 	��  ��  ֵ��	0
 * 	˵	����	��
 */
uint8_t MPU_Read_Len(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{ 
	HAL_I2C_Mem_Read(&hi2c_mpu, addr, reg, I2C_MEMADD_SIZE_8BIT, buf, len, 0xffff);
	HAL_Delay(1);

	return 0;
}

/*
 * 	�������ܣ�	��MPU6050�ļĴ���д��һ���ֽ�
 * 	���������	@arg reg 	��Ҫд��ļĴ���
 * 			@arg data	��Ҫд�������
 * 	��  ��  ֵ��	0
 * 	˵	����	��
 */
uint8_t MPU_Write_Byte(uint8_t reg,uint8_t data)
{ 
	unsigned char wrtByte = 0;
	HAL_I2C_Mem_Write(&hi2c_mpu, MPU_WRITE, reg, I2C_MEMADD_SIZE_8BIT, &wrtByte, 1, 0xffff);
	HAL_Delay(1);

	return 0;
}

/*
 * 	�������ܣ�	��MPU6050�ļĴ�����ȡһ���ֽ�
 * 	���������	@arg reg ��Ҫ��ȡ�ļĴ���
 * 	��  ��  ֵ��	��ȡ����ֵ
 * 	˵	����	��
 */
uint8_t MPU_Read_Byte(uint8_t reg)
{
	unsigned char recByte = 0;
	HAL_I2C_Mem_Read(&hi2c_mpu, MPU_READ, reg, I2C_MEMADD_SIZE_8BIT, &recByte, 1, 0xffff);
	HAL_Delay(1);

	return recByte;
}


