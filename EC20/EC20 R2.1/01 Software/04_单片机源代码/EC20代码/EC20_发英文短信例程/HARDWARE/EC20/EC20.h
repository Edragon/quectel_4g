#ifndef __EC20_H
#define __EC20_H	
#include "stm32f10x.h"
void Uart1_SendStr(char*SendBuf);//����1��ӡ����;
void Clear_Buffer(void);//��ջ���
void  EC20_Init(void);//M26��ʼ��
void Send_Str(char*data);//��������
void  MQTT_Init(void);
void Send_Text(char *phone,char *data);
#endif  

