#ifndef __tim5_h
#define __tim5_h

#include "stm8s.h"

//清楚中断标志
#define TIM5_UIF_CLR()  TIM5->SR1 &= ~TIM5_SR1_UIF
#define TIM5_IntEnable()    TIM5->IER |= TIM5_IER_UIE    //Interrupt Enable
#define TIM5_IntDisable()   TIM5->IER &= ~TIM5_IER_UIE   //关定时器中断
#define TIM5_IntStatus()    (TIM5->IER & TIM5_IER_UIE)    //定时器中断状态，用来判断一次显示刷新是否完成

void TIM5_Init(void);


#endif /* __tim5_h */