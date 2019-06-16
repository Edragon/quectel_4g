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
    delay_init();	    	 //��ʱ������ʼ��	  
    NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
    uart_init(115200);//����1��ʼ��������EC20ģ��
    delay_ms(500);
    PWRKEY=0;//ģ�鿪��
    EC20_Init(); //GPRS��ʼ��
    printf("ATD15956936278;\r\n");//����绰,����������֧�ֵ绰
    delay_ms(500);
    Clear_Buffer();	
    while(1) 
    {
        strx=strstr((const char*)RxBuffer,(const char*)"NO CARRIER");//�������˽���
        if(strx)
        {
            Uart1_SendStr("ͨ���Ѿ�����\r\n");
            Clear_Buffer();	
            while(1);
        }
    }
 }





