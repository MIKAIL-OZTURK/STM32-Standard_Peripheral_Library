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
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	// AHB1 �evre birimini saatine ge�i� yapmak i�in belirtir


	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;		// Yap�land�r�lacak GPIO pinlerini belirtir
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;												// Se�ilen pinler i�in �al��ma modunu belirtir
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;												// Se�ilen pinler i�in �al��ma ��k�� tipini belirtir
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;											// Se�ilen pinler i�in �al��an Pull-up/Pull-down'� belirtir
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;											// Se�ilen pinler i�in h�z� belirtir

	GPIO_Init(GPIOA, &GPIO_InitStruct);	// GPIOx �evre birimini GPIO_InitStruct i�inde belirtilen parametrelere g�re ba�lat�r.
}


void DAC2_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

	DAC_InitStruct.DAC_Trigger = DAC_Trigger_None;					// Se�ili DAC kanal� i�in harici tetikleyiciyi belirtir
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;	// DAC kanal� g�r�lt� dalgalar�n�n m� yoksa ��gen dalgalar�n m� olu�turulaca��n� veya hi�bir dalgan�n olu�turulup olu�turulmayaca��n� belirtir
	DAC_InitStruct.DAC_OutputBuffer = DAC_OutputBuffer_Enable;		// DAC kanal� ��k�� arabelle�inin etkin mi yoksa devre d��� m� oldu�unu belirtir

	DAC_Init(DAC_Channel_2, &DAC_InitStruct);						// DAC �evre birimini DAC_InitStruct i�inde belirtilen parametrelere g�re ba�lat�r

	DAC_Cmd(DAC_Channel_2, ENABLE);									// Belirtilen DAC kanal�n� etkinle�tirir veya devre d��� b�rak�r
}


int main(void)
{
	GPIO_Config();
	DAC2_Config();

  while (1)
  {
	  for(;i<255;i++)
	  {
		  DAC_SetChannel2Data(DAC_Align_8b_R, i);				// DAC channel2 i�in belirtilen veri tutma kayd� de�erini ayarlay�n(DAC veri hizalama)
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
