#include "common.h"

//软件延时(16M系统时钟前提下，加上函数调用时间大约1us)
void Delay_1us(void)
{
	nop();
}

void Delay_Nus(u16 Cnt)
{
  while (Cnt--)
  {
    Delay_1us();
  }  
}

//软件延时(16M系统时钟前提下，大约1ms)
void Delay_1ms(void)
{
	u16 i = 1167;
	while (i--);
}

void Delay_Nms(u16 Cnt)
{
  while (Cnt--)
  {
    Delay_1ms();
  }  
}

//计算数据指针前n个数的校验和 (n < 256)
u8 CheckSum(u8 * pBuf, u8 n)
{
  u8 Sum = 0;
  
  while(n--)
  {
    Sum += *(pBuf++);
  }
  return ((Sum ^ 0xff) + 1);
}

//获取数组中6个数的平均值(去掉最值后4平均)
u8 GetAverage(u8 *p)
{
  u8 i = 6;
  u8 dat;
  u8 Max = 0;
  u8 Min = 255;
  u16 Sum = 0;
  
  while (i--)
  {
    dat = *(p+i);
    if (dat > Max)
    {
      Max = dat;
    }
    if (dat < Min)
    {
      Min = dat;
    }
    Sum += dat;
  }
  Sum -= Min;   //去掉最小值
  Sum -= Max;   //去掉最大值
  Sum /= 4;     //取平均值
  return (u8)Sum;
}

void CLK_Config(void)
{
  /* 时钟配置 */
  CLK->ICKR = CLK_ICKR_HSIEN;  //内部高速时钟使能
  CLK->CKDIVR = 0;            //内部时钟16MHz，CPU时钟无分频
  //CLK->CKDIVR = 0x10;            //内部时钟4MHz，CPU时钟无分频
  CLK->PCKENR1 = 0;            //禁止外设时钟
  CLK->PCKENR2 = 0;            //禁止外设时钟
  
  //CLK->ICKR |= CLK_ICKR_LSIEN;  //LSI使能(不需要，当LSI被指定为主时钟源/CCO时钟源/AWU/IWDG的时钟源时，该位不能被清除)
}

void IO_Init(void)
{
  /* 全局配置寄存器 */
  //CFG->GCR |= CFG_GCR_SWD;  //禁用SWIM引脚(PD1)
  
  /* 端口配置，空脚输出开漏低电平，增强抗干扰性能 */
  GPIOA->ODR = 0;        // 输出低电平
  GPIOA->DDR = PA3;        //空脚输出
  GPIOA->CR1 = 0;                //空脚输出开漏
  //GPIOA->CR2 = 0;
  
  GPIOB->ODR = 0;  // 输出低电平
  GPIOB->DDR = FAN| LIGHT |A1En|A2En|PB5|PB4;  //I2C脚输出
  GPIOB->CR1 = FAN| LIGHT |A1En|A2En;          //输出推挽
  //GPIOB->CR2 = 0;
  
  GPIOC->ODR = SEG_MASK;      //输出为高电平
  GPIOC->DDR = SEG_MASK;      //输出
  GPIOC->CR1 = SEG_MASK;          //输出推挽
  //GPIOC->CR2 = 0;
  //GPIOC->CR2 |= Bit6 | Bit5;  //SPI接口快速摆率
  
  GPIOD->ODR = COM_MASK;              //输出为高电平
  GPIOD->DDR = COM_MASK;              //输出，其余的输入
  GPIOD->CR1 = COM_MASK;          //输出推挽，其余的输入悬浮
  //GPIOD->CR2 = 0;
  
  GPIOE->ODR = 0;              //输出为低电平
  GPIOE->DDR = PE5;              //输出
  GPIOE->CR1 = 0;                //输出开漏
  //GPIOE->CR2 = 0;
  
  GPIOF->ODR = 0;              //输出为低电平
  GPIOF->DDR = PUMP;              //输出
  GPIOF->CR1 = PUMP;                //输出推挽
  //GPIOF->CR2 = 0;
}

/* end of file */