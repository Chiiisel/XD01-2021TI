/*
 * 		Name:	IOT_ali.c
 *
 *  	Created on: 2021��2��21��
 *      Author: cHisel
 *     	Description:
 *
 *		��	  �ܣ�	���Ӱ����Ʒ�����
 *   	ʹ�÷�����	��Ҫʹ��IOT_Connect()�������Ʒ�����������
 *
 *
 */

#include "IOT_ali.h"

/**
 * ��������: ���ڴ�ӡ����
 * �������: ʹ�÷���ͬprintf
 * �� �� ֵ: ��
 * ˵    ����huartx���޸���Ҫ�Ĵ���
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


/***********************��������********************************/

/**********���������ӷ��������֣������뷢��***************************************/

uint16_t buflen=200;
unsigned char buf[200];

char ClientID[128];
uint8_t ClientID_len;

char Username[128];
uint8_t Username_len;

char Password[128];
uint8_t Password_len;

/**
 * ��������: �����Ʒ�����
 * �������: ��
 * �� �� ֵ: ��
 * ˵    ����
 */

uint8_t IOT_Connect(void)
{
	PC_printf("���������Ʒ���������\r\n");
	uint32_t len;
	char temp[128];

	MQTTPacket_connectData data = MQTTPacket_connectData_initializer;//���ò��ֿɱ�ͷ����ֵ

	buflen = sizeof(buf);
	memset(buf,0,buflen);

	memset(ClientID,128,0);                                               //�ͻ���ID�Ļ�����ȫ������
	sprintf(ClientID,"%s|securemode=3,signmethod=hmacsha1|",DEVICENAME);  //�����ͻ���ID�������뻺����

	memset(Username,128,0);                                               //�û����Ļ�����ȫ������
	sprintf(Username,"%s&%s",DEVICENAME,PRODUCTKEY);                      //�����û����������뻺����

	Username_len = strlen(Username);

	memset(temp,128,0);                                                                      //��ʱ������ȫ������
	sprintf(temp,"clientId%sdeviceName%sproductKey%s",DEVICENAME,DEVICENAME,PRODUCTKEY);     //��������ʱ������
	utils_hmac_sha1(temp,strlen(temp),Password,DEVICESECRE,DEVICESECRE_LEN);                 //��DeviceSecretΪ��Կ��temp�е����ģ�����hmacsha1���ܣ�����������룬�����浽��������
	Password_len = strlen(Password);                                                         //�����û����ĳ���

	PC_printf("ClientId:%s\r\n",ClientID);
	PC_printf("Username:%s\r\n",Username);
	PC_printf("Password:%s\r\n",Password);

	data.MQTTVersion = 3;
	data.clientID.cstring = ClientID;						//�ͻ��˱�ʶ����������ÿ���ͻ���xxxΪ�Զ��壬����Ϊ�̶���ʽ
	data.keepAliveInterval = 60;							//�����ʱ���������˷������յ��ͻ�����Ϣ�����ʱ����,��λ����
	data.cleansession = 1;									//�ñ�־��1���������붪��֮ǰ���ֵĿͻ��˵���Ϣ������������Ϊ�������ڡ�
	data.username.cstring = Username;						//�û��� DeviceName&ProductKey
	data.password.cstring = Password;						//���룬��������

	len = MQTTSerialize_connect(buf, buflen, &data); 		/*1 �������ӱ���*/
	transport_sendPacketBuffer(3,buf, len);				//������������

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
 * ��������: ����������
 * �������: ��
 * �� �� ֵ: 0  �������ӳɹ�
 * 			 1	��������ʧ��
 * ˵    �������ڱ��ַ���������
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
