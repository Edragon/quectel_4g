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
    u8 sendstr[]="EC20 Send English Text!";//输入自己需要发送的英文短信内容即可
	u8 phone[11]="13979988236";//输入自己的手机号码即可
    delay_init();	    	 //延时函数初始化	  
    NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    LED_Init();		  		//初始化与LED连接的硬件接口
    uart_init(115200);//串口1初始化，连接EC20模块
    delay_ms(500);
    PWRKEY=0;//模块开机
    EC20_Init(); //GPRS初始化
    Send_Text(phone,sendstr);//短信发送
 while(1) 
    {
        delay_ms(500);
    }
 }





