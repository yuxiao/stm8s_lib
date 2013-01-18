#ifndef __eeprom_h
#define __eeprom_h

#include "stm8s.h"

#if defined (STM8S105)
  #define BLOCK_SIZE 128
#else
  #define BLOCK_SIZE 64
#endif

#define EEPROM_EOP() (FLASH->IAPSR & FLASH_IAPSR_EOP)	//校验操作是否完成

void EEPROM_Unlock(void);

void EEPROM_Lock(void);

void EEPROM_ProgramByte(u32 Add, u8 Dat);

void EEPROM_ProgramWord(u32 Add, u32 *p_Dat);
void EEPROM_ProgramBlock(u32 Add, u8 *p_Dat);
u8 EEPROM_ReadByte(u32 Add);
void ROP_Enable(void);

#endif /* __eeprom_h */