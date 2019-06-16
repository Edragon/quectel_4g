
#include "RTC_Alarm.h"
#include "stm32f10x_rtc.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_bkp.h"
#include "led.h"
//RTC�ж�����
 void RTC_NVIC_Config(void)
{    
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;        //RTCȫ���ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;    //��ռ���ȼ�1λ,�����ȼ�3λ
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;   
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;        //ʹ�ܸ�ͨ���ж�
    NVIC_Init(&NVIC_InitStructure);        //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
}

//RTC���ӳ�ʼ��:����ʱ�ӡ�����LSI��RTCʱ�ӡ�����Ԥ��Ƶ40000�õ�1Hz
//��������ʱ��WORK_TIMES
void RTC_Alarm_Configuration(void)
{
	/* Enable PWR and BKP clocks */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	/* Allow access to BKP Domain */
	PWR_BackupAccessCmd(ENABLE);	
	/* Reset Backup Domain */
	BKP_DeInit();

    /* RTC clock source configuration ----------------------------------------*/
	/* Enable the LSI OSC */
  	RCC_LSICmd(ENABLE);
    /* Wait till LSI is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
    {
    }
    /* Select the RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
    /* Enable the RTC Clock */
    RCC_RTCCLKCmd(ENABLE);
	/* Wait for RTC registers synchronization */
	RTC_WaitForSynchro();
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask(); 
	/* ʹ��RTC�����ж�*/
	RTC_ITConfig(RTC_IT_ALR, ENABLE);	
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();	
	/* Set RTC prescaler: set RTC period to 1sec */
	RTC_SetPrescaler(40000);	
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
		
	//�ж�����
	RTC_NVIC_Config();

	//��������WORK_TIMES
	RTC_SetAlarm(RTC_GetCounter() + WORK_TIMES);
	RTC_WaitForLastTask();
}

//��������ʱ�����������
//sΪ�ж�����
void RTC_Enter_StandbyMode(u32 s)
{

    RTC_SetAlarm(RTC_GetCounter() + s);
    RTC_WaitForLastTask();
    // �������ģʽ, ��ʱ����1.8V���ʱ�Ӷ��ر�,HIS��HSE�������ر�, ��ѹ�������ر�.
    // ֻ��WKUP����������,RTC�����¼�,NRST���ŵ��ⲿ��λ,IWDG��λ.
	/* Request to enter STANDBY mode (Wake Up flag is cleared in PWR_EnterSTANDBYMode function) */
   // PWR_EnterSTANDBYMode();
}

//�жϷ�����
void RTC_IRQHandler(void)
{
 if(RTC_GetITStatus(RTC_IT_ALR)!= RESET)//�����ж�
 {
  	RTC_ClearITPendingBit(RTC_IT_ALR);  //�������ж�
	RTC_Enter_StandbyMode(STANDBY_TIMES);//�������
 }                 
}


