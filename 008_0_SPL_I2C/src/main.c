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
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);		// Buton için 	( A0 )
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);		// SDA ve SCL Clock Hattý ( B6 & B7 )

	// Buton Konfigürasyon Ayarlarý -->

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA ,&GPIO_InitStruct);

	// SCL - SDA Pinlerinin Konfigürasyon Ayarlarý -->

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);		// SCL Pin | SCL --> Hatta aktarýlan verilerin senkronizasyonu, SCL hattý tarafýndan gerçekleþtirilir.
																// 					 SCL hattýnda master cihaz tarafýndan üretilen saat sinyali bulunur.
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);		// SDA Pin | SDA --> Cihazlar arasýndaki veri aktarýmýnýn saðlandýðý hattýr.

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOB ,&GPIO_InitStruct);
}

void I2C_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);					// I2C Clock Hattý

	I2C_InitStruct.I2C_Ack = ENABLE;										// ACK (Acknowledge) - Onay biti
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;	// ACK'nýn kaç bit olacaðýný ayarladýk
	I2C_InitStruct.I2C_ClockSpeed = 400000;									// Saat frekansýný belirtir. Bu parametre 400kHz'den daha düþük bir deðere ayarlanmalýdýr.
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;							// I2C hýzlý mod görev döngüsünü belirtir.
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;									// I2C modunu belirtir.
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;									// Ýlk cihazýn kendi adresini belirtir.

	I2C_Init(I2C1, &I2C_InitStruct);

	I2C_Cmd(I2C1, ENABLE);
}

void I2C_Write(uint8_t address, uint8_t data)		// I2C üzerinde mesaj gönderme iþlemleri -->
{
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));	// Belirtilen I2C bayraðýnýn ayarlanýp ayarlanmadýðýný kontrol eder.

	I2C_GenerateSTART(I2C1, ENABLE);				// I2Cx iletiþimi BAÞLAT koþulu oluþturur.

	while(!(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))); 		// Master modun seçilip seçilmediðini kontrol eder.

	I2C_Send7bitAddress(I2C1, address, I2C_Direction_Transmitter);		// Slave cihazý seçmek için adres baytýný iletir.

	while(!(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))); 	// Master cihazýn mesaj göndermek için hazýr olup olmadýðýný kontrol eder.

	I2C_SendData(I2C1, data);						// I2Cx çevre birimi aracýlýðýyla bir veri baytý gönderir.

	I2C_GenerateSTOP(I2C1, ENABLE);					// I2Cx iletiþim STOP koþulu oluþturur.
}

int main(void)
{
	GPIO_Config();
	I2C_Config();

  while (1)
  {
	  if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))			// Belirtilen giriþ baðlantý noktasý(A0) pinini okur.
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
