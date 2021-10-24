#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
DAC_InitTypeDef DAC_InitStruct;

int i = 0;

void delay(uint32_t time)
{
	while(time--);
}

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	// AHB1 çevre birimini saatine geçiþ yapmak için belirtir


	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;		// Yapýlandýrýlacak GPIO pinlerini belirtir
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;												// Seçilen pinler için çalýþma modunu belirtir
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;												// Seçilen pinler için çalýþma çýkýþ tipini belirtir
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;											// Seçilen pinler için çalýþan Pull-up/Pull-down'ý belirtir
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;											// Seçilen pinler için hýzý belirtir

	GPIO_Init(GPIOA, &GPIO_InitStruct);	// GPIOx çevre birimini GPIO_InitStruct içinde belirtilen parametrelere göre baþlatýr.
}


void DAC2_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

	DAC_InitStruct.DAC_Trigger = DAC_Trigger_None;					// Seçili DAC kanalý için harici tetikleyiciyi belirtir
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;	// DAC kanalý gürültü dalgalarýnýn mý yoksa üçgen dalgalarýn mý oluþturulacaðýný veya hiçbir dalganýn oluþturulup oluþturulmayacaðýný belirtir
	DAC_InitStruct.DAC_OutputBuffer = DAC_OutputBuffer_Enable;		// DAC kanalý çýkýþ arabelleðinin etkin mi yoksa devre dýþý mý olduðunu belirtir

	DAC_Init(DAC_Channel_2, &DAC_InitStruct);						// DAC çevre birimini DAC_InitStruct içinde belirtilen parametrelere göre baþlatýr

	DAC_Cmd(DAC_Channel_2, ENABLE);									// Belirtilen DAC kanalýný etkinleþtirir veya devre dýþý býrakýr
}


int main(void)
{
	GPIO_Config();
	DAC2_Config();

  while (1)
  {
	  for(;i<255;i++)
	  {
		  DAC_SetChannel2Data(DAC_Align_8b_R, i);				// DAC channel2 için belirtilen veri tutma kaydý deðerini ayarlayýn(DAC veri hizalama)
		  delay(100000);
	  }
	  i = 0;
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
