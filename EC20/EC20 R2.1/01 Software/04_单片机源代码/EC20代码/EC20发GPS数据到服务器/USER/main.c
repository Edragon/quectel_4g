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
#include "EC20.h"
extern char RxCounter,RxBuffer[100]; 
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
		EC20_Init(); //GPRS初始化,设置为透传模式
      
		while(1)
		{
            printf("AT+QGPSGNMEA=\042RMC\042\r\n");//读取GPS定位数据
            delay_ms(500);
            strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
            while(strx==NULL)
            {
                strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
            }	
            EC20Send_StrData(RxBuffer);//通过EC20将数据发送出去
        }
        

}






