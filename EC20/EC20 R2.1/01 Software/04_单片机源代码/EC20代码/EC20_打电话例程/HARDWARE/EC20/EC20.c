#include "EC20.h"
#include "usart.h"	 
#include "stdlib.h"
#include "string.h"
#include "wdg.h"
#include "delay.h"
char *strx=0,*extstrx,*Readystrx,*Errstrx; 	//����ֵָ���ж�
char Timestr[100];//ʱ���ַ���
extern char  RxBuffer[100],RxCounter;
void Uart1_SendStr(char*SendBuf)//����1��ӡ����
{
	while(*SendBuf)
	{
	  while((USART1->SR&0X40)==0);//�ȴ�������� 
    USART1->DR = (u8) *SendBuf; 
		SendBuf++;
	}
}
void Clear_Buffer(void)//��ջ���
{
		u8 i;
		for(i=0;i<RxCounter;i++)
		RxBuffer[i]=0;//����
		RxCounter=0;
		IWDG_Feed();//ι��
}
void  EC20_Init(void)
{
		int i;
	
		printf("AT\r\n"); 
		delay_ms(500);
		printf("AT\r\n"); 
		delay_ms(500);
		strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
		while(strx==NULL)
		{
				Clear_Buffer();	
				printf("AT\r\n"); 
				delay_ms(500);
				strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
		}
		printf("ATE0\r\n"); //�رջ���
		delay_ms(500);
		Clear_Buffer();	
		printf("AT+CSQ\r\n"); //���CSQ
		delay_ms(500);
		/////////////////////////////////
		printf("AT+CPIN?\r\n");//���SIM���Ƿ���λ
		delay_ms(500);
		strx=strstr((const char*)RxBuffer,(const char*)"+CPIN: READY");//�鿴�Ƿ񷵻�ready
		while(strx==NULL)
		{
				Clear_Buffer();
				printf("AT+CPIN?\r\n");
				delay_ms(500);
				strx=strstr((const char*)RxBuffer,(const char*)"+CPIN: READY");//���SIM���Ƿ���λ���ȴ�����λ�������ʶ�𲻵���ʣ��Ĺ�����û������
		}
		Clear_Buffer();	
			///////////////////////////////////
		printf("AT+QICLOSE=0\r\n");//�Ͽ�����
		delay_ms(500);
		///////////////////////////////////
		printf("AT+CREG?\r\n");//�鿴�Ƿ�ע��GSM����
		delay_ms(500);
		strx=strstr((const char*)RxBuffer,(const char*)"+CREG: 0,1");//��������
		extstrx=strstr((const char*)RxBuffer,(const char*)"+CREG: 0,5");//��������������
		while(strx==NULL&&extstrx==NULL)
		{
				Clear_Buffer();
				printf("AT+CREG?\r\n");//�鿴�Ƿ�ע��GSM����
				delay_ms(500);
				strx=strstr((const char*)RxBuffer,(const char*)"+CREG: 0,1");//��������
				extstrx=strstr((const char*)RxBuffer,(const char*)"+CREG: 0,5");//��������������
		}
		Clear_Buffer();


}		


