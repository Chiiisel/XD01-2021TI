#ifndef __IOT_ALI_H
#define __IOT_ALI_H

#include "stm32f4xx_hal.h"
#include "MQTTPacket.h"
#include "utils_hmac.h"
#include "my_uart.h"
#include "transport.h"
#include <stdarg.h>

extern uint16_t buflen;
extern unsigned char buf[200];

/*********服务器信息*********************/

#define  PRODUCTKEY			"a1REnRPxsPv"
#define  PRODUCTKEY_LEN		strlen(PRODUCTKEY)
#define  DEVICENAME			"ESP8266"
#define  DEVICENAME_LEN		strlen(DEVICENAME)
#define  DEVICESECRE		"22ad6868e1272af12df1321a7fd25501"
#define  DEVICESECRE_LEN	strlen(DEVICESECRE)

void PC_printf(const char *format, ...);
uint8_t IoT_Connect(void);
uint8_t IoT_ping(void);
uint8_t IOT_TEST(void);


#endif /*__IOT_ALI_H*/
