/*
 * 		Name:	iot_serve.c
 *
 *  	Created on: 2021��2��21��
 *      Author: cHisel
 *     	Description:
 *
 *		��	  �ܣ�	���Ӱ����Ʒ�����
 *   	ʹ�÷�����	��ʼ��ʱʹ��IOT_Connect()�������Ʒ�����������
 *					һ��ʼ��Ҫ��������IOT_Subscribe()
 *					��while1�м���IOT_TaskHandle();
 *
 */

#include "iot_serve.h"


IotTaskTypeDef IotTaskflag={0,0,0,0};
char PublishMessage[100]={0};
char SubscirbMessage[200]={0};
uint8_t LED_Status = 0;
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
uint8_t IotConnect_Flag=0;

char ClientID[128];
uint8_t ClientID_len;

char Username[128];
uint8_t Username_len;

char Password[128];
uint8_t Password_len;

uint16_t buflen=200;
unsigned char buf[200];
//unsigned char buf[200];
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
	data.keepAliveInterval = 70;							//�����ʱ���������˷������յ��ͻ�����Ϣ�����ʱ����,��λ����
	data.cleansession = 1;									//�ñ�־��1���������붪��֮ǰ���ֵĿͻ��˵���Ϣ������������Ϊ�������ڡ�
	data.username.cstring = Username;						//�û��� DeviceName&ProductKey
	data.password.cstring = Password;						//���룬��������

	len = MQTTSerialize_connect(buf, buflen, &data); 		/*1 �������ӱ���*/
	transport_sendPacketBuffer(3,buf, len);				//������������

	/****************/
	//	if (MQTTPacket_read(buf, buflen, transport_getdata) == CONNACK)
	//	{
	//		unsigned char sessionPresent, connack_rc;
	//
	//		if (MQTTDeserialize_connack(&sessionPresent, &connack_rc, buf, buflen) != 1 || connack_rc != 0)
	//		{
	//			PC_printf("Unable to connect, return code %d\r\n", connack_rc);
	//			goto exit;
	//		}
	//	}
	//	else{
	//		PC_printf("Connect ERROR!\r\n");
	//		goto exit;
	//	}
	//
	//	PC_printf("Connect Success!\r\n");
	//	IotConnect_Flag=1;
	//	return 1;

	/*****************/
	if (MQTTPacket_read(buf, buflen, transport_getdata)== CONNACK)	//�յ�Ӧ������Ϊ���ӳɹ�
	{
		PC_printf("Successfully Connect !\r\n");
		IotConnect_Flag=1;
		return 1;
	}
	else{
		PC_printf("Connect ERROR!\r\n");
		goto exit;
	}

	exit:
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
	PC_printf("Ping...\r\n");
	buflen = sizeof(buf);
	uint32_t len;
	len = MQTTSerialize_pingreq(buf, buflen);
	transport_sendPacketBuffer(NULL, buf, len);

	if (MQTTPacket_read(buf, buflen, transport_getdata) == PINGRESP ){
		PC_printf("Pong\r\n");
		return 0;
	}
	else {
		PC_printf("OOPS\r\n");
		IotConnect_Flag=0;
		return 1;
	}
}


/****************************************
 * ��������: ����cjson��ʽ�ķ�����Ϣ
 * �������: method����
 * 			 id����
 * 			 STATUS ��Ҫ�ϴ�������
 *
 *			 Message �������ַ���
 * �� �� ֵ: 1
 *
 * ˵    ������׼��ʽ����
 * 			{"method":"thing.service.property.set",
 *			"id":"123456",
 *			"params":{"LEDSwitch":0}
 *			}
 */
uint8_t Creat_JsonMessage(char *methodData,char *idData,u_int8_t STATUS,char *Message)
{
	sprintf(Message,"{\"method\":\"%s\","
			"\"id\":\"%s\","
			"\"params\":{\"LEDSwitch\": %d}"
			"}",methodData,idData,STATUS);
	PC_printf("PublishMessage:%s\r\n",Message);
	/************�����Ǳ�׼��ʹ��cjson��Դ��������ɵķ���������������ֲ���ʼ�ղ��ܳɹ�����һ��Сbug********/
	//		cJSON * cjson_payload = NULL;
	//
	//		cjson_payload = cJSON_CreateObject();
	//
	//		cJSON_AddStringToObject(cjson_payload, "method", methodData);
	//		cJSON_AddStringToObject(cjson_payload, "id", idData);																											//		 "version":"1.0.0"
	//
	//		cJSON *cjson_child_params = cJSON_CreateObject();
	//		cJSON_AddNumberToObject(cjson_child_params, "LEDSwitch", STATUS);
	//		cJSON_AddItemToObject(cjson_payload, "params", cjson_child_params);
	//
	//		*Message = cJSON_PrintUnformatted(cjson_payload);
	//
	//		cJSON_Delete(cjson_payload);
	/*******************************************************************************************************/
	return 1;
}


/***********************************
 * ��������: ����cjson��ʽ�Ľ�����Ϣ
 * �������: StatusName  Ŀ��״̬������
 * 			 Message	��Ҫ������ַ���

 * �� �� ֵ: Message_data �õ�Ŀ��״̬����ֵ
 *
 * ˵    ����
 *
 */
