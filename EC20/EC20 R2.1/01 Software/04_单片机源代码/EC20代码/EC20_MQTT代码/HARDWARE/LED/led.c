#include "led.h"


//��ʼ��PA0
//LED IO��ʼ��
void LED_Init(void)
{
 
		GPIO_InitTypeDef  GPIO_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PA�˿�ʱ��
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
        GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //LED0-->PA0 �˿�����
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
		GPIO_Init(GPIOA, &GPIO_InitStructure);
        GPIO_ResetBits(GPIOA,GPIO_Pin_0);	 //�����趨������ʼ��GPIOA0
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //PWRKEY-->PA8 �˿�����
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
		GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA0
		GPIO_SetBits(GPIOA,GPIO_Pin_0);						 //PA0 �����
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //PWRKEY-->PA8 �˿�����
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
		GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA0
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);						 //PA0 �����
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				 //PWRKEY-->PA8 �˿�����
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
		GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA0
		GPIO_ResetBits(GPIOB,GPIO_Pin_3);	
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 //LED0-->PA0 �˿�����
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
		GPIO_Init(GPIOA, &GPIO_InitStructure);		
        GPIO_ResetBits(GPIOA,GPIO_Pin_7);	
		 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //LED0-->PA0 �˿�����
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
		GPIO_Init(GPIOB, &GPIO_InitStructure);		
	
}
 

