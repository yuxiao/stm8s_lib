#include "i2c.h"
#include "sys_ctrl.h"

//I2C配置MCU为标准模式（总线速率100KHz）
void I2C_Init(void)
{
	CLK->PCKENR1 |= CLK_PCKENR1_I2C;	//I2C clock Enable
	I2C->FREQR = FsysMHz;							//外设时钟频率 FsysMHz
	/* 内部时钟分频配置 */
	I2C->CR1 &= ~I2C_CR1_PE;					//disable I2C	to config TRISE
	I2C->TRISER = FsysMHz + 1;			//最大上升时间设置1000ns
	I2C->CCRL = (u8)(FsysMHz*5);			//由FsysMHz*5算得CCR
	I2C->CCRH = (u8)(FsysMHz>>8);
	I2C->CCRH &= ~I2C_CCRH_FS;				//选择为标准模式100KHz
	I2C->CR1 |= I2C_CR1_PE;					//Enable I2C
	I2C->CR2 |= I2C_CR2_ACK;				//应答使能
	I2C->CR2 &= ~I2C_CR2_POS;				//应答当前字节
	I2C->OARL =	WSD_ADD;								//从地址设置，7位从地址
	I2C->OARH |= I2C_OARH_ADDCONF;	//地址模式配置，必须配置成1 
  I2C->ITR |= (I2C_ITR_ITEVTEN | I2C_ITR_ITBUFEN);//开启事件中断和缓存中断
}

//I2C从机中断
@far @interrupt void I2C_Slave_IRQ(void)
{
  static u8 DataReceived;
  u8 Event = I2C->SR1;
  
  if (Event & I2C_SR1_ADDR)//EV1从地址匹配成功
  {
    if (I2C->SR3 & I2C_SR3_TRA)    //读SR3清除EV1,如果进入从发送模式
    {
      switch (DataReceived)
      {
        case HumiAddr:
          I2C->DR = I2CHumiValue;
          break;
        case TempAddr:
          I2C->DR = I2CTempValue;
          break;
        default:
          I2C->DR = 0;
          break;
      }
    }
  }
  else if (Event & I2C_SR1_RXNE)//EV2接收到数据
  {
    DataReceived = I2C->DR; //读取数据，同时清除EV2
  }
  else if (Event & I2C_SR1_STOPF)//EV4接收到停止位
  {
    I2C->CR2 = I2C->CR2;    //写CR2寄存器，清除EV4
  }
  else if (Event & I2C_SR1_TXE)//EV3数据发送完成并接收到应答
  {
    I2C->DR = 0; //继续发送数据，同时清除EV3，数据为0
  }
}

/* end of file */
