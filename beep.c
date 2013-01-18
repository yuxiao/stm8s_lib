#include "beep.h"

//直接由LSI 128KHz作为时钟源，未校准。
void BEEP_Init(void)
{
	CLK->PCKENR2 |= CLK_PCKENR2_AWU;	//设置时钟源(比较特别)
	BEEP->CSR = BEEP_CSR_RESET_VALUE;
	BEEP->CSR = 0x0f;								//BeepDiv=16
	BEEP->CSR |= BEEP_CSR_BEEPSEL;	//0xC0选择4kHz
	//BEEP->CSR |= 0x40;							//0x40选择2kHz
	//BEEP->CSR |= 0x00;							//0x00选择1kHz
	//BEEP-> CSR = 0x98;//DIV  f=2.6KHz
}

/*
void BEEP_On(void)
{
	BEEP->CSR |= BEEP_CSR_BEEPEN;		//使能蜂鸣器功能
}

void BEEP_Off(void)
{
	BEEP->CSR &= ~BEEP_CSR_BEEPEN;	//禁止蜂鸣器功能	
}
*/