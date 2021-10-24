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
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);									// AHB1 �evre birimini saatine ge�i� yapmak i�in belirtir

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0; 													// Yap�land�r�lacak GPIO pinlerini belirtir
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;												// Se�ilen pinler i�in �al��ma modunu belirtir
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;											// Se�ilen pinler i�in h�z� belirtir

	GPIO_Init(GPIOD, &GPIO_InitStruct);			// GPIOx �evre birimini GPIO_InitStruct i�inde belirtilen parametrelere g�re ba�lat�r.
}

void ADC_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_CommonStruct.ADC_Mode = ADC_Mode_Independent;						// ADC'yi ba��ms�z veya �oklu modda �al��acak �ekilde yap�land�r�r. (Independent - Ba��ms�z)
	ADC_CommonStruct.ADC_Prescaler = ADC_Prescaler_Div4;					// ADC'ye g�re saatin frekans�n� se�in. Saat t�m ADC'ler i�in ortakt�r.
	ADC_CommonStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;		// �oklu ADC modu i�in Do�rudan bellek eri�im modunu yap�land�r�r.
	ADC_CommonStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;	// 2 �rnekleme a�amas� aras�ndaki Gecikmeyi yap�land�r�r.

	ADC_CommonInit(&ADC_CommonStruct);										// ADC �evre birimlerini belirtilen parametrelere g�re ba�lat�r

	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;						// ADC ��z�n�rl��� ikili modunu yap�land�r�r.
	ADC_InitStruct.ADC_ScanConvMode = ENABLE;								// D�n��t�rmenin Tarama (�ok kanall�) veya Tek (tek kanal) modunda ger�ekle�tirilece�ini belirtir.
	ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;// Harici tetik kenar�n� se�in ve normal bir grubun tetikleyicisini etkinle�tirin.
	ADC_InitStruct.ADC_ExternalTrigConv = 0;								// Normal bir grubun d�n���m�n�n ba�lang�c�n� tetiklemek i�in kullan�lan harici olay� se�in.
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;						// ADC veri hizalamas�n�n sol mu sa� m� oldu�unu belirtir
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;							// D�n���m�n S�rekli veya Tek modda ger�ekle�tirilip ger�ekle�tirilmeyece�ini belirtir
	ADC_InitStruct.ADC_NbrOfConversion = BufferLenght;						// Normal kanal grubu i�in s�ralay�c� kullan�larak yap�lacak ADC d�n���mlerinin say�s�n� belirtir.

	ADC_Init(ADC1, &ADC_InitStruct);										// ADCx �evre birimini ADC_InitStruct i�inde belirtilen parametrelere g�re ba�lat�r.

	ADC_Cmd(ADC1, ENABLE);													// Belirtilen ADC �evre birimini etkinle�tirir veya devre d��� b�rak�r.

	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_3Cycles);// Se�ilen ADC normal kanal� i�in s�ralay�c�daki kar��l�k gelen s�ras�n� ve �rnekleme zaman�n� yap�land�r�r.
	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);						 // Son aktar�mdan sonra ADC DMA iste�ini etkinle�tirir veya devre d��� b�rak�r (Tek ADC modu)
	ADC_DMACmd(ADC1, ENABLE);												 // Belirtilen ADC DMA iste�ini etkinle�tirir veya devre d��� b�rak�r.
}

void DMA_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

	DMA_InitStruct.DMA_Channel = DMA_Channel_0;									// Belirtilen ak�� i�in kullan�lan kanal� belirtir.
	DMA_InitStruct.DMA_Priority = DMA_Priority_VeryHigh;						// DMAy Streamx i�in yaz�l�m �nceli�ini belirtir.
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;				// DMAy Streamx i�in �evresel temel adresi belirtir.
	DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t)&ADC_Value;					// DMAy Streamx i�in bellek 0 temel adresini belirtir. Bu bellek, �ift arabellek modu etkinle�tirilmedi�inde kullan�lan varsay�lan bellektir.
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralToMemory;						// Verinin bellekten �evre birimine mi, bellekten belle�e mi yoksa �evre biriminden belle�e mi aktar�laca��n� belirtir.
	DMA_InitStruct.DMA_BufferSize = BufferLenght;								// Belirtilen Kanal�n veri biriminde arabellek boyutunu belirtir. Veri birimi, aktar�m y�n�ne ba�l� olarak DMA_PeripheralDataSize veya DMA_MemoryDataSize �yelerinde ayarlanan yap�land�rmaya e�ittir.
	DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Enable;							// Belirtilen Ak�� i�in FIFO modunun mu yoksa Do�rudan modunun mu kullan�laca��n� belirtir.
	DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;				// FIFO e�ik seviyesini belirtir.
	DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;					// Bellek aktar�mlar� i�in Burst aktar�m yap�land�rmas�n� belirtir. Kesintisiz tek bir i�lemde aktar�lacak veri miktar�n� belirtir.
	DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;			// �evresel aktar�mlar i�in Burst aktar�m yap�land�rmas�n� belirtir. Kesintisiz tek bir i�lemde aktar�lacak veri miktar�n� belirtir.
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;								// DMay Streamx'in �al��ma modunu belirtir. ( Circular - Dairesel )
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;			// Bellek veri geni�li�ini belirtir.
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	// �evre birimi veri geni�li�ini belirtir.
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;						// Bellek adres kayd�n�n art�r�l�p art�r�lmayaca��n� belirtir.
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;				// �evre Birimi adres kayd�n�n art�r�l�p art�r�lmayaca��n� belirtir.

	DMA_Init(DMA2_Stream0, &DMA_InitStruct);									// DMAy Streamx'i DMA_InitStruct yap�s�nda belirtilen parametrelere g�re ba�lat�r.

	DMA_Cmd(DMA2_Stream0, ENABLE);												// Belirtilen DMay Streamx'i etkinle�tirir veya devre d��� b�rak�r.
}

int main(void)
{
	GPIO_Config();
	ADC_Config();
	DMA_Config();

	ADC_SoftwareStartConv(ADC1);												// Se�ilen ADC yaz�l�m�n�n normal kanallar�n d�n���m�n� ba�latmas�n� sa�lar.

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


