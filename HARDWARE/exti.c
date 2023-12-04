#include "exti.h"

int Balance_Pwm,Velocity_Pwm,Turn_Pwm;



void EXTI9_5_IRQHandler(void)
{
 // 首先检查是否是GPIO_PIN_5触发了中断
    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_5) != RESET) 
    {   
          // 清除中断标志
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_5);

        Flag_Stop=0; 
        Get_Angle();   
        
        Balance_Pwm =balance(Angle_Balance,Gyro_Balance);                     //===平衡控制	

        Velocity_Pwm=velocity(Moto1,Moto2);                                   //===速度环PI控制	 速度反馈是正反馈，就是小车快的时候要慢下来就需要再跑快一点    
        Moto1=Balance_Pwm+Velocity_Pwm-Turn_Pwm;                              //===计算左轮电机最终PWM
        Moto2=Balance_Pwm+Velocity_Pwm+Turn_Pwm;                              //===计算右轮电机最终PWM
        Xianfu_Pwm();

            printf("Pitch: %d ,%d \n\r", Moto1,Moto2);
               
        if(Turn_Off(Angle_Balance)==0)                                //===如果不存在异常
        {

            Set_Pwm(Moto1,Moto2); 


            led_on;
        }

        else
	     Set_Pwm(0,0);           
         Get_Zhongzhi();		 
      

   	}       	    
}