cjsonMessageTypeDef cjsonMessage;
uint8_t Parse_JsonMessage(char *StatusName,char *Message)
{
	uint8_t Message_data;
	cJSON   *root, *params;
	root = cJSON_Parse(Message);
	if(root){
		cjsonMessage.method = cJSON_GetObjectItem(root, "method")->valuestring;//�ַ�����
		cjsonMessage.id = cJSON_GetObjectItem(root, "id")->valuestring;//�ַ�����

		params = cJSON_GetObjectItem(root, "params");
		if(params){
			cjsonMessage.Status = cJSON_GetObjectItem(params, StatusName)->valueint;//�ַ�����
		}
	}
	Message_data=cjsonMessage.Status;
	cJSON_Delete(root);

	//	PC_printf("method:%s\r\n",cjsonMessage.method);
	//	PC_printf("id:%s\r\n",cjsonMessage.id);
	//	PC_printf("%s:%d\r\n",StatusName,cjsonMessage.Status);
	return Message_data;
}

/*********************************************************
 * ��������: ������Ϣ
 * �������: pTopic��������
 * 			 payload��Ϣ����
 *
 * �� �� ֵ: 1�ɹ�
 * 			 0ʧ��
 *
 * ˵    ����ע�ⷢ����Ϣ�ĸ�ʽ��ʹ��Creat_JsonMessage();
 *
 */
uint8_t IOT_Publish(char *pTopic,char *payload)
{
	buflen = sizeof(buf);
	int rc = 0;
	int mysock = 0;
	int payloadlen = strlen(payload);
	int len = 0;
	MQTTString topicString = MQTTString_initializer;
	topicString.cstring = pTopic;
	len = MQTTSerialize_publish(buf, buflen, 0, 0, 0, 0, topicString, (unsigned char*)payload, payloadlen);//�ڶ���0������qos�ȼ��������ƽ�֧��qos0��1
	rc = transport_sendPacketBuffer(mysock, (unsigned char*)buf, len);
	PC_printf("Successfully Published\r\n");
	return 1;
}


/*********************************************************
 * ��������: ��������
 * �������: pTopicҪ���ĵ�����
 *
 * �� �� ֵ: 1�ɹ�
 * 			 0ʧ��
 *
 * ˵    ��������ֻ���ڶ������⣬�������Ӻ���һ�μ���
 *
 */
uint8_t IOT_Subscribe(char *pTopic)
{
	if(IotConnect_Flag){
		buflen = sizeof(buf);
		int mysock = 0;
		int msgid = 1;
		int req_qos = 0;
		int rc = 0;
		int len = 0;
		MQTTString topicString = MQTTString_initializer;
		topicString.cstring = pTopic;

		len = MQTTSerialize_subscribe(buf, buflen, 0, msgid, 1, &topicString, &req_qos);
		rc = transport_sendPacketBuffer(mysock, buf, len);

		//�ȴ���������
		//SUBACK
		if (MQTTPacket_read(buf, buflen, transport_getdata) == SUBACK) 	/* �ȴ� suback */
		{
			PC_printf("Successfully Subscribed !\r\n");
			return 1;
		}
		else
			goto exit;


		exit:
		PC_printf("Subscribe Fail!\r\n");
		return 0;
	}
	return 0;
}
/*********************************************************
 * ��������: �����������˷�������Ϣ
 * �������: Message ������Ϣ���ַ�����
 *
 * �� �� ֵ:
 *
 * ˵    ����
 *
 */
uint8_t IOT_HandleGetData(char *Message){
	buflen = sizeof(buf);
	if (MQTTPacket_read(buf, buflen, transport_getdata) == PUBLISH)
	{
		memcpy(Message,&UsartType.RX_pData[56],buflen-56);//��������
		return 1;
	}
	else
		return 0;
	return 0;
}



/*********************************************************
 * ��������: IOT������
 * �������: ��
 *
 * �� �� ֵ: ��
 *
 * ˵    ��������while1��ѭ��ִ��
 * 			���ڴ������IOT�¼�
 * 			����Ҫ�ĵط���IotTaskflag.xxxx��1
 *
 */
void IOT_TaskHandle(void){
	if(IotConnect_Flag){

		if(IotTaskflag.IotHandleGetData_task){	//������Ϣ��������
			IotTaskflag.IotHandleGetData_task = 0;
			if (IOT_HandleGetData(SubscirbMessage)) {
				PC_printf("RecieveMessage:%s\r\n",SubscirbMessage);
				LED_Status=Parse_JsonMessage("LEDSwitch", SubscirbMessage);
				HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, LED_Status);
			}
		}

		if(IotTaskflag.IotPing_task){	//��������������
			IotTaskflag.IotPing_task = 0;
			IOT_Ping();
			return ;
		}

		if(IotTaskflag.IotSubscribe_task){	//������������
			IotTaskflag.IotSubscribe_task = 0;
			IOT_Subscribe(S_TOPIC_NAME);
			return ;
		}

		if(IotTaskflag.IotPublish_task){	//������Ϣ����
			IotTaskflag.IotPublish_task = 0;
			LED_Status = HAL_GPIO_ReadPin(LD3_GPIO_Port,LD3_Pin);
			Creat_JsonMessage("thing.service.property.set", "123456", LED_Status ,PublishMessage);
			IOT_Publish(P_TOPIC_NAME,PublishMessage);
			return ;
		}



	}
	return ;
}

/*********************************************************
 * ��������: IOT��ʼ��
 * �������: ��
 *
 * �� �� ֵ: ��
 *
 * ˵    �����û�ʹ��
 *
 */
void IOT_Init(void)
{
	IOT_Connect();
	HAL_Delay(100);
	IotTaskflag.IotSubscribe_task = 1;
	IotTaskflag.IotPublish_task = 1;
}
