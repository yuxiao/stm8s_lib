#include "adc1.h"

//通道4,5，4MHz的时钟源，一次转换14个时钟周期，3.5us
void ADC1_Init(void)
{
	CLK->PCKENR2 |= CLK_PCKENR2_ADC;	//ADC Clock Enable
	ADC1->TDRL |= ADC1_TDRL_DEF;	//禁用对应AD通道的施密特触发器
	ADC1->CR2 &= ~ADC1_CR2_ALIGN;				//结果左对齐，可只读取高八位
	ADC1->CR1 |= (0x20 | ADC1_CR1_ADON);	//时钟4分频并开启ADC1电源
  //此时默认会开启通道0(PB0)，若PB0配置为输出，则可能输出无效，直到切换通道
	ADC1->CSR = CH_TEMP;								//选择任一通道，防止PB0接输出时出故障
}

void ADC1_Start(u8 channel)
{
	ADC1->CSR = channel;								//选择通道
	ADC1->CR1 |= ADC1_CR1_ADON;				//启动ADC1开始转换
}

u8 ADC1_GetValue(void)
{
	u8 data;
	while(!(ADC1->CSR & ADC1_CSR_EOC));//等待转换结束   14个时钟周期
	ADC1->CSR &= ~ADC1_CSR_EOC;				//结束标志位清零
	data = ADC1->DRH;
	return data;
}
