#ifndef __adc1_h
#define __adc1_h

#include "stm8s.h"
#include "common.h"

void ADC1_Init(void);
void ADC1_Start(u8 channel);
u8 ADC1_GetValue(void);

#endif /* __adc1_h */