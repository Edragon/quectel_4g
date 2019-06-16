#include "EC20.h"
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
void  EC20_Init(void)
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
		printf("AT+QICLOSE=0\r\n");//断开连接
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


}		


