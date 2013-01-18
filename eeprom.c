#include "eeprom.h"

void EEPROM_Unlock(void)
{
	if(!(FLASH->IAPSR & FLASH_IAPSR_DUL))
	{
		FLASH->DUKR = 0xAE;
		FLASH->DUKR = 0x56;
	}    
}

void EEPROM_Lock(void)
{
	if(FLASH->IAPSR & FLASH_IAPSR_DUL)
	{
		FLASH->IAPSR &= ~FLASH_IAPSR_DUL;
	}    
}

void EEPROM_ProgramByte(u32 Add, u8 Dat)
{
	*((PointerAttr u8*) Add) = Dat;
}

u8 EEPROM_ReadByte(u32 Add)
{
	return *((PointerAttr u8*) Add);
}

void EEPROM_ProgramWord(u32 Add, u32 *p_Dat)
{
	/* Enable Word Write Once */
	FLASH->CR2 |= FLASH_CR2_WPRG;
	FLASH->NCR2 &= (u8)(~FLASH_NCR2_NWPRG);
	
	/* Write 4 byte - from lowest address*/
	*((PointerAttr u8*) Add)      = *((u8*)p_Dat);		
	*(((PointerAttr u8*) Add) + 1)= *((u8*)p_Dat + 1);	
	*(((PointerAttr u8*) Add) + 2)= *((u8*)p_Dat + 2);
	*(((PointerAttr u8*) Add) + 3)= *((u8*)p_Dat + 3);
}

#pragma section (CODE_IN_RAM)

void EEPROM_ProgramBlock(u32 Add, u8 *p_Dat)
{
  u8 Count;
	/* Enable Block Write Once */
	FLASH->CR2 |= FLASH_CR2_PRG;
	FLASH->NCR2 &= (u8)(~FLASH_NCR2_NPRG);
  
  /* Copy data bytes from RAM to FLASH memory */
  for (Count = 0; Count < BLOCK_SIZE; Count++)
  {
    *((PointerAttr u8*)Add + Count) = (*(p_Dat + Count));
  }
}

#pragma section ()

/**
 * @brief:  使能读保护(在main的最开始调用)
 * @param:  
 * @retval: 
 */
void ROP_Enable(void)
{
  /* 判断ROP是否为0xAA，若不是则写入 */
  if (OPT->OPT0 != 0xAA)
  {
    EEPROM_Unlock();
    
    /* Enable Option Bytes Write Once */
    FLASH->CR2 |= FLASH_CR2_OPT;
    FLASH->NCR2 &= (u8)(~FLASH_NCR2_NOPT);
    
    /* ROP write */
    OPT->OPT0 = 0xAA;
    while (EEPROM_EOP() == 0);
    
    EEPROM_Lock();
  }
}

/*
u8 EEPROM_EOP(void)
{
	return FLASH->IAPSR & FLASH_IAPSR_EOP;
}
*/