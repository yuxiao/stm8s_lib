/**
 * @file:   common.h
 * @brief:  SENHE Plant Wall Project Hardware definition
 * @author: Eric Yu
 * @date:   2012-11-26
 */
/*
2012-11-26 Eric Yu
  初版硬件引脚定义和资源分配
*/

#ifndef __common_h
#define __common_h

#define HW_V1 0
#define HW_V2 1
#define HW_Ver  HW_V2 // 硬件版本

#define WATER_LOW_RESTORE   1   // 水位过低故障后恢复原先运行状态和运行时间

#include "stm8s.h"
#include "iwdg.h"
//#include "spi.h"
#include "beep.h"
#include "tim6.h"
#include "tim5.h"
#include "eeprom.h"
//#include "i2c.h"

//用到的中断在此定义声明
extern @far @interrupt void TIME_BASE_IRQ(void);
extern @far @interrupt void TIM5_UPD_IRQ(void);
//extern @far @interrupt void I2C_Slave_IRQ(void);
//extern @far @interrupt void UART1_TX_IRQ(void);

#define TIM6_UPD_OVF_TRG_IRQHandler     TIME_BASE_IRQ
#define TIM5_UPD_OVF_BRK_TRG_IRQHandler     TIM5_UPD_IRQ
//#define I2C_IRQHandler    I2C_Slave_IRQ
//#define UART1_TX_IRQHandler    UART1_TX_IRQ

#define Bit0      ((u8)0x01)
#define Bit1      ((u8)0x02)
#define Bit2      ((u8)0x04)
#define Bit3      ((u8)0x08)
#define Bit4      ((u8)0x10)
#define Bit5      ((u8)0x20)
#define Bit6      ((u8)0x40)
#define Bit7      ((u8)0x80)

//端口宏定义
//GPIOA
#define WATER_FULL  Bit1      // 高水位输入
#define WATER_LOW   Bit2      // 低水位输入
#define PA3       Bit3        // 引脚悬空
#define WaterLow_In()      (GPIOA->IDR & WATER_LOW)          //低水位开关状态输入
#define WaterFull_In()  (GPIOA->IDR & WATER_FULL)          //水满开关状态输入

//GPIOB
#define LIGHT     Bit7        // 补光灯
#define FAN       Bit6        // 风扇
#define PB5       Bit5        //引脚悬空
#define PB4       Bit4        //引脚悬空
#define FAN_Enable()  GPIOB->ODR |= FAN
#define FAN_Disable()  GPIOB->ODR &= ~FAN
#define LIGHT_Enable()  GPIOB->ODR |= LIGHT
#define LIGHT_Disable()  GPIOB->ODR &= ~LIGHT

// 湿度传感器驱动相关
#define TEMPADIn  Bit3				//温度AD端口PB3(AIN3)
#define HUMIADIn  Bit2				//湿度AD端口PB2(AIN2)
#define A1En      Bit0				//A1使能 接传感器端
#define A2En      Bit1				//A2使能 接固定电阻端
#define MASK      (A1En|A2En)
#define HUMI_PORT   GPIOB->ODR
#define A1_High()   HUMI_PORT |= A1En						//A1置高
#define A1_Low()    HUMI_PORT &= ~A1En						//A1置低
#define A2_High()   HUMI_PORT |= A2En						//A2置高
#define A2_Low()    HUMI_PORT &= ~A2En						//A2置低
#define SE_Disable()  HUMI_PORT &= ~MASK					//Sensor Excitation Disable

#define CH_TEMP  3    //温度测量通道
#define CH_HUMI  2    //湿度测量通道
#define ADC1_TDRL_DEF ((1<<CH_TEMP)|(1<<CH_HUMI))

//GPIOC
#define SEG_PORT  GPIOC->ODR  // PC口

#define SEG_MASK    0xfe  // P7~P1
#define SEG_AllDirIn()   GPIOC->DDR &= ~SEG_MASK  // 段选端口全部置为输入
#define SEG_AllDirOut()   GPIOC->DDR |= SEG_MASK  // 段选端口全部置为输出
#define SEG_DirOut(i)     GPIOC->DDR |= i        // 某一段选端口置为输出
#define SEG_AllRuEn()     GPIOC->CR1 |= SEG_MASK    // 输入上拉电阻使能
#define SEG_In()        (GPIOC->IDR & SEG_MASK)     // 读取输入值
//GPIOE
#define PE5         Bit5        //引脚悬空


//GPIOD
#define KEY_IN      Bit7				// 按键输入
#define COM5        Bit0        // 显示公共端 指示灯
#define COM4        Bit3        // 显示公共端 数码管2个位
#define COM3        Bit5        // 显示公共端 数码管2十位
#define COM2        Bit2				// 显示公共端 数码管1个位
#define COM1        Bit6				// 显示公共端 数码管1十位

#define COM_MASK    (COM1 | COM2 | COM3 | COM4 | COM5)
#define COM_PORT    GPIOD->ODR  // PD口
//#define LED_Enable()  COM_PORT &= ~COM_MASK  //显示使能
#define LED_Disable()  COM_PORT |= COM_MASK  //显示关闭，高电平关闭

#define KEY_In()      (GPIOD->IDR & KEY_IN)          // 按键状态输入
#define KEY_DirIn()   GPIOD->DDR &= ~KEY_IN   // 配置为输入
#define KEY_DirOut()   GPIOD->DDR |= KEY_IN   // 配置为输出
#define KEY_High()    GPIOD->ODR |= KEY_IN    // 输出高电平
#define KEY_Low()    GPIOD->ODR &= ~KEY_IN    // 输出低电平

//GPIOF
#define PUMP      Bit4        // 水泵
#define PUMP_Enable()  GPIOF->ODR |= PUMP
#define PUMP_Disable()  GPIOF->ODR &= ~PUMP


#define FsysMHz      16        //系统时钟MHz

//内部EEPROM掉电存储数据首地址
#define  DATA_SAVE_ADD    0x4000      

// 数字温湿度传感器地址
#define RHI_ADDR    0xA6        //传感器器件地址
#define HumiAddr    0x18        //湿度数据单元地址
#define TempAddr    0x0a        //温度数据单元地址

// 数字湿度传感器值边界定义
#define HUMI_MIN  10    //10%
#define HUMI_MAX  99    //99%

// 温度传感器AD值边界定义
#define TEMP_AD_MIN	(u8)9	 	//-40℃
#define TEMP_AD_MAX	(u8)220	 	//80℃

// 湿度传感器AD值边界定义
#define HUMI_AD_MIN (u8)6  // 开路
#define HUMI_AD_MAX (u8)254 // 短路

void Delay_1us(void);
void Delay_Nus(u16 Cnt);
void Delay_1ms(void);
void Delay_Nms(u16 Cnt);
s8 GetCoilValue(u8 AdValue);//根据AD值获取盘管温度值
s8 GetExhaValue(u8 AdValue);//根据AD值获取排气温度值
u8 GetAverage(u8 *p);//获取数组中6个数的平均值(去掉最值后4平均)
u8 CheckSum(u8 * pBuf, u8 n);
s8 GetTempValue(u8 I2cData);
u8 GetHumiValue(u8 I2cData);
void CLK_Config(void);
void IO_Init(void);

#endif /* __common_h */
