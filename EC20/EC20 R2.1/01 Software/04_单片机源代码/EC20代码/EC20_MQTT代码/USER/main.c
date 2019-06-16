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
extern char Timestr[100];//ʱ���ַ���
extern char  RxBuffer[100],RxCounter;
 int main(void)
 {	
        char  *strx;
		delay_init();	    	 //��ʱ������ʼ��	  
		NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
		LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
		uart_init(115200);//����1��ʼ��������EC20ģ��
        delay_ms(500);
	 	PWRKEY=0;//ģ�鿪��
        LED=0;
        LED1=1;
		GSM_Init(); //GPRS��ʼ��
        MQTT_Init();
		while(1)
		{
			printf("AT+QMTPUB=0,0,0,0,\"mzh_pub\"\r\n");//������Ϣ
            delay_ms(500);
            printf("This is test data, hello MQTT");//��������
            while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
            USART1->DR = (u8) 0x1a;//������   
		    strx=strstr((const char*)RxBuffer,(const char*)"+QMTRECV: ");//���ĳɹ�+QMTRECV: 
            if(strx)
            {
                //Uart1_SendStr(RxBuffer);
            } 
            delay_ms(500);
            RxCounter=0;
		}
}






