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
        printf("+++");
        delay_ms(500);
        printf("+++");
        delay_ms(500);
		EC20_Init(); //GPRS初始化,设置为透传模式
      
		while(1)
		{
			printf("Transparent Data!\r\n");//透传下不接收指令，会把一切作为指令来看待,数据接收也是在串口1当中直接接收
            delay_ms(500);
        
		}
}






