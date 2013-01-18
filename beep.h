#ifndef __beep_h
#define __beep_h

#include "stm8s.h"

//Ê¹ÄÜ·äÃùÆ÷¹¦ÄÜ
#define BEEP_On()		BEEP->CSR |= BEEP_CSR_BEEPEN
//½ûÖ¹·äÃùÆ÷¹¦ÄÜ
#define BEEP_Off()	BEEP->CSR &= ~BEEP_CSR_BEEPEN


/**************************************
CSR[7:6] :·äÃùÆµÂÊÑ¡Ôñ 
00: Êä³öfLS/(8 x BEEPDIV) kHz  
01: Êä³öfLS/(4 x BEEPDIV) kHz  
1x: Êä³öfLS/(2 x BEEPDIV) kHz 
***************************************/
//·äÃùÆ÷ÆµÂÊÑ¡Ôñ
#define BEEP_4KHz()	BEEP->CSR |= Bit7
#define BEEP_2KHz()	BEEP->CSR |= Bit6;BEEP->CSR &= ~Bit7
#define BEEP_1KHz()	BEEP->CSR &= ~(Bit7|Bit6)

void BEEP_Init(void);
/*
void BEEP_On(void);
void BEEP_Off(void);
*/

#endif /* __beep_h */