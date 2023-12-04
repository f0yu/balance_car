//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : Evk123
//  生成日期   : 2014-0101
//  最近修改   : 
//  功能描述   : 0.69寸OLED 接口演示例程(STM32F103ZE系列IIC)
//              说明: 
//              ----------------------------------------------------------------
//              GND   电源地
//              VCC   接5V或3.3v电源
//              SCL   接PD6（SCL）
//              SDA   接PD7（SDA）            
//              ----------------------------------------------------------------
//Copyright(C) 中景园电子2014/3/16
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////
#ifndef __OLED_H
#define __OLED_H			  	 

#include "main.h"


#include "stm32f1xx_hal.h"
#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED IIC端口定义----------------  					   
#define OLED_SCL_GPIO_PORT                  GPIOB
#define OLED_SCL_GPIO_PIN                   GPIO_PIN_8
#define OLED_SCL_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)  

#define OLED_SDA_GPIO_PORT                  GPIOB
#define OLED_SDA_GPIO_PIN                   GPIO_PIN_9
#define OLED_SDA_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   

#define OLED_SCLK_Clr() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_RESET)//SCL
#define OLED_SCLK_Set() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_SET)

#define OLED_SDIN_Clr() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_RESET)//SDA
#define OLED_SDIN_Set() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_SET)

 		     
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  
typedef const int16_t sc16;  
typedef const int8_t sc8;  

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;  
typedef __I int16_t vsc16; 
typedef __I int8_t vsc8;   

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  
typedef const uint16_t uc16;  
typedef const uint8_t uc8; 

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;  
typedef __I uint16_t vuc16; 
typedef __I uint8_t vuc8;  																    
	 
//OLED控制用函数
void OLED_WR_Byte(unsigned dat,unsigned cmd);  
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_ShowNumber(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void fill_picture(unsigned char fill_Data);
void Picture(void);
void OLED_IIC_Start(void);
void OLED_IIC_Stop(void);
void OLED_Write_IIC_Command(unsigned char IIC_Command);
void OLED_Write_IIC_Data(unsigned char IIC_Data);
void OLED_Write_IIC_Byte(unsigned char IIC_Byte);
void OLED_IIC_Wait_Ack(void);

void OLED_fuhao_write(unsigned char x,unsigned char y,unsigned char asc);
void OLED_Num_write(unsigned char x,unsigned char y,unsigned char asc) ;
void OLED_Float(unsigned char Y,unsigned char X,double real,unsigned char N);
void OLED_Float2(unsigned char Y,unsigned char X,double real,unsigned char N1,unsigned char N2);
void OLED_Num2(unsigned char x,unsigned char y, int number);
void OLED_Num3(unsigned char x,unsigned char y,int number); 
void OLED_Num4(unsigned char x,unsigned char y, int number);
void OLED_Num5(unsigned char x,unsigned char y,unsigned int number);


void OLED_ShowFloat(u8 x, u8 y, float num, u8 len, u8 size2, u8 decimalPlaces) ;


#endif  
