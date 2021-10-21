#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;	// GPIO_InitTypeDef - Belirtilen GPIO çevre birimi için yapýlandýrma bilgilerini içeren bir GPIO_InitTypeDef yapýsýna iþaretçi.

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	// AHB1 çevre birimini saatine geçiþ yapmak için belirtir


	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;		// Yapýlandýrýlacak GPIO pinlerini belirtir
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;												// Seçilen pinler için çalýþma modunu belirtir
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;												// Seçilen pinler için çalýþma çýkýþ tipini belirtir
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;											// Seçilen pinler için çalýþan Pull-up/Pull-down'ý belirtir
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;											// Seçilen pinler için hýzý belirtir

	GPIO_Init(GPIOD, &GPIO_InitStruct);	// GPIOx çevre birimini GPIO_InitStruct içinde belirtilen parametrelere göre baþlatýr.
}

void delay(uint32_t time)
{
	while(time--);
}

int main(void)
{
	GPIO_Config();

	while(1)
	{
		  GPIO_SetBits(GPIOD, GPIO_Pin_All);		// Seçili veri baðlantý noktasý bitlerini ayarlar.
		  delay(1680000);

		  GPIO_ResetBits(GPIOD, GPIO_Pin_All);		// Seçili veri baðlantý noktasý bitlerini temizler.
		  delay(1680000);
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
