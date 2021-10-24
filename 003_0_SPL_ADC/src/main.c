#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
ADC_InitTypeDef  ADC_InitStruct;
ADC_CommonInitTypeDef ADC_CommonInitStruct;

uint16_t adc_value;
float adc_voltage;

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	// AHB1 çevre birimini saatine geçiþ yapmak için belirtir

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;													// Yapýlandýrýlacak GPIO pinlerini belirtir
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;												// Seçilen pinler için çalýþma modunu belirtir
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;												// Seçilen pinler için çalýþma çýkýþ tipini belirtir
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;											// Seçilen pinler için çalýþan Pull-up/Pull-down'ý belirtir
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;											// Seçilen pinler için hýzý belirtir

	GPIO_Init(GPIOA, &GPIO_InitStruct);	// GPIOx çevre birimini GPIO_InitStruct içinde belirtilen parametrelere göre baþlatýr.
}

void ADC_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);	// APB2 çevre birimini saatine geçiþ yapmak için belirtir

	ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;	// ADC'yi baðýmsýz veya çoklu modda çalýþacak þekilde yapýlandýrýr. (Independent - Baðýmsýz)
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4;// ADC'ye göre saatin frekansýný seçin. Saat tüm ADC'ler için ortaktýr.

	ADC_CommonInit(&ADC_CommonInitStruct);					// ADC çevre birimlerini belirtilen parametrelere göre baþlatýr

	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;		// ADC çözünürlüðü ikili modunu yapýlandýrýr.

	ADC_Init(ADC1, &ADC_InitStruct);						// ADCx çevre birimini ADC_InitStruct içinde belirtilen parametrelere göre baþlatýr.

	ADC_Cmd(ADC1, ENABLE);									// Belirtilen ADC çevre birimini etkinleþtirir veya devre dýþý býrakýr.
}

uint16_t Read_ADC()
{
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_56Cycles); // Seçilen ADC düzenli kanalý için sýralayýcýdaki karþýlýk gelen sýrasýný ve örnekleme süresini yapýlandýrýr.

	ADC_SoftwareStartConv(ADC1);			// Seçilen ADC yazýlýmýnýn normal kanallarýn dönüþümünü baþlatmasýný saðlar.

	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);	// Belirtilen ADC bayraðýnýn ayarlanýp ayarlanmadýðýný kontrol eder.

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
