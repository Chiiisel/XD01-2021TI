/*
 * 		Name:	iot_serve.c
 *
 *  	Created on: 2021年2月21日
 *      Author: cHisel
 *     	Description:
 *
 *		功	  能：	连接阿里云服务器
 *   	使用方法：	初始化时使用IOT_Connect()来连接云服务器并保持
 *					一开始需要开启订阅IOT_Subscribe()
 *					在while1中加入IOT_TaskHandle();
 *
 */

#include "iot_serve.h"


IotTaskTypeDef IotTaskflag={0,0,0,0};
char PublishMessage[100]={0};
char SubscirbMessage[200]={0};

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
uint8_t IotConnect_Flag=0;

char ClientID[128];
uint8_t ClientID_len;

char Username[128];
uint8_t Username_len;

char Password[128];
uint8_t Password_len;

uint16_t buflen=200;
unsigned char buf[200];
/**
 * 函数功能: 连接云服务器
 * 输入参数: 无
 * 返 回 值: 1 成功
 * 			 0 失败
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
	data.keepAliveInterval = 70;							//保活计时器，定义了服务器收到客户端消息的最大时间间隔,单位是秒
	data.cleansession = 1;									//该标志置1服务器必须丢弃之前保持的客户端的信息，将该连接视为“不存在”
	data.username.cstring = Username;						//用户名 DeviceName&ProductKey
	data.password.cstring = Password;						//密码，工具生成

	len = MQTTSerialize_connect(buf, buflen, &data); 		/*1 构造连接报文*/
	transport_sendPacketBuffer(3,buf, len);				//发送连接请求

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
	if (MQTTPacket_read(buf, buflen, transport_getdata)== CONNACK)
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
 * 函数功能: 发送心跳包
 * 输入参数: 无
 * 返 回 值: 0  保持连接成功
 * 			 1	保持连接失败
 * 说    明：用于保持服务器连接
 */
uint8_t IOT_Ping(void)
{
	if(IotConnect_Flag){

		PC_printf("Ping...\r\n");
		buflen = sizeof(buf);
		uint32_t len;
		len = MQTTSerialize_pingreq(buf, buflen);
		transport_sendPacketBuffer(NULL, buf, len);

		if (MQTTPacket_read(buf, buflen, transport_getdata) == PINGRESP){
			PC_printf("Pong\r\n");
			return 0;
		}
		else {
			PC_printf("OOPS\r\n");
			return 1;
		}
	}
	return 0;
}


/****************************************
 * 函数功能: 创建cjson格式的发布信息
 * 输入参数: method数据
 * 			 id数据
 * 			 STATUS 需要上传的数据
 *
 *			 Message 操作的字符串
 * 返 回 值: 1
 *
 * 说    明：标准格式如下
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

	/************这里是标准的使用cjson开源代码库生成的方法，但是添加数字部分始终不能成功，有一点小bug********/
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
 * 函数功能: 解析cjson格式的接收信息
 * 输入参数: StatusName  目标状态的名称
 * 			 Message	需要处理的字符串

 * 返 回 值: 1
 *
 * 说    明：
 *
 */
cjsonMessageTypeDef cjsonMessage;
uint8_t Parse_JsonMessage(char *StatusName,char *Message)
{
	uint8_t Message_data;
	cJSON   *root, *params;
	root = cJSON_Parse(Message);
	if(root){
		cjsonMessage.method = cJSON_GetObjectItem(root, "method")->valuestring;//字符串型
		cjsonMessage.id = cJSON_GetObjectItem(root, "id")->valuestring;//字符串型

		params = cJSON_GetObjectItem(root, "params");
		if(params){
			cjsonMessage.Status = cJSON_GetObjectItem(params, StatusName)->valueint;//字符串型
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
 * 函数功能: 发布消息
 * 输入参数: pTopic发布主题
 * 			 payload消息内容
 *
 * 返 回 值: 1成功
 * 			 0失败
 *
 * 说    明：注意发布消息的格式，使用Creat_JsonMessage();
 *
 */
uint8_t IOT_Publish(char *pTopic,char *payload)
{
	if(IotConnect_Flag){
		buflen = sizeof(buf);
		int rc = 0;
		int mysock = 0;
		int payloadlen = strlen(payload);
		int len = 0;
		MQTTString topicString = MQTTString_initializer;
		topicString.cstring = pTopic;
		len = MQTTSerialize_publish(buf, buflen, 0, 0, 0, 0, topicString, (unsigned char*)payload, payloadlen);//第二个0是设置qos等级，阿里云仅支持qos0和1
		rc = transport_sendPacketBuffer(mysock, (unsigned char*)buf, len);
		PC_printf("Message:%s\r\n",buf);//
		PC_printf("Successfully Published\r\n");
		return 1;
	}
	return 0;
}


/*********************************************************
 * 函数功能: 订阅主题
 * 输入参数: pTopic要订阅的主题
 *
 * 返 回 值: 1成功
 * 			 0失败
 *
 * 说    明：这里只用于订阅主题，建立连接后订阅一次即可
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

		//等待服务器答复
		//SUBACK
		if (MQTTPacket_read(buf, buflen, transport_getdata) == SUBACK) 	/* 等待 suback */
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
 * 函数功能: 解析服务器端发来的消息
 * 输入参数:
 *
 * 返 回 值:
 *
 * 说    明：
 *
 */
uint8_t IOT_HandleGetData(char *Message){
	if(IotConnect_Flag){
		buflen = sizeof(buf);
		if (MQTTPacket_read(buf, buflen, transport_getdata) == PUBLISH)
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
			Message = payload_in;

			int len = MQTTSerialize_puback(buf,buflen,msgid);
			transport_sendPacketBuffer(1, buf, len);
			return 1;
		}
		else
			return 0;

	}
	return 0;
}



/*********************************************************
 * 函数功能: IOT任务处理
 * 输入参数: 无
 *
 * 返 回 值: 无
 *
 * 说    明：放在while1中循环执行
 * 			用于处理各种IOT事件
 * 			在需要的地方将IotTaskflag.置1
 *
 */
void IOT_TaskHandle(void){
	if(IotConnect_Flag){

//		if(IotTaskflag.IotHandleGetData_task){
//			IotTaskflag.IotHandleGetData_task = 0;
//			IOT_HandleGetData(SubscirbMessage);
//		}
		if(IotTaskflag.IotPing_task){
			IotTaskflag.IotPing_task = 0;
			IOT_Ping();
			return ;
		}
		if(IotTaskflag.IotPublish_task){
			IotTaskflag.IotPublish_task = 0;
			Creat_JsonMessage("thing.service.property.set", "123456", HAL_GPIO_ReadPin(LD3_GPIO_Port,LD3_Pin),PublishMessage);
			PC_printf("PublishMessage:%s\r\n",PublishMessage);
			IOT_Publish(P_TOPIC_NAME,PublishMessage);
			return ;
		}
		if(IotTaskflag.IotSubscribe_task){
			IotTaskflag.IotSubscribe_task = 0;
			IOT_Subscribe(S_TOPIC_NAME);
			return ;
		}

	}
	return ;
}
