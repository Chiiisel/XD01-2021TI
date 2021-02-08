/*
 * 		Name:esp8266_at.c
 *
 *  	Created on: 2021年2月4日
 *      Author: cHisel
 *     	Description:
 *
 *		功	  能：	esp8266驱动的指令集，封装了ESP8266的基本AT指令
 *   	使用方法：	需要配合my_uart.c使用，在.h中互相包含；
 *   				esp8266_at.h中选择esp对应的串口号和PC对应的串口号；
 *
 *   				在my_uart.c中对应串口的用户函数中写：
 *						   					ESP8266_DefineValue(RxDMABuffx);
 *						   					如果需要使用其他串口发送指令
 *						   					加入ESP_UartSendCmd(&PcUart);
 *

 *
 */

#include "esp8266_at.h"


/* Private variables ---------------------------------------------------------*/

ESP_RECEIVETYPE UsartType;
uint8_t UartSendCmd_Flag=0;

/**
 * 函数功能: 串口接收值的字符串赋值操作
 * 输入参数: rxLenth, 串口的接收缓冲区RxDMABuffx
 * 返 回 值: 无
 * 说    明：使用在my_uart.c的用户函数区
 */

void ESP8266_DefineValue(uint32_t rxLenth,char * RxDMABuffx)
{
	UsartType.RX_Size = rxLenth;
	UsartType.RX_flag =1;
	strcpy(UsartType.RX_pData,RxDMABuffx);
	UsartType.RX_pData[UsartType.RX_Size]='\0';
}


/**
 * 函数功能: 使用其他串口向esp8266发送AT指令
 * 输入参数: 使用串口的串口号
 * 返 回 值: 无
 * 说    明：如果需要使用其他串口向esp8266发送指令，使用该函数，放在8266对应的串口用户函数中
 * 			 并且在使用串口的用户函数中写入
 * 										ESP8266_DefineValue(RxDMABuffx);
 * 										UartSendString(&huartx, UsartType.RX_pData);
 * 注	意：使用后将UartSendCmd_Flag	置1
 *
 */
void ESP_UartSendCmd(UART_HandleTypeDef *huart)
{
	if(UartSendCmd_Flag)
		{
			UartSendString(huart, UsartType.RX_pData);
			UartSendCmd_Flag=0;
		}
	else
		UartSendCmd_Flag=0;
}


/**
 * 函数功能: 对ESP8266模块发送AT指令
 * 输入参数: cmd，待发送的指令
 *           reply1，reply2，期待的响应，为NULL表示不需响应，两者为或逻辑关系
 *           waittime，等待响应的时间
 * 返 回 值: 1，指令发送成功
 *           0，指令发送失败
 * 说    明：无
 */
bool ESP8266_Cmd ( char * cmd, char * reply1, char * reply2, uint32_t waittime )
{
	UsartType.RX_Size = 0;               //从新开始接收新的数据包
										//打印指令
	UartSendString(&EspUart, cmd);
	UartSendString(&EspUart, "\r\n");
	if ( ( reply1 == 0 ) && ( reply2 == 0 ) )                      //不需要接收数据
		return true;

	HAL_Delay( waittime );
	UartSendString(&PcUart,UsartType.RX_pData);	//打印esp8266返回的信息

	if ( ( reply1 != 0 ) && ( reply2 != 0 ) )
		return ( ( bool ) strstr ( UsartType.RX_pData, reply1 ) || ( bool ) strstr ( UsartType.RX_pData, reply2 ) );

	else if ( reply1 != 0 )
		return ( ( bool ) strstr ( UsartType.RX_pData, reply1 ) );
	else
		return ( ( bool ) strstr ( UsartType.RX_pData, reply2 ) );

}


/**
 * 函数功能: 对ESP8266模块重启
 * 输入参数: 无
 * 返 回 值: 无
 * 说    明：无
 */

void ESP8266_Rst(void)
{
	HAL_GPIO_WritePin(ESP_RST_GPIO_Port,ESP_RST_Pin,GPIO_PIN_RESET);
	HAL_Delay(250);
	HAL_GPIO_WritePin(ESP_RST_GPIO_Port,ESP_RST_Pin,GPIO_PIN_SET);
	HAL_Delay(500);
}


/**
 * 函数功能: 对ESP8266模块进行AT测试启动
 * 输入参数: 无
 * 返 回 值: 1，选择成功
 *           0，选择失败
 * 说    明：无
 */
