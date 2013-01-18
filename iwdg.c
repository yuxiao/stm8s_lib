#include "iwdg.h"

//配置成20ms超时复位，对LSI/2先64分频，再设置RL[7:0]=20
void IWDG_Init(void)
{
	IWDG->KR = KEY_ACCESS;		//解除写保护
	//IWDG->PR = 4;							//64分频，每步1ms
	IWDG->PR = 6;							//256分频，每步4ms
	//IWDG->RLR = 20;						//重装载寄存器，20ms
	IWDG->RLR = 255;						//重装载寄存器，1.02s
	IWDG->KR = KEY_REFRESH;		//恢复写保护
	IWDG->KR = KEY_ENABLE;		//启动看门狗
}

/*
void IWDG_Refresh(void)
{
	IWDG->KR = KEY_REFRESH;		//刷新计数值
}
*/