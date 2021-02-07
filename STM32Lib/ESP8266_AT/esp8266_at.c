/*
 * 		Name:esp8266_at.c
 *
 *  	Created on: 2021��2��4��
 *      Author: cHisel
 *     	Description:
 *
 *		��	  �ܣ�	esp8266������ָ�����װ��ESP8266�Ļ���ATָ��
 *   	ʹ�÷�����	��Ҫ���my_uart.cʹ�ã���.h�л��������
 *   				esp8266_at.h��ѡ��esp��Ӧ�Ĵ��ںź�PC��Ӧ�Ĵ��ںţ�
 *
 *   				��my_uart.c�ж�Ӧ���ڵ��û�������д��
 *						   					ESP8266_DefineValue(RxDMABuffx);
 *						   					�����Ҫʹ���������ڷ���ָ��
 *						   					����ESP_UartSendCmd(&PcUart);
 *

 *
 */

#include "esp8266_at.h"


/* Private variables ---------------------------------------------------------*/

ESP_RECEIVETYPE UsartType;
uint8_t UartSendCmd_Flag=0;

/**
 * ��������: ���ڽ���ֵ���ַ�����ֵ����
 * �������: rxLenth, ���ڵĽ��ջ�����RxDMABuffx
 * �� �� ֵ: ��
 * ˵    ����ʹ����my_uart.c���û�������
 */

void ESP8266_DefineValue(uint32_t rxLenth,char * RxDMABuffx)
{
	UsartType.RX_Size = rxLenth;
	UsartType.RX_flag =1;
	strcpy(UsartType.RX_pData,RxDMABuffx);
	UsartType.RX_pData[UsartType.RX_Size]='\0';
}


/**
 * ��������: ʹ������������esp8266����ATָ��
 * �������: ʹ�ô��ڵĴ��ں�
 * �� �� ֵ: ��
 * ˵    ���������Ҫʹ������������esp8266����ָ�ʹ�øú���������8266��Ӧ�Ĵ����û�������
 * 			 ������ʹ�ô��ڵ��û�������д��
 * 										ESP8266_DefineValue(RxDMABuffx);
 * 										UartSendString(&huartx, UsartType.RX_pData);
 * ע	�⣺ʹ�ú�UartSendCmd_Flag	��1
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
 * ��������: ��ESP8266ģ�鷢��ATָ��
 * �������: cmd�������͵�ָ��
 *           reply1��reply2���ڴ�����Ӧ��ΪNULL��ʾ������Ӧ������Ϊ���߼���ϵ
 *           waittime���ȴ���Ӧ��ʱ��
 * �� �� ֵ: 1��ָ��ͳɹ�
 *           0��ָ���ʧ��
 * ˵    ������
 */
bool ESP8266_Cmd ( char * cmd, char * reply1, char * reply2, uint32_t waittime )
{
	UsartType.RX_Size = 0;               //���¿�ʼ�����µ����ݰ�
										//��ӡָ��
	UartSendString(&EspUart, cmd);
	UartSendString(&EspUart, "\r\n");
	if ( ( reply1 == 0 ) && ( reply2 == 0 ) )                      //����Ҫ��������
		return true;

	HAL_Delay( waittime );
	UartSendString(&PcUart,UsartType.RX_pData);	//��ӡesp8266���ص���Ϣ

	if ( ( reply1 != 0 ) && ( reply2 != 0 ) )
		return ( ( bool ) strstr ( UsartType.RX_pData, reply1 ) || ( bool ) strstr ( UsartType.RX_pData, reply2 ) );

	else if ( reply1 != 0 )
		return ( ( bool ) strstr ( UsartType.RX_pData, reply1 ) );
	else
		return ( ( bool ) strstr ( UsartType.RX_pData, reply2 ) );

}


/**
 * ��������: ��ESP8266ģ������
 * �������: ��
 * �� �� ֵ: ��
 * ˵    ������
 */

void ESP8266_Rst(void)
{
	HAL_GPIO_WritePin(ESP_RST_GPIO_Port,ESP_RST_Pin,GPIO_PIN_RESET);
	HAL_Delay(250);
	HAL_GPIO_WritePin(ESP_RST_GPIO_Port,ESP_RST_Pin,GPIO_PIN_SET);
	HAL_Delay(500);
}


