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
		delay_init();	    	 //��ʱ������ʼ��	  
		NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
		LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
		uart_init(115200);//����1��ʼ��������EC20ģ��
        delay_ms(500);
	 	PWRKEY=0;//ģ�鿪��
        LED=0;
        LED1=1;
        printf("+++");
        delay_ms(500);
        printf("+++");
        delay_ms(500);
		EC20_Init(); //GPRS��ʼ��,����Ϊ͸��ģʽ
      
		while(1)
		{
			printf("Transparent Data!\r\n");//͸���²�����ָ����һ����Ϊָ��������,���ݽ���Ҳ���ڴ���1����ֱ�ӽ���
            delay_ms(500);
        
		}
}