bool ESP8266_AT_Test ( void )
{
	char count=0;
	ESP8266_Rst();
	HAL_Delay(1000);
	while(count<10)
	{
		if(ESP8266_Cmd("AT","OK",NULL,1000))return 1;
		HAL_Delay(1000);
		++count;
	}
	return 0;
}

/**
 * 函数功能: 选择ESP8266模块的工作模式
 * 输入参数: enumMode，工作模式
 * 返 回 值: 1，选择成功
 *           0，选择失败
 * 说    明：无
 */
bool ESP8266_Net_Mode_Choose ( ENUM_Net_ModeTypeDef enumMode )
{
	bool result=0;
	char count=0;
	while(count<10)
	{
		switch ( enumMode )
		{
		case STA:
			result=ESP8266_Cmd ( "AT+CWMODE=1", "OK", "no change", 2500 );
			break;
		case AP:
			result=ESP8266_Cmd ( "AT+CWMODE=2", "OK", "no change", 2500 );
			break;
		case STA_AP:
			result=ESP8266_Cmd ( "AT+CWMODE=3", "OK", "no change", 2500 );
			break;
		default:
			result=false;
			break;
		}
		if(result) return result;
		++count;
	}
	return 0;
}

/**
 * 函数功能: ESP8266模块连接外部WiFi
 * 输入参数: pSSID，WiFi名称字符串
 *           pPassWord，WiFi密码字符串
 * 返 回 值: 1，连接成功
 *           0，连接失败
 * 说    明：无
 */
bool ESP8266_JoinAP ( char * pSSID, char * pPassWord )
{
	char cCmd [120];
	char count=0;
	sprintf ( cCmd, "AT+CWJAP=\"%s\",\"%s\"", pSSID, pPassWord );
	while(count<5 )
	{
		if(ESP8266_Cmd(cCmd,"OK",0,2000))return 1;
		++count;
	}
	return 0;
}


/**
 * 函数功能: ESP8266模块创建WiFi热点
 * 输入参数: pSSID，WiFi名称字符串
 *           pPassWord，WiFi密码字符串
 *           enunPsdMode，WiFi加密方式代号字符串
 * 返 回 值: 1，创建成功
 *           0，创建失败
 * 说    明：无
 */
bool ESP8266_BuildAP ( char * pSSID, char * pPassWord, ENUM_AP_PsdMode_TypeDef enunPsdMode )
{
	char cCmd [120];
	char count=0;
	sprintf ( cCmd, "AT+CWSAP=\"%s\",\"%s\",1,%d", pSSID, pPassWord, enunPsdMode );
	while(count<10)
	{
		if(ESP8266_Cmd(cCmd,"OK",0,1000))return 1;
		++count;
	}
	return 0;
}

/**
 * 函数功能: ESP8266模块启动多连接
 * 输入参数: enumEnUnvarnishTx，配置是否多连接
 * 返 回 值: 1，配置成功
 *           0，配置失败
 * 说    明：无
 */
bool ESP8266_Enable_MultipleId ( FunctionalState enumEnUnvarnishTx )
{
	char cStr [20];
	char count=0;
	sprintf ( cStr, "AT+CIPMUX=%d", ( enumEnUnvarnishTx ? 1 : 0 ) );
	while(count<10)
	{
		if(ESP8266_Cmd(cStr,"OK",0,500))return 1;
		++count;
	}
	return 0;
}

/**
 * 函数功能: ESP8266模块连接外部服务器
 * 输入参数: enumE，网络协议
 *           ip，服务器IP
 *           ComNum，服务器端口
 *           id，模块连接服务器的ID
 * 返 回 值: 1，连接成功
 *           0，连接失败
 * 说    明：id<5为多路连接，id=5为单路连接
 */
bool ESP8266_Link_Server ( ENUM_NetPro_TypeDef enumE, char * ip, char * ComNum, ENUM_ID_NO_TypeDef id)
{
	char count=0;
	char cStr [100] = { 0 }, cCmd [120];

	switch (  enumE )
	{
	case enumTCP:
		sprintf ( cStr, "\"%s\",\"%s\",%s", "TCP", ip, ComNum );
		break;

	case enumUDP:
		sprintf ( cStr, "\"%s\",\"%s\",%s", "UDP", ip, ComNum );
		break;

	default:
		break;
	}

	if ( id < 5 )
		sprintf ( cCmd, "AT+CIPSTART=%d,%s", id, cStr);
	else
		sprintf ( cCmd, "AT+CIPSTART=%s", cStr );

	while(count<5)
	{
		if(ESP8266_Cmd ( cCmd, "OK", "ALREAY CONNECT", 4000 ))return 1;
		++count;
	}
	return 0;
}

