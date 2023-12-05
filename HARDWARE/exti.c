#include "exti.h"

int Balance_Pwm,Velocity_Pwm,Turn_Pwm;



int EXTI9_5_IRQHandler(void)
{
 // 首先检查是否是GPIO_PIN_5触发了中断
    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_5) != RESET) 
    {   
          // 清除中断标志
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_5);
        
        
        HAL_GPIO_WritePin(bsq_led_GPIO_Port, bsq_led_Pin, GPIO_PIN_RESET);

       Flag_Stop=0;
        
        Balance_Pwm =balance(Angle_Balance,Gyro_Balance);                     //===平衡控制	
//        Velocity_Pwm=velocity(Moto1,Moto2);                                   //===速度环PI控制	 速度反馈是正反馈，就是小车快的时候要慢下来就需要再跑快一点    
      
//        Moto1=Balance_Pwm+Velocity_Pwm-Turn_Pwm;                              //===计算左轮电机最终PWM
//        Moto2=Balance_Pwm+Velocity_Pwm+Turn_Pwm;                              //===计算右轮电机最终PWM
       Moto1=Balance_Pwm;
        Moto2=Balance_Pwm;
        if(Turn_Off(Angle_Balance)==0)                                //===如果不存在异常
         MotorControl(Moto1,Moto2); 

        else
        MotorControl(0,0);  
        Get_Zhongzhi();

   	}     
//        printf("%d, %d \n\r",Balance_Pwm,Velocity_Pwm);    

//    printf("data:%d,%d,%f\n\r",Moto1,Moto2,Angle_Balance,Gyro_Balance);    
//     printf("data:%d,%fd\n\r",Angle_Balance,Gyro_Balance);    
     return 0;	  
}


