#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

// NVIC - Birden fazla kesme olduðundan bu kesmelerin bir arada uyumlu çalýþmasýný saðlamak için yapýlmýþ bir sistemdir.
// EXTI - Harici bir kaynaktan oluþan olaylardan dolayý meydana gelen kesmelere, harici kesmeler denir.Harici kaynak olarak, dýþ ortamdan
//		  pinler vasýtasýyla gelecek kesme ve kendi içindeki donanýmlardan gelen kesmeleri anlayabiliriz.

GPIO_InitTypeDef GPIO_InitStruct;	// GPIO_InitStruct: Belirtilen GPIO çevre birimi için yapýlandýrma bilgilerini içeren bir GPIO_InitTypeDef yapýsýnýn iþaretçisi.
EXTI_InitTypeDef EXTI_InitStruct;	// EXTI_InitStruct: EXTI çevre birimi için yapýlandýrma bilgilerini içeren bir EXTI_InitTypeDef yapýsýnýn iþaretçisi.
NVIC_InitTypeDef NVIC_InitStruct;	// NVIC_InitStruct: Belirtilen NVIC çevre birimi için yapýlandýrma bilgilerini içeren bir NVIC_InitTypeDef yapýsýnýn iþaretçisi.

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	// AHB1 çevre birimini saatine geçiþ yapmak için belirtir

	// LED -->
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;		// Yapýlandýrýlacak GPIO pinlerini belirtir
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;												// Seçilen pinler için çalýþma modunu belirtir
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;												// Seçilen pinler için çalýþma çýkýþ tipini belirtir
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;											// Seçilen pinler için çalýþan Pull-up/Pull-down'ý belirtir
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;											// Seçilen pinler için hýzý belirtir

	GPIO_Init(GPIOD, &GPIO_InitStruct);	// GPIOx çevre birimini GPIO_InitStruct içinde belirtilen parametrelere göre baþlatýr.

	// BUTON -->
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);	// GPIOx çevre birimini GPIO_InitStruct içinde belirtilen parametrelere göre baþlatýr.
}

void EXTI_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); 	// APB2 çevre birimini saatine geçiþ yapmak için belirtir

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, GPIO_PinSource0); // SYSCFG_EXTILineConfig() kullanarak EXTI hattý için giriþ kaynaðý pinini seçer.

	EXTI_InitStruct.EXTI_Line = EXTI_Line0;				// Etkinleþtirilecek veya devre dýþý býrakýlacak EXTI satýrlarýný belirtir
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;				// Seçili EXTI satýrlarýnýn yeni durumunu belirtir
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;	// EXTI hatlarýnýn modunu belirtir
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;	// EXTI hatlarý için tetik sinyali aktif kenarýný belirtir

	EXTI_Init(&EXTI_InitStruct); // EXTI çevre birimini, EXTI_InitStruct içinde belirtilen parametrelere göre baþlatýr.

	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;		//	Etkinleþtirilecek veya devre dýþý býrakýlacak IRQ kanalýný belirtir.
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;		//	NVIC_IRQChannel'da tanýmlanan IRQ kanalýnýn etkinleþtirilip etkinleþtirilmeyeceðini belirtir
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;	// NVIC_IRQChannel'da belirtilen IRQ kanalý için ön alým önceliðini belirtir. Bu parametre 0 ile 15 arasýnda bir deðer olabilir.
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;			// NVIC_IRQChannel içinde belirtilen IRQ kanalý için alt öncelik düzeyini belirtir. Bu parametre 0 ile 15 arasýnda bir deðer olabilir.

	NVIC_Init(&NVIC_InitStruct);	// NVIC çevre birimini, NVIC_InitStruct içinde belirtilen parametrelere göre baþlatýr.
}

void delay(uint32_t time)
{
	while(time--);
}

void EXTI0_IRQHandler()		//
{
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)	// Belirtilen EXTI satýrýnýn geçerli olup olmadýðýný kontrol eder.
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
