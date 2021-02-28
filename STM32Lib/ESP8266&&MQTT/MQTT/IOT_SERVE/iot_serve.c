/*
 * 		Name:	iot_serve.c
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

#include "iot_serve.h"

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
 * �� �� ֵ: 1 �ɹ�
 * 			 0 ʧ��
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
	data.keepAliveInterval = 100;							//�����ʱ���������˷������յ��ͻ�����Ϣ�����ʱ����,��λ����
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


	HAL_Delay(1000);
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
	return 1;
	exit:
	transport_close(1);
	PC_printf("Something wrong and EXIT\r\n");
	return 0;
}

/**
 * ��������: ����������
 * �������: ��
 * �� �� ֵ: 0  �������ӳɹ�
 * 			 1	��������ʧ��
 * ˵    �������ڱ��ַ���������
 */

uint8_t IOT_Ping(void)
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

/**
 * ��������: ����cjson��ʽ�ķ�����Ϣ
 * �������: method����
 * 			 id����
 * 			 STATUS
 *
 * �� �� ֵ: Message ���ɵķ�����Ϣ
 *
 * ˵    ������׼��ʽ����
 * 			{"method":"thing.service.property.set",
 *			"id":"123456",
 *			"params":{"LEDSwitch":0}
 *			}
 */

uint8_t Creat_JsonMessage(char *methodData,char *idData,u_int8_t STATUS,char **Message)
{

	cJSON * cjson_payload = NULL;

	cjson_payload = cJSON_CreateObject();

	cJSON_AddStringToObject(cjson_payload, "method", methodData);
	cJSON_AddStringToObject(cjson_payload, "id", idData);																											//		 "version":"1.0.0"

	cJSON *cjson_child_params = cJSON_CreateObject();
	cJSON_AddNumberToObject(cjson_child_params, "LEDSwitch", STATUS);
	cJSON_AddItemToObject(cjson_payload, "params", cjson_child_params);

	*Message = cJSON_PrintUnformatted(cjson_payload);
//	*Message = cJSON_Print(cjson_payload);

	cJSON_Delete(cjson_payload);
	return 1;
}


uint8_t IOT_Publish(char *pTopic,char *payload)
{
	static uint8_t err_cnt=0;
	int rc = 0;
	int mysock = 0;
	unsigned char buf[200];
	int buflen = sizeof(buf);
	int msgid = 1;
	MQTTString topicString = MQTTString_initializer;
	int payloadlen = strlen(payload);
	int len = 0;


	topicString.cstring = pTopic;		//��������
	len = MQTTSerialize_publish(buf, buflen, 0, 0, 0, 0, topicString, (unsigned char*)payload, payloadlen);
	rc = transport_sendPacketBuffer(mysock, buf, len);
	if (MQTTPacket_read(buf, buflen, transport_getdata) == PUBREC)
	{
		unsigned char dup;
		int qos;
		unsigned char retained;
		unsigned short msgid;
		int payloadlen_in;
		unsigned char* payload_in;
		int rc;
		MQTTString receivedTopic;

		rc = MQTTDeserialize_publish(&dup, &qos, &retained, &msgid, &receivedTopic,
				&payload_in, &payloadlen_in, buf, buflen);
		PC_printf("message arrived %.*s\r\n", payloadlen_in, payload_in);
	}

	PC_printf("publishing reading\r\n");

	return 0;
}
void json_pack(void)
{

	cJSON * cjson_payload = NULL;

	cjson_payload = cJSON_CreateObject();
	cJSON_AddNumberToObject(cjson_payload, "LEDSwitch", 11.11);
	cJSON_AddStringToObject(cjson_payload, "method","data");
	cJSON_AddStringToObject(cjson_payload, "id", "data");																											//		 "version":"1.0.0"
//
//	cJSON *cjson_child_params = cJSON_CreateObject();
//	cJSON_AddNumberToObject(cjson_child_params, "LEDSwitch", 11);
//	cJSON_AddItemToObject(cjson_payload, "params", cjson_child_params);
//
//	cJSON_AddStringToObject(cjson_payload, "version", "1.0.0");

	char *Message = cJSON_PrintUnformatted(cjson_payload);
	PC_printf("%s",Message);			//ͨ�����ڴ�ӡ����
/********************/
/*		�ͷ��ڴ�				*/
/*********************/
		cJSON_Delete(cjson_payload);
		free(Message);
}