/**
 * 函数功能: ESP8266模块开启或关闭服务器模式
 * 输入参数: enumMode，开启/关闭
 *           pPortNum，服务器端口号字符串
 *           pTimeOver，服务器超时时间字符串，单位：秒
 * 返 回 值: 1，操作成功
 *           0，操作失败
 * 说    明：无
 */
bool ESP8266_StartOrShutServer ( FunctionalState enumMode, char * pPortNum, char * pTimeOver )
{
	char cCmd1 [120], cCmd2 [120];

	if ( enumMode )
	{
		sprintf ( cCmd1, "AT+CIPSERVER=%d,%s", 1, pPortNum );

		sprintf ( cCmd2, "AT+CIPSTO=%s", pTimeOver );

		return ( ESP8266_Cmd ( cCmd1, "OK", 0, 500 ) &&
				ESP8266_Cmd ( cCmd2, "OK", 0, 500 ) );
	}

	else
	{
		sprintf ( cCmd1, "AT+CIPSERVER=%d,%s", 0, pPortNum );

		return ESP8266_Cmd ( cCmd1, "OK", 0, 500 );
	}
}

/**
 * 函数功能: 获取ESP8266 的连接状态，较适合单端口时使用
 * 输入参数: 无
 * 返 回 值: 2，获得ip
 *           3，建立连接
 *           4，失去连接
 *           0，获取状态失败
 * 说    明：无
 */
uint8_t ESP8266_Get_LinkStatus ( void )
{
	if ( ESP8266_Cmd ( "AT+CIPSTATUS", "OK", 0, 500 ) )
	{
		if ( strstr ( UsartType.RX_pData, "STATUS:2\r\n" ) )
			return 2;

		else if ( strstr ( UsartType.RX_pData, "STATUS:3\r\n" ) )
			return 3;

		else if ( strstr ( UsartType.RX_pData, "STATUS:4\r\n" ) )
			return 4;
	}
	return 0;
}

/**
 * 函数功能: 获取ESP8266 的端口（Id）连接状态，较适合多端口时使用
 * 输入参数: 无
 * 返 回 值: 端口（Id）的连接状态，低5位为有效位，分别对应Id5~0，某位若置1表该Id建立了连接，若被清0表该Id未建立连接
 * 说    明：无
 */
uint8_t ESP8266_Get_IdLinkStatus ( void )
{
	uint8_t ucIdLinkStatus = 0x00;


	if ( ESP8266_Cmd ( "AT+CIPSTATUS", "OK", 0, 500 ) )
	{
		if ( strstr ( UsartType.RX_pData, "+CIPSTATUS:0," ) )
			ucIdLinkStatus |= 0x01;
		else
			ucIdLinkStatus &= ~ 0x01;

		if ( strstr ( UsartType.RX_pData, "+CIPSTATUS:1," ) )
			ucIdLinkStatus |= 0x02;
		else
			ucIdLinkStatus &= ~ 0x02;

		if ( strstr ( UsartType.RX_pData, "+CIPSTATUS:2," ) )
			ucIdLinkStatus |= 0x04;
		else
			ucIdLinkStatus &= ~ 0x04;

		if ( strstr ( UsartType.RX_pData, "+CIPSTATUS:3," ) )
			ucIdLinkStatus |= 0x08;
		else
			ucIdLinkStatus &= ~ 0x08;

		if ( strstr ( UsartType.RX_pData, "+CIPSTATUS:4," ) )
			ucIdLinkStatus |= 0x10;
		else
			ucIdLinkStatus &= ~ 0x10;
	}
	return ucIdLinkStatus;
}

/**
 * 函数功能: 获取ESP8266 的 AP IP
 * 输入参数: pApIp，存放 AP IP 的数组的首地址
 *           ucArrayLength，存放 AP IP 的数组的长度
 * 返 回 值: 1，获取成功
 *           0，获取失败
 * 说    明：无
 */
uint8_t ESP8266_Inquire_ApIp ( char * pApIp, uint8_t ucArrayLength )
{
	char uc;

	char * pCh;


	ESP8266_Cmd ( "AT+CIFSR", "OK", 0, 500 );

	pCh = strstr ( UsartType.RX_pData, "APIP,\"" );

	if ( pCh )
		pCh += 6;

	else
		return 0;

	for ( uc = 0; uc < ucArrayLength; uc ++ )
	{
		pApIp [ uc ] = * ( pCh + uc);

		if ( pApIp [ uc ] == '\"' )
		{
			pApIp [ uc ] = '\0';
			break;
		}
	}
	return 1;
}

