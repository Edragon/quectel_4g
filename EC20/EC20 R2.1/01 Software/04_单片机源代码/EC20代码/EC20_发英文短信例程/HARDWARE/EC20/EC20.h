#ifndef __EC20_H
#define __EC20_H	
#include "stm32f10x.h"
void Uart1_SendStr(char*SendBuf);//串口1打印数据;
void Clear_Buffer(void);//清空缓存
void  EC20_Init(void);//M26初始化
void Send_Str(char*data);//发送数据
void  MQTT_Init(void);
void Send_Text(char *phone,char *data);
#endif  

