#include "spi.h"

//配置成只发送主模式，接收引脚可以作为普通IO口使用
void SPI_Init(void)
{
	CLK->PCKENR1 |= CLK_PCKENR1_SPI;	//SPI Clock Enable
	SPI->CR1 = SPI_CR1_RESET_VALUE;
	SPI->CR2 = SPI_CR2_RESET_VALUE;
	//SPI->CR1 |= SPI_CR1_BR & 0x00;		//波特率为Fmaster的2分频
	//SPI->CR1 |= (SPI_CR1_BR & 0x08);		//波特率为Fmaster的4分频
	SPI->CR1 |= (SPI_CR1_BR & 0x20);		//波特率为Fmaster的32分频 500K
	//SPI->CR1 |= (SPI_CR1_BR & 0x30);		//波特率为Fmaster的128分频 125K
	//SPI->CR1 |= (SPI_CR1_BR & 0x38);		//波特率为Fmaster的256分频 62.5K
	SPI->CR1 |= SPI_CR1_MSTR;					//配置为主设备
	//SPI->CR1 |= SPI_CR1_CPOL;					//Clock Polarity
	//SPI->CR1 |= SPI_CR1_CPHA;					//Clock Phase
  //SPI->CR1 |= SPI_CR1_LSBFIRST;     //先发送低位
  SPI->CR2 |= SPI_CR2_SSM;					//软件从设备管理，代替NSS管脚输入控制
	SPI->CR2 |= SPI_CR2_SSI;					//内部选择为主模式
	
	SPI->CR1 |= SPI_CR1_SPE;					//SPI Enable 
}

u8 SPI_SendByte(u8 Data)
{
	/* Write in the DR register the data to be sent*/
  SPI->DR = Data; 
  /* 等待数据传输完成 */
  while(!(SPI->SR & SPI_SR_RXNE));
  /* 读DR寄存器，清除RXNE标志 */
  return (SPI->DR); 
}