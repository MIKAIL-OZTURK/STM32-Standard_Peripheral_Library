#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#define	BufferLenght	1

uint16_t ADC_Value[BufferLenght];

GPIO_InitTypeDef GPIO_InitStruct;
ADC_InitTypeDef ADC_InitStruct;
ADC_CommonInitTypeDef ADC_CommonStruct;
DMA_InitTypeDef DMA_InitStruct;

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);									// AHB1 çevre birimini saatine geçiþ yapmak için belirtir

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0; 													// Yapýlandýrýlacak GPIO pinlerini belirtir
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;												// Seçilen pinler için çalýþma modunu belirtir
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;											// Seçilen pinler için hýzý belirtir

	GPIO_Init(GPIOD, &GPIO_InitStruct);			// GPIOx çevre birimini GPIO_InitStruct içinde belirtilen parametrelere göre baþlatýr.
}

void ADC_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_CommonStruct.ADC_Mode = ADC_Mode_Independent;						// ADC'yi baðýmsýz veya çoklu modda çalýþacak þekilde yapýlandýrýr. (Independent - Baðýmsýz)
	ADC_CommonStruct.ADC_Prescaler = ADC_Prescaler_Div4;					// ADC'ye göre saatin frekansýný seçin. Saat tüm ADC'ler için ortaktýr.
	ADC_CommonStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;		// Çoklu ADC modu için Doðrudan bellek eriþim modunu yapýlandýrýr.
	ADC_CommonStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;	// 2 örnekleme aþamasý arasýndaki Gecikmeyi yapýlandýrýr.

	ADC_CommonInit(&ADC_CommonStruct);										// ADC çevre birimlerini belirtilen parametrelere göre baþlatýr

	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;						// ADC çözünürlüðü ikili modunu yapýlandýrýr.
	ADC_InitStruct.ADC_ScanConvMode = ENABLE;								// Dönüþtürmenin Tarama (çok kanallý) veya Tek (tek kanal) modunda gerçekleþtirileceðini belirtir.
	ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;// Harici tetik kenarýný seçin ve normal bir grubun tetikleyicisini etkinleþtirin.
	ADC_InitStruct.ADC_ExternalTrigConv = 0;								// Normal bir grubun dönüþümünün baþlangýcýný tetiklemek için kullanýlan harici olayý seçin.
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;						// ADC veri hizalamasýnýn sol mu sað mý olduðunu belirtir
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;							// Dönüþümün Sürekli veya Tek modda gerçekleþtirilip gerçekleþtirilmeyeceðini belirtir
	ADC_InitStruct.ADC_NbrOfConversion = BufferLenght;						// Normal kanal grubu için sýralayýcý kullanýlarak yapýlacak ADC dönüþümlerinin sayýsýný belirtir.

	ADC_Init(ADC1, &ADC_InitStruct);										// ADCx çevre birimini ADC_InitStruct içinde belirtilen parametrelere göre baþlatýr.

	ADC_Cmd(ADC1, ENABLE);													// Belirtilen ADC çevre birimini etkinleþtirir veya devre dýþý býrakýr.

	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_3Cycles);// Seçilen ADC normal kanalý için sýralayýcýdaki karþýlýk gelen sýrasýný ve örnekleme zamanýný yapýlandýrýr.
	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);						 // Son aktarýmdan sonra ADC DMA isteðini etkinleþtirir veya devre dýþý býrakýr (Tek ADC modu)
	ADC_DMACmd(ADC1, ENABLE);												 // Belirtilen ADC DMA isteðini etkinleþtirir veya devre dýþý býrakýr.
}

void DMA_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

	DMA_InitStruct.DMA_Channel = DMA_Channel_0;									// Belirtilen akýþ için kullanýlan kanalý belirtir.
	DMA_InitStruct.DMA_Priority = DMA_Priority_VeryHigh;						// DMAy Streamx için yazýlým önceliðini belirtir.
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;				// DMAy Streamx için çevresel temel adresi belirtir.
	DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t)&ADC_Value;					// DMAy Streamx için bellek 0 temel adresini belirtir. Bu bellek, çift arabellek modu etkinleþtirilmediðinde kullanýlan varsayýlan bellektir.
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralToMemory;						// Verinin bellekten çevre birimine mi, bellekten belleðe mi yoksa çevre biriminden belleðe mi aktarýlacaðýný belirtir.
	DMA_InitStruct.DMA_BufferSize = BufferLenght;								// Belirtilen Kanalýn veri biriminde arabellek boyutunu belirtir. Veri birimi, aktarým yönüne baðlý olarak DMA_PeripheralDataSize veya DMA_MemoryDataSize üyelerinde ayarlanan yapýlandýrmaya eþittir.
	DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Enable;							// Belirtilen Akýþ için FIFO modunun mu yoksa Doðrudan modunun mu kullanýlacaðýný belirtir.
	DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;				// FIFO eþik seviyesini belirtir.
	DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;					// Bellek aktarýmlarý için Burst aktarým yapýlandýrmasýný belirtir. Kesintisiz tek bir iþlemde aktarýlacak veri miktarýný belirtir.
	DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;			// Çevresel aktarýmlar için Burst aktarým yapýlandýrmasýný belirtir. Kesintisiz tek bir iþlemde aktarýlacak veri miktarýný belirtir.
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;								// DMay Streamx'in çalýþma modunu belirtir. ( Circular - Dairesel )
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;			// Bellek veri geniþliðini belirtir.
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	// Çevre birimi veri geniþliðini belirtir.
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;						// Bellek adres kaydýnýn artýrýlýp artýrýlmayacaðýný belirtir.
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;				// Çevre Birimi adres kaydýnýn artýrýlýp artýrýlmayacaðýný belirtir.

	DMA_Init(DMA2_Stream0, &DMA_InitStruct);									// DMAy Streamx'i DMA_InitStruct yapýsýnda belirtilen parametrelere göre baþlatýr.

	DMA_Cmd(DMA2_Stream0, ENABLE);												// Belirtilen DMay Streamx'i etkinleþtirir veya devre dýþý býrakýr.
}

int main(void)
{
	GPIO_Config();
	ADC_Config();
	DMA_Config();

	ADC_SoftwareStartConv(ADC1);												// Seçilen ADC yazýlýmýnýn normal kanallarýn dönüþümünü baþlatmasýný saðlar.

	while (1)
  {

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


