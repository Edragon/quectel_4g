#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"	 
#include "math.h"			
#include "stdio.h"
#include "stm32f10x_flash.h"
#include "stdlib.h"
#include "string.h"
#include "wdg.h"
#include "m26.h"
extern char Timestr[100];//时间字符串
extern char  RxBuffer[100],RxCounter;
 int main(void)
 {	
        char  *strx;
		delay_init();	    	 //延时函数初始化	  
		NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
		LED_Init();		  		//初始化与LED连接的硬件接口
		uart_init(115200);//串口1初始化，连接EC20模块
        delay_ms(500);
	 	PWRKEY=0;//模块开机
        LED=0;
        LED1=1;
		GSM_Init(); //GPRS初始化
        MQTT_Init();
		while(1)
		{
			printf("AT+QMTPUB=0,0,0,0,\"mzh_pub\"\r\n");//发布消息
            delay_ms(500);
            printf("This is test data, hello MQTT");//发布数据
            while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
            USART1->DR = (u8) 0x1a;//结束符   
		    strx=strstr((const char*)RxBuffer,(const char*)"+QMTRECV: ");//订阅成功+QMTRECV: 
            if(strx)
            {
                //Uart1_SendStr(RxBuffer);
            } 
            delay_ms(500);
            RxCounter=0;
		}
}






