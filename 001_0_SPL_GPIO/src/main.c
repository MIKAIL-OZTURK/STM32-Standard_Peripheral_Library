#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;	// GPIO_InitTypeDef - Belirtilen GPIO �evre birimi i�in yap�land�rma bilgilerini i�eren bir GPIO_InitTypeDef yap�s�na i�aret�i.

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	// AHB1 �evre birimini saatine ge�i� yapmak i�in belirtir


	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;		// Yap�land�r�lacak GPIO pinlerini belirtir
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;												// Se�ilen pinler i�in �al��ma modunu belirtir
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;												// Se�ilen pinler i�in �al��ma ��k�� tipini belirtir
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;											// Se�ilen pinler i�in �al��an Pull-up/Pull-down'� belirtir
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;											// Se�ilen pinler i�in h�z� belirtir

	GPIO_Init(GPIOD, &GPIO_InitStruct);	// GPIOx �evre birimini GPIO_InitStruct i�inde belirtilen parametrelere g�re ba�lat�r.
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
		  GPIO_SetBits(GPIOD, GPIO_Pin_All);		// Se�ili veri ba�lant� noktas� bitlerini ayarlar.
		  delay(1680000);

		  GPIO_ResetBits(GPIOD, GPIO_Pin_All);		// Se�ili veri ba�lant� noktas� bitlerini temizler.
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
