#ifndef __iwdg_h
#define __iwdg_h

#include "stm8s.h"

#define	KEY_ENABLE	0xcc
#define KEY_REFRESH	0xaa
#define KEY_ACCESS	0x55

#define IWDG_Refresh()	IWDG->KR = KEY_REFRESH	//刷新计数值

void IWDG_Init(void);


#endif /* __iwdg_h */