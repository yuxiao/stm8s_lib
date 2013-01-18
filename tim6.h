#ifndef __tim6_h
#define __tim6_h

#include "stm8s.h"

//清楚中断标志
#define TIM6_UIF_CLR()	TIM6->SR1 &= ~TIM6_SR1_UIF

void TIM6_Init(void);


#endif /* __tim6_h */