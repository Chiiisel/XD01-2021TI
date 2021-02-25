/*
 * 		Name:	IOT_ali.c
 *
 *  	Created on: 2021年2月21日
 *      Author: cHisel
 *     	Description:
 *
 *		功	  能：	连接阿里云服务器
 *   	使用方法：	主要使用IOT_Connect()来连接云服务器并保持
 *
 *
 */

#include "IOT_ali.h"

/**
 * 函数功能: 串口打印函数
 * 输入参数: 使用方法同printf
 * 返 回 值: 无
 * 说    明：huartx处修改需要的串口
 */
void PC_printf(const char *format, ...)
{
    va_list args;
    uint32_t length;
    uint8_t txbuf[100] = {0};

    va_start(args, format);
    length = vsnprintf((char *)txbuf, sizeof(txbuf), (char *)format, args);
    va_end(args);
    HAL_UART_Transmit(&PcUart, (uint8_t *)txbuf, length, HAL_MAX_DELAY);
    memset(txbuf, 0, 100);
}


/***********************函数定义********************************/

/**********以下是连接服务器部分，订阅与发布***************************************/

uint16_t buflen=200;
unsigned char buf[200];

char ClientID[128];
uint8_t ClientID_len;

char Username[128];
uint8_t Username_len;

char Password[128];
uint8_t Password_len;

/**
 * 函数功能: 连接云服务器
 * 输入参数: 无
 * 返 回 值: 无
 * 说    明：
 */

uint8_t IOT_Connect(void)
{
	PC_printf("进入连接云服务器函数\r\n");
	uint32_t len;
	char temp[128];

	MQTTPacket_connectData data = MQTTPacket_connectData_initializer;//配置部分可变头部的值

	buflen = sizeof(buf);
	memset(buf,0,buflen);

	memset(ClientID,128,0);                                               //客户端ID的缓冲区全部清零
	sprintf(ClientID,"%s|securemode=3,signmethod=hmacsha1|",DEVICENAME);  //构建客户端ID，并存入缓冲区

	memset(Username,128,0);                                               //用户名的缓冲区全部清零
	sprintf(Username,"%s&%s",DEVICENAME,PRODUCTKEY);                      //构建用户名，并存入缓冲区

	Username_len = strlen(Username);

	memset(temp,128,0);                                                                      //临时缓冲区全部清零
	sprintf(temp,"clientId%sdeviceName%sproductKey%s",DEVICENAME,DEVICENAME,PRODUCTKEY);     //构建加密时的明文
	utils_hmac_sha1(temp,strlen(temp),Password,DEVICESECRE,DEVICESECRE_LEN);                 //以DeviceSecret为秘钥对temp中的明文，进行hmacsha1加密，结果就是密码，并保存到缓冲区中
	Password_len = strlen(Password);                                                         //计算用户名的长度

	PC_printf("ClientId:%s\r\n",ClientID);
	PC_printf("Username:%s\r\n",Username);
	PC_printf("Password:%s\r\n",Password);

	data.MQTTVersion = 3;
	data.clientID.cstring = ClientID;						//客户端标识，用于区分每个客户端xxx为自定义，后面为固定格式
	data.keepAliveInterval = 60;							//保活计时器，定义了服务器收到客户端消息的最大时间间隔,单位是秒
	data.cleansession = 1;									//该标志置1服务器必须丢弃之前保持的客户端的信息，将该连接视为“不存在”
	data.username.cstring = Username;						//用户名 DeviceName&ProductKey
	data.password.cstring = Password;						//密码，工具生成

	len = MQTTSerialize_connect(buf, buflen, &data); 		/*1 构造连接报文*/
	transport_sendPacketBuffer(3,buf, len);				//发送连接请求

	if (MQTTPacket_read(buf, buflen, transport_getdata) == CONNACK)
	{
		unsigned char sessionPresent, connack_rc;

		if (MQTTDeserialize_connack(&sessionPresent, &connack_rc, buf, buflen) != 1 || connack_rc != 0)
		{
			PC_printf("Unable to connect, return code %d\n", connack_rc);
			goto exit;
		}
	}
	else
		goto exit;
	PC_printf("Connect Success!\r\n");

	while(1)
	{
		HAL_Delay(3000);
		len = MQTTSerialize_pingreq(buf, buflen);
		transport_sendPacketBuffer(3, buf, len);
		HAL_Delay(100);
		PC_printf("Ping...\r\n");
		if (MQTTPacket_read(buf, buflen, transport_getdata) == PINGRESP){
			PC_printf("Pong\r\n");
			HAL_Delay(30000);
		}
		else {
			PC_printf("OOPS\r\n");
			goto exit;
		}
	}
	exit:
	transport_close(1);
	PC_printf("EXIT\r\n");
	return 0;
}

/**
 * 函数功能: 发送心跳包
 * 输入参数: 无
 * 返 回 值: 0  保持连接成功
 * 			 1	保持连接失败
 * 说    明：用于保持服务器连接
 */

uint8_t IOT_ping(void)
{
	uint32_t len;
	len = MQTTSerialize_pingreq(buf, buflen);
	transport_sendPacketBuffer(3, buf, len);
	PC_printf("Ping...\r\n");
	if (MQTTPacket_read(buf, buflen, transport_getdata) == PINGRESP){
		PC_printf("Pong\r\n");
		return 0;
	}
	else {
		PC_printf("OOPS\r\n");
		return 1;
	}

}