/**
 * ��������: ��ESP8266ģ�����AT��������
 * �������: ��
 * �� �� ֵ: 1��ѡ��ɹ�
 *           0��ѡ��ʧ��
 * ˵    ������
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
 * ��������: ѡ��ESP8266ģ��Ĺ���ģʽ
 * �������: enumMode������ģʽ
 * �� �� ֵ: 1��ѡ��ɹ�
 *           0��ѡ��ʧ��
 * ˵    ������
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
 * ��������: ESP8266ģ�������ⲿWiFi
 * �������: pSSID��WiFi�����ַ���
 *           pPassWord��WiFi�����ַ���
 * �� �� ֵ: 1�����ӳɹ�
 *           0������ʧ��
 * ˵    ������
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
 * ��������: ESP8266ģ�鴴��WiFi�ȵ�
 * �������: pSSID��WiFi�����ַ���
 *           pPassWord��WiFi�����ַ���
 *           enunPsdMode��WiFi���ܷ�ʽ�����ַ���
 * �� �� ֵ: 1�������ɹ�
 *           0������ʧ��
 * ˵    ������
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
 * ��������: ESP8266ģ������������
 * �������: enumEnUnvarnishTx�������Ƿ������
 * �� �� ֵ: 1�����óɹ�
 *           0������ʧ��
 * ˵    ������
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
 * ��������: ESP8266ģ�������ⲿ������
 * �������: enumE������Э��
 *           ip��������IP
 *           ComNum���������˿�
 *           id��ģ�����ӷ�������ID
 * �� �� ֵ: 1�����ӳɹ�
 *           0������ʧ��
 * ˵    ����id<5Ϊ��·���ӣ�id=5Ϊ��·����
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
 * ��������: ESP8266ģ�鿪����رշ�����ģʽ
 * �������: enumMode������/�ر�
 *           pPortNum���������˿ں��ַ���
 *           pTimeOver����������ʱʱ���ַ�������λ����
 * �� �� ֵ: 1�������ɹ�
 *           0������ʧ��
 * ˵    ������
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
 * ��������: ��ȡESP8266 ������״̬�����ʺϵ��˿�ʱʹ��
 * �������: ��
 * �� �� ֵ: 2�����ip
 *           3����������
 *           4��ʧȥ����
 *           0����ȡ״̬ʧ��
 * ˵    ������
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
 * ��������: ��ȡESP8266 �Ķ˿ڣ�Id������״̬�����ʺ϶�˿�ʱʹ��
 * �������: ��
 * �� �� ֵ: �˿ڣ�Id��������״̬����5λΪ��Чλ���ֱ��ӦId5~0��ĳλ����1���Id���������ӣ�������0���Idδ��������
 * ˵    ������
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
 * ��������: ��ȡESP8266 �� AP IP
 * �������: pApIp����� AP IP ��������׵�ַ
 *           ucArrayLength����� AP IP ������ĳ���
 * �� �� ֵ: 1����ȡ�ɹ�
 *           0����ȡʧ��
 * ˵    ������
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
 * ��������: ����ESP8266ģ�����͸������
 * �������: ��
 * �� �� ֵ: 1�����óɹ�
 *           0������ʧ��
 * ˵    ������
 */
bool ESP8266_UnvarnishSend ( void )
{

	if ( ! ESP8266_Cmd ( "AT+CIPMODE=1", "OK", 0, 1000 ) )
		return false;

	return  ESP8266_Cmd ( "AT+CIPSEND", "OK", ">", 1000 );

}

/**
 * ��������: ����ESP8266ģ���˳�͸��ģʽ
 * �������: ��
 * �� �� ֵ: ��
 * ˵    ������
 */
void ESP8266_ExitUnvarnishSend ( void )
{
	HAL_Delay(1000);
	UartSendString(&EspUart, "+++");
	HAL_Delay(500);

}

/**
 * ��������: ESP8266ģ�鷢���ַ���
 * �������: enumEnUnvarnishTx�������Ƿ���ʹ����͸��ģʽ��0δ������1����
 *           pStr��Ҫ���͵��ַ���
 *           ucId���ĸ�ID���͵��ַ���
 *           ulStrLength��Ҫ���͵��ַ������ֽ���
 * �� �� ֵ: 1�����ͳɹ�
 *           0������ʧ��
 * ˵    ����͸��ģʽ�¿��Ժ���ulStrLength��ucID
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
 * ��������: ESP8266ģ������ַ���
 * �������: enumEnUnvarnishTx�������Ƿ���ʹ����͸��ģʽ
 * �� �� ֵ: ���յ����ַ����׵�ַ
 * ˵    ������
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
 * ��������: ��ESP8266ģ���ʼ��
 * �������: ��
 * �� �� ֵ: ��
 * ˵    ����Ĭ��ΪSTA/APģʽ��·���ӣ� 	��Ҫ����������������AP��ssid��password �� ��Ҫ�������ӷ�������IP�Ͷ˿ں�
 */
void ESP8266_Init(void)
{
	if(!ESP8266_AT_Test())
		UartSendString(&PcUart, "test error\r\n");
	else
		UartSendString(&PcUart, "test OK\r\n");

	if(ESP8266_Net_Mode_Choose(STA_AP)) //ѡ��STAģʽ
		UartSendString(&PcUart, "STA mode OK\r\n");
	HAL_Delay(100);
	ESP8266_Cmd("AT+RST", "OK", NULL, 1000);
	HAL_Delay(1000);

	if(ESP8266_JoinAP("Don't Use My Net", "D2313...")) //��������AP��ssid��password
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


