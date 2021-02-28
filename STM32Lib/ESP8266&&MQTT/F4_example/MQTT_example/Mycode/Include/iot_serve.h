#ifndef __IOT_SERVE_H
#define __IOT_SERVE_H

#include "stm32f4xx_hal.h"
#include "MQTTPacket.h"
#include "utils_hmac.h"
#include "my_uart.h"
#include "transport.h"
#include <stdarg.h>
#include <string.h>
#include "cJSON.h"

extern uint16_t buflen;
extern unsigned char buf[200];

/*********��������Ϣ*********************/
#define IOT_DOMAIN_NAME "a1REnRPxsPv.iot-as-mqtt.cn-shanghai.aliyuncs.com"		//��������ַ
#define IOT_PORTNUM 	"1883"													//�������˿�

#define  PRODUCTKEY			"a1REnRPxsPv"							//ProductKey
#define  PRODUCTKEY_LEN		strlen(PRODUCTKEY)
#define  DEVICENAME			"ESP8266"								//�豸����
#define  DEVICENAME_LEN		strlen(DEVICENAME)
#define  DEVICESECRE		"22ad6868e1272af12df1321a7fd25501"		//DeviceSecret����
#define  DEVICESECRE_LEN	strlen(DEVICESECRE)

/**********�����뷢����Ϣ***************/
#define  S_TOPIC_NAME         "/sys/a1REnRPxsPv/ESP8266/thing/service/property/set"			//��������
#define  P_TOPIC_NAME         "/sys/a1REnRPxsPv/ESP8266/thing/event/property/post"			//��������

typedef struct
{
	char *method;//[40];
	char *id;//[10];
	char *params;//[50];
	uint8_t Status;
//	char *paramsData;//[10];
}cjsonMessageTypeDef;		//IOT������


typedef struct
{
	uint8_t IotPublish_task;
	uint8_t IotPing_task;
	uint8_t IotSubscribe_task;
	uint8_t IotHandleGetData_task;
}IotTaskTypeDef;		//IOT������

extern uint8_t IotConnect_Flag;
extern IotTaskTypeDef IotTaskflag;

/****************��������*************************/
void PC_printf(const char *format, ...);
uint8_t IOT_Connect(void);
uint8_t IOT_Ping(void);
uint8_t Creat_JsonMessage(char *methodData,char *idData,u_int8_t STATUS,char *Message);
uint8_t Parse_JsonMessage(char *StatusName,char *Message);
uint8_t IOT_Publish(char *pTopic,char *payload);
uint8_t IOT_Subscribe(char *pTopic);
uint8_t IOT_HandleGetData(char *Message);
void IOT_TaskHandle(void);
#endif /*__IOT_ALI_H*/
