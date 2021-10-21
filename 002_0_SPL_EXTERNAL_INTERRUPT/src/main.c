#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

// NVIC - Birden fazla kesme oldu�undan bu kesmelerin bir arada uyumlu �al��mas�n� sa�lamak i�in yap�lm�� bir sistemdir.
// EXTI - Harici bir kaynaktan olu�an olaylardan dolay� meydana gelen kesmelere, harici kesmeler denir.Harici kaynak olarak, d�� ortamdan
//		  pinler vas�tas�yla gelecek kesme ve kendi i�indeki donan�mlardan gelen kesmeleri anlayabiliriz.

GPIO_InitTypeDef GPIO_InitStruct;	// GPIO_InitStruct: Belirtilen GPIO �evre birimi i�in yap�land�rma bilgilerini i�eren bir GPIO_InitTypeDef yap�s�n�n i�aret�isi.
EXTI_InitTypeDef EXTI_InitStruct;	// EXTI_InitStruct: EXTI �evre birimi i�in yap�land�rma bilgilerini i�eren bir EXTI_InitTypeDef yap�s�n�n i�aret�isi.
NVIC_InitTypeDef NVIC_InitStruct;	// NVIC_InitStruct: Belirtilen NVIC �evre birimi i�in yap�land�rma bilgilerini i�eren bir NVIC_InitTypeDef yap�s�n�n i�aret�isi.

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	// AHB1 �evre birimini saatine ge�i� yapmak i�in belirtir

	// LED -->
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;		// Yap�land�r�lacak GPIO pinlerini belirtir
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;												// Se�ilen pinler i�in �al��ma modunu belirtir
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;												// Se�ilen pinler i�in �al��ma ��k�� tipini belirtir
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;											// Se�ilen pinler i�in �al��an Pull-up/Pull-down'� belirtir
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;											// Se�ilen pinler i�in h�z� belirtir

	GPIO_Init(GPIOD, &GPIO_InitStruct);	// GPIOx �evre birimini GPIO_InitStruct i�inde belirtilen parametrelere g�re ba�lat�r.

	// BUTON -->
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);	// GPIOx �evre birimini GPIO_InitStruct i�inde belirtilen parametrelere g�re ba�lat�r.
}

void EXTI_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); 	// APB2 �evre birimini saatine ge�i� yapmak i�in belirtir

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, GPIO_PinSource0); // SYSCFG_EXTILineConfig() kullanarak EXTI hatt� i�in giri� kayna�� pinini se�er.

	EXTI_InitStruct.EXTI_Line = EXTI_Line0;				// Etkinle�tirilecek veya devre d��� b�rak�lacak EXTI sat�rlar�n� belirtir
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;				// Se�ili EXTI sat�rlar�n�n yeni durumunu belirtir
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;	// EXTI hatlar�n�n modunu belirtir
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;	// EXTI hatlar� i�in tetik sinyali aktif kenar�n� belirtir

	EXTI_Init(&EXTI_InitStruct); // EXTI �evre birimini, EXTI_InitStruct i�inde belirtilen parametrelere g�re ba�lat�r.

	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;		//	Etkinle�tirilecek veya devre d��� b�rak�lacak IRQ kanal�n� belirtir.
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;		//	NVIC_IRQChannel'da tan�mlanan IRQ kanal�n�n etkinle�tirilip etkinle�tirilmeyece�ini belirtir
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;	// NVIC_IRQChannel'da belirtilen IRQ kanal� i�in �n al�m �nceli�ini belirtir. Bu parametre 0 ile 15 aras�nda bir de�er olabilir.
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;			// NVIC_IRQChannel i�inde belirtilen IRQ kanal� i�in alt �ncelik d�zeyini belirtir. Bu parametre 0 ile 15 aras�nda bir de�er olabilir.

	NVIC_Init(&NVIC_InitStruct);	// NVIC �evre birimini, NVIC_InitStruct i�inde belirtilen parametrelere g�re ba�lat�r.
}

void delay(uint32_t time)
{
	while(time--);
}

void EXTI0_IRQHandler()		//
{
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)	// Belirtilen EXTI sat�r�n�n ge�erli olup olmad���n� kontrol eder.
	{
	  	 GPIO_ResetBits(GPIOD, GPIO_Pin_All);
	  	 delay(3360000);
	  	 GPIO_SetBits(GPIOD, GPIO_Pin_All);
	  	 delay(3360000);
	  	 GPIO_ResetBits(GPIOD, GPIO_Pin_All);
	  	 delay(3360000);
	  	 GPIO_SetBits(GPIOD, GPIO_Pin_All);
	  	 delay(3360000);
	  	 GPIO_ResetBits(GPIOD, GPIO_Pin_All);

	  	 EXTI_ClearITPendingBit(EXTI_Line0); // EXTI'nin bekleyen bitlerini temizler.
	}
}

int main(void)
{
	GPIO_Config();
	EXTI_Config();

	while(1)
	{
	  	 GPIO_SetBits(GPIOD, GPIO_Pin_All);
	}
}


void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}


uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
