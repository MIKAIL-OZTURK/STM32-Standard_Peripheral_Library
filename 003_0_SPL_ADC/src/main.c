#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
ADC_InitTypeDef  ADC_InitStruct;
ADC_CommonInitTypeDef ADC_CommonInitStruct;

uint16_t adc_value;
float adc_voltage;

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	// AHB1 �evre birimini saatine ge�i� yapmak i�in belirtir

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;													// Yap�land�r�lacak GPIO pinlerini belirtir
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;												// Se�ilen pinler i�in �al��ma modunu belirtir
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;												// Se�ilen pinler i�in �al��ma ��k�� tipini belirtir
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;											// Se�ilen pinler i�in �al��an Pull-up/Pull-down'� belirtir
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;											// Se�ilen pinler i�in h�z� belirtir

	GPIO_Init(GPIOA, &GPIO_InitStruct);	// GPIOx �evre birimini GPIO_InitStruct i�inde belirtilen parametrelere g�re ba�lat�r.
}

void ADC_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);	// APB2 �evre birimini saatine ge�i� yapmak i�in belirtir

	ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;	// ADC'yi ba��ms�z veya �oklu modda �al��acak �ekilde yap�land�r�r. (Independent - Ba��ms�z)
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4;// ADC'ye g�re saatin frekans�n� se�in. Saat t�m ADC'ler i�in ortakt�r.

	ADC_CommonInit(&ADC_CommonInitStruct);					// ADC �evre birimlerini belirtilen parametrelere g�re ba�lat�r

	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;		// ADC ��z�n�rl��� ikili modunu yap�land�r�r.

	ADC_Init(ADC1, &ADC_InitStruct);						// ADCx �evre birimini ADC_InitStruct i�inde belirtilen parametrelere g�re ba�lat�r.

	ADC_Cmd(ADC1, ENABLE);									// Belirtilen ADC �evre birimini etkinle�tirir veya devre d��� b�rak�r.
}

uint16_t Read_ADC()
{
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_56Cycles); // Se�ilen ADC d�zenli kanal� i�in s�ralay�c�daki kar��l�k gelen s�ras�n� ve �rnekleme s�resini yap�land�r�r.

	ADC_SoftwareStartConv(ADC1);			// Se�ilen ADC yaz�l�m�n�n normal kanallar�n d�n���m�n� ba�latmas�n� sa�lar.

	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);	// Belirtilen ADC bayra��n�n ayarlan�p ayarlanmad���n� kontrol eder.

	return ADC_GetConversionValue(ADC1);	// Returns the last ADCx conversion result data for regular channel.
}

int main(void)
{
	GPIO_Config();
	ADC_Config();

  while (1)
  {
	  adc_value = Read_ADC();
	  adc_voltage = (0.000805) * adc_value;
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
