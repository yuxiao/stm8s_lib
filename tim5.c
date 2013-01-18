#include "tim5.h"
#include "common.h"

//定时更新中断模式 
void TIM5_Init(void)
{
  CLK->PCKENR1 |= CLK_PCKENR1_TIM5;    // Timer5 clock enable
  TIM5->PSCR |= 0x04;                  // 16分频，1MHZ = 1uS
  TIM5->CR1 |= TIM5_CR1_ARPE;          // Auto-Reload Preload Enable
  TIM5->ARRH = 0;                  
  //TIM5->ARRL = 0x64;                // 100us=0x0064
  TIM5->ARRL = 250;                  // 250us
  TIM5->IER |= TIM5_IER_UIE;          // Update Interrupt Enable
  TIM5->CR1 |= TIM5_CR1_CEN;          // Counter Enable
}

