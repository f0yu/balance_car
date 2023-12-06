#ifndef __CONTROL_H
#define __CONTROL_H

#include "main.h"
#include "gpio.h"
#include "tim.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"

#define FILTERING_TIMES  10


extern	int Balance_Pwm,Velocity_Pwm,Turn_Pwm;



void run(void);
int balance(float Angle ,float Gyro);
int velocity(int velocity_left,int velocity_right);
void Set_Pwm(int moto1,int moto2);
//void Key(void);
void Xianfu_Pwm(void);
u8 Turn_Off(float angle);
void Get_Angle(void) ;

int Put_Down(float Angle,int encoder_left,int encoder_right);
void speed_filter(void);
int Mean_Filter(int moto1,int moto2);
float Linear_Conversion(int moto);
void  Get_Zhongzhi(void);
long long myabs(int a);




#endif



