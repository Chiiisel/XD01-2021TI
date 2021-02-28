#ifndef __transport_H
#define __transport_H

#include "stm32f4xx_hal.h"
#include "my_uart.h"
#include "esp8266_at.h"
#include "iot_serve.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UART_RX_BUF_SIZE	1024

/* º¯ÊıÉùÃ÷ */
int transport_sendPacketBuffer(int sock, unsigned char* buf, int buflen);
int transport_getdata(unsigned char* buf, int count);
int transport_getdatanb(void *sck, unsigned char* buf, int count);
int transport_open(char* addr, char* port);
int transport_close(int sock);


#endif  /* __transport_H */
