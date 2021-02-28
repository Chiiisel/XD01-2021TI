#ifndef __IOT_SERVE_H
#define __IOT_SERVE_H

#include "stm32f4xx_hal.h"
#include "MQTTPacket.h"
#include "utils_hmac.h"
#include "my_uart.h"
#include "transport.h"
#include <stdarg.h>
#include "cJSON.h"

extern uint16_t buflen;
extern unsigned char buf[200];

/*********服务器信息*********************/
#define IOT_DOMAIN_NAME "a1REnRPxsPv.iot-as-mqtt.cn-shanghai.aliyuncs.com"
#define IOT_PORTNUM 	"1883"

#define  PRODUCTKEY			"a1REnRPxsPv"
#define  PRODUCTKEY_LEN		strlen(PRODUCTKEY)
#define  DEVICENAME			"ESP8266"
#define  DEVICENAME_LEN		strlen(DEVICENAME)
#define  DEVICESECRE		"22ad6868e1272af12df1321a7fd25501"
#define  DEVICESECRE_LEN	strlen(DEVICESECRE)

/**********订阅与发布信息***************/
#define  S_TOPIC_NAME         "/sys/a1REnRPxsPv/ESP8266/thing/service/property/set"
#define  P_TOPIC_NAME         "/sys/a1REnRPxsPv/ESP8266/thing/event/property/post"

//typedef struct
//{
//char *methodData;
//char *idData;
//char *paramsName;
//char *paramsData;
//
//}JsonMessageTypeDef;		//json格式发送主题

void PC_printf(const char *format, ...);
uint8_t IOT_Connect(void);
uint8_t IOT_Ping(void);
uint8_t IOT_Publish(char *pTopic,char *payload);
uint8_t Creat_JsonMessage(char *methodData,char *idData,u_int8_t STATUS,char **Message);
void json_pack(void);
#endif /*__IOT_ALI_H*/
