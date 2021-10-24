#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
I2C_InitTypeDef I2C_InitStruct;

uint8_t m_address = 0x4E;
int i = 0;

void delay(uint32_t time)
{
	while(time--);
}

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);		// Buton i�in 	( A0 )
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);		// SDA ve SCL Clock Hatt� ( B6 & B7 )

	// Buton Konfig�rasyon Ayarlar� -->

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA ,&GPIO_InitStruct);

	// SCL - SDA Pinlerinin Konfig�rasyon Ayarlar� -->

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);		// SCL Pin | SCL --> Hatta aktar�lan verilerin senkronizasyonu, SCL hatt� taraf�ndan ger�ekle�tirilir.
																// 					 SCL hatt�nda master cihaz taraf�ndan �retilen saat sinyali bulunur.
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);		// SDA Pin | SDA --> Cihazlar aras�ndaki veri aktar�m�n�n sa�land��� hatt�r.

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOB ,&GPIO_InitStruct);
}

void I2C_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);					// I2C Clock Hatt�

	I2C_InitStruct.I2C_Ack = ENABLE;										// ACK (Acknowledge) - Onay biti
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;	// ACK'n�n ka� bit olaca��n� ayarlad�k
	I2C_InitStruct.I2C_ClockSpeed = 400000;									// Saat frekans�n� belirtir. Bu parametre 400kHz'den daha d���k bir de�ere ayarlanmal�d�r.
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;							// I2C h�zl� mod g�rev d�ng�s�n� belirtir.
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;									// I2C modunu belirtir.
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;									// �lk cihaz�n kendi adresini belirtir.

	I2C_Init(I2C1, &I2C_InitStruct);

	I2C_Cmd(I2C1, ENABLE);
}

void I2C_Write(uint8_t address, uint8_t data)		// I2C �zerinde mesaj g�nderme i�lemleri -->
{
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));	// Belirtilen I2C bayra��n�n ayarlan�p ayarlanmad���n� kontrol eder.

	I2C_GenerateSTART(I2C1, ENABLE);				// I2Cx ileti�imi BA�LAT ko�ulu olu�turur.

	while(!(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))); 		// Master modun se�ilip se�ilmedi�ini kontrol eder.

	I2C_Send7bitAddress(I2C1, address, I2C_Direction_Transmitter);		// Slave cihaz� se�mek i�in adres bayt�n� iletir.

	while(!(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))); 	// Master cihaz�n mesaj g�ndermek i�in haz�r olup olmad���n� kontrol eder.

	I2C_SendData(I2C1, data);						// I2Cx �evre birimi arac�l���yla bir veri bayt� g�nderir.

	I2C_GenerateSTOP(I2C1, ENABLE);					// I2Cx ileti�im STOP ko�ulu olu�turur.
}

int main(void)
{
	GPIO_Config();
	I2C_Config();

  while (1)
  {
	  if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))			// Belirtilen giri� ba�lant� noktas�(A0) pinini okur.
	  {
		  while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
				  i++;
		  delay(1680000);
	  }

	  switch(i)
	  {
	  case 0:
		  I2C_Write(m_address, 0x00);
		  break;
	  case 1:
		  I2C_Write(m_address, 0x01);
		  break;
	  case 2:
		  I2C_Write(m_address, 0x02);
		  break;
	  case 3:
		  I2C_Write(m_address, 0x04);
		  break;
	  case 4:
		  I2C_Write(m_address, 0x08);
		  break;
	  case 5:
		  I2C_Write(m_address, 0x10);
		  break;
	  case 6:
		  I2C_Write(m_address, 0x20);
		  break;
	  case 7:
		  I2C_Write(m_address, 0x40);
		  break;
	  case 8:
		  I2C_Write(m_address, 0x80);
		  break;
	  default:
		  i = 0;
		  break;
	  }
  }
}


void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size)
{
  /* TODO, implement your code here */
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void)
{
  /* TODO, implement your code here */
  return -1;
}
