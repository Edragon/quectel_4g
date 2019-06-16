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
        printf("AT+QGPS=1\r\n"); //打开GNSS
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
        printf("AT+QIOPEN=1,0,\042TCP\042,\042114.115.148.172\042,10000,0,1\r\n");//这里是需要登陆的IP号码，采用直接吐出模式
        delay_ms(500);
        strx=strstr((const char*)RxBuffer,(const char*)"+QIOPEN: 0,0");//检查是否登陆成功
  while(strx==NULL)
    {
        strx=strstr((const char*)RxBuffer,(const char*)"+QIOPEN: 0,0");//检查是否登陆成功
        delay_ms(100);
    }

        delay_ms(500);
        Clear_Buffer();

}		

///发送字符型数据
void EC20Send_StrData(char *bufferdata)
{
	u8 untildata=0xff;
	printf("AT+QISEND=0\r\n");
	delay_ms(100);
	printf(bufferdata);
    delay_ms(100);	
    USART_SendData(USART1, (u8) 0x1a);//发送完成函数
  while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
    {
    }
	delay_ms(100);
    strx=strstr((char*)RxBuffer,(char*)"SEND OK");//是否正确发送
  while(strx==NULL)
    {
        strx=strstr((char*)RxBuffer,(char*)"SEND OK");//是否正确发送
        delay_ms(10);
    }
    delay_ms(100);
    Clear_Buffer();
    printf("AT+QISEND=0,0\r\n");
    delay_ms(200);
    strx=strstr((char*)RxBuffer,(char*)"+QISEND:");//发送剩余字节数据
  while(untildata)//这个主要是确认服务器是否全部接收完数据，这个判断可以选择不要
    {
          printf("AT+QISEND=0,0\r\n");
          delay_ms(200);
          strx=strstr((char*)RxBuffer,(char*)"+QISEND:");//发送剩余字节数据
          strx=strstr((char*)strx,(char*)",");//获取第一个,
          strx=strstr((char*)(strx+1),(char*)",");//获取第二个,
          untildata=*(strx+1)-0x30;
    }
   Clear_Buffer();
}


