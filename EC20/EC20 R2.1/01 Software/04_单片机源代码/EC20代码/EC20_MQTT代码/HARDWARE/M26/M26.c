#include "M26.h"
#include "usart.h"	 
#include "stdlib.h"
#include "string.h"
#include "wdg.h"
#include "delay.h"
char *strx=0,*extstrx,*Readystrx,*Errstrx; 	//返回值指针判断
char Timestr[100];//时间字符串
extern char  RxBuffer[100],RxCounter;
void Uart1_SendStr(char*SendBuf)//串口1打印数据
{
	while(*SendBuf)
	{
	  while((USART1->SR&0X40)==0);//等待发送完成 
    USART1->DR = (u8) *SendBuf; 
		SendBuf++;
	}
}
void Clear_Buffer(void)//清空缓存
{
		u8 i;
		for(i=0;i<RxCounter;i++)
		RxBuffer[i]=0;//缓存
		RxCounter=0;
		IWDG_Feed();//喂狗
}
void  GSM_Init(void)
{
		int i;
	
		printf("AT\r\n"); 
		delay_ms(500);
		printf("AT\r\n"); 
		delay_ms(500);
		strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
		while(strx==NULL)
		{
				Clear_Buffer();	
				printf("AT\r\n"); 
				delay_ms(500);
				strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
		}
		printf("ATE0\r\n"); //关闭回显
		delay_ms(500);
		Clear_Buffer();	
		printf("AT+CSQ\r\n"); //检查CSQ
		delay_ms(500);
		/////////////////////////////////
		printf("AT+CPIN?\r\n");//检查SIM卡是否在位
		delay_ms(500);
		strx=strstr((const char*)RxBuffer,(const char*)"+CPIN: READY");//查看是否返回ready
		while(strx==NULL)
		{
				Clear_Buffer();
				printf("AT+CPIN?\r\n");
				delay_ms(500);
				strx=strstr((const char*)RxBuffer,(const char*)"+CPIN: READY");//检查SIM卡是否在位，等待卡在位，如果卡识别不到，剩余的工作就没法做了
		}
		Clear_Buffer();	
			///////////////////////////////////
		printf("AT+QMTCLOSE=0\r\n");//断开MQTT连接
		delay_ms(500);
		///////////////////////////////////
		printf("AT+CREG?\r\n");//查看是否注册GSM网络
		delay_ms(500);
		strx=strstr((const char*)RxBuffer,(const char*)"+CREG: 0,1");//返回正常
		extstrx=strstr((const char*)RxBuffer,(const char*)"+CREG: 0,5");//返回正常，漫游
		while(strx==NULL&&extstrx==NULL)
		{
				Clear_Buffer();
				printf("AT+CREG?\r\n");//查看是否注册GSM网络
				delay_ms(500);
				strx=strstr((const char*)RxBuffer,(const char*)"+CREG: 0,1");//返回正常
				extstrx=strstr((const char*)RxBuffer,(const char*)"+CREG: 0,5");//返回正常，漫游
		}
		Clear_Buffer();
		/////////////////////////////////////
		printf("AT+CGREG?\r\n");//查看是否注册GPRS网络
		delay_ms(500);
		strx=strstr((const char*)RxBuffer,(const char*)"+CGREG: 0,1");//，这里重要，只有注册成功，才可以进行GPRS数据传输。
		extstrx=strstr((const char*)RxBuffer,(const char*)"+CGREG: 0,5");//返回正常，漫游
		while(strx==NULL&&extstrx==NULL)
		{
				Clear_Buffer();
				printf("AT+CGREG?\r\n");//查看是否注册GPRS网络
				delay_ms(500);
				strx=strstr((const char*)RxBuffer,(const char*)"+CGREG: 0,1");//，这里重要，只有注册成功，才可以进行GPRS数据传输。
				extstrx=strstr((const char*)RxBuffer,(const char*)"+CGREG: 0,5");//返回正常，漫游
		}
		Clear_Buffer();
	
}		


void  MQTT_Init(void)
{
    printf("AT+QMTOPEN=0,\"198.41.30.241\",1883\r\n");//通过TCP方式去连接MQTT服务器 
    delay_ms(500);
    strx=strstr((const char*)RxBuffer,(const char*)"+QMTOPEN: 0,0");//看下返回状态
    while(strx==NULL)
    {
      strx=strstr((const char*)RxBuffer,(const char*)"+QMTOPEN: 0,0");//确认返回值正确
    }
    Clear_Buffer(); 
   printf("AT+QMTCONN=0,\"clientExample\",\"username\",\"password\"\r\n");//去登录MQTT服务器，设备ID，账号和密码.用户根据实际需要进行更改
    delay_ms(500);
    strx=strstr((const char*)RxBuffer,(const char*)"+QMTCONN: 0,0,0");//看下返回状态
  while(strx==NULL)
    {
        strx=strstr((const char*)RxBuffer,(const char*)"+QMTCONN: 0,0,0");//看下返回状态
    }
    Clear_Buffer(); 
    printf("AT+QMTSUB=0,1,\"MZH_EC20\",0\r\n");//订阅个主题
        delay_ms(500);
    strx=strstr((const char*)RxBuffer,(const char*)"+QMTSUB: 0,1,0,0");//订阅成功
  while(strx==NULL)
    {
        strx=strstr((const char*)RxBuffer,(const char*)"+QMTSUB: 0,1,0,0");//订阅成功
    }
    Clear_Buffer(); 
}