/**
 * 函数功能: 配置ESP8266模块进入透传发送
 * 输入参数: 无
 * 返 回 值: 1，配置成功
 *           0，配置失败
 * 说    明：无
 */
bool ESP8266_UnvarnishSend ( void )
{

	if ( ! ESP8266_Cmd ( "AT+CIPMODE=1", "OK", 0, 1000 ) )
		return false;

	return  ESP8266_Cmd ( "AT+CIPSEND", "OK", ">", 1000 );

}

/**
 * 函数功能: 配置ESP8266模块退出透传模式
 * 输入参数: 无
 * 返 回 值: 无
 * 说    明：无
 */
void ESP8266_ExitUnvarnishSend ( void )
{
	HAL_Delay(1000);
	UartSendString(&EspUart, "+++");
	HAL_Delay(500);

}

/**
 * 函数功能: ESP8266模块发送字符串
 * 输入参数: enumEnUnvarnishTx，声明是否已使能了透传模式，0未开启，1开启
 *           pStr，要发送的字符串
 *           ucId，哪个ID发送的字符串
 *           ulStrLength，要发送的字符串的字节数
 * 返 回 值: 1，发送成功
 *           0，发送失败
 * 说    明：透传模式下可以忽视ulStrLength和ucID
 */
bool ESP8266_SendString ( FunctionalState enumEnUnvarnishTx, char * pStr, uint32_t ulStrLength, ENUM_ID_NO_TypeDef ucId )
{
	char cStr [20];
	bool bRet = false;


	if ( enumEnUnvarnishTx )
	{
		UartSendString(&EspUart, pStr);
		bRet = true;

	}

	else
	{
		if ( ucId < 5 )
			sprintf ( cStr, "AT+CIPSEND=%d,%d", ucId, ulStrLength + 2 );

		else
			sprintf ( cStr, "AT+CIPSEND=%d", ulStrLength + 2 );

		ESP8266_Cmd ( cStr, ">", 0, 1000 );

		bRet = ESP8266_Cmd ( pStr, "SEND OK", 0, 1000 );
	}

	return bRet;

}

/**
 * 函数功能: ESP8266模块接收字符串
 * 输入参数: enumEnUnvarnishTx，声明是否已使能了透传模式
 * 返 回 值: 接收到的字符串首地址
 * 说    明：无
 */
char * ESP8266_ReceiveString ( FunctionalState enumEnUnvarnishTx )
{
	char * pRecStr = 0;

	UsartType.RX_Size=0;
	UsartType.RX_flag=0;

	while ( ! UsartType.RX_flag );
	UsartType.RX_pData [ UsartType .RX_Size ] = '\0';

	if ( enumEnUnvarnishTx )
		pRecStr = UsartType.RX_pData;
	else
	{
		if ( strstr ( UsartType.RX_pData, "+IPD" ) )
			pRecStr = UsartType.RX_pData;

	}
	return pRecStr;
}



/**
 * 函数功能: 对ESP8266模块初始化
 * 输入参数: 无
 * 返 回 值: 无
 * 说    明：默认为STA/AP模式单路连接； 	需要配置连接配置连接AP的ssid和password ； 需要配置连接服务器的IP和端口号
 */
void ESP8266_Init(void)
{
	if(!ESP8266_AT_Test())
		UartSendString(&PcUart, "test error\r\n");
	else
		UartSendString(&PcUart, "test OK\r\n");

	if(ESP8266_Net_Mode_Choose(STA_AP)) //选择STA模式
		UartSendString(&PcUart, "STA mode OK\r\n");
	HAL_Delay(100);
	ESP8266_Cmd("AT+RST", "OK", NULL, 1000);
	HAL_Delay(1000);

	if(ESP8266_JoinAP("Don't Use My Net", "D2313...")) //配置连接AP的ssid和password
		UartSendString(&PcUart, "wifi connect OK\r\n");
	else
		UartSendString(&PcUart, "wifi connect error,please check ssid and password\r\n");

	if (ESP8266_Cmd("AT+CIFSR", "OK", NULL, 500)) {
		UartSendString(&PcUart, "Local IP address\r\n");
	}

	HAL_Delay(100);
	ESP8266_Cmd("AT+CIPMUX=0", "OK", NULL, 500);
	if(ESP8266_Link_Server(enumTCP, "192.168.0.211", "10666", 5))
		UartSendString(&PcUart, "TCP connect OK\r\n");
	else
		UartSendString(&PcUart, "TCP connect error,please check out\r\n");

	HAL_Delay(100);
	UartSendString(&PcUart, "ESP8266 Already Init!\r\n");

}


