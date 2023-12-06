#include "control.h"

int Balance_Pwm,Velocity_Pwm,Turn_Pwm;

void run(void)
{
        Flag_Stop=0;
        Get_Angle();                                               //===������̬	
               
        Balance_Pwm =balance(Angle_Balance,Gyro_Balance);         //===ƽ�����	
        Velocity_Pwm=velocity(Moto1,Moto2);                       //===�ٶȻ�PI����	 �ٶȷ�����������������С�����ʱ��Ҫ����������Ҫ���ܿ�һ��    
       
    
        Moto1=Balance_Pwm+Velocity_Pwm-Turn_Pwm;                  //===�������ֵ������PWM
        Moto2=Balance_Pwm+Velocity_Pwm+Turn_Pwm;                  //===�������ֵ������PWM
                
        Xianfu_Pwm();
        if(Turn_Off(Angle_Balance)==0)                                //===����������쳣
        {
            Set_Pwm(Moto1,Moto2);                                         //===��ֵ��PWM�Ĵ���  

        }
        else
        Set_Pwm(0,0);           
        Get_Zhongzhi();		 
//            printf("Angle_Balance��%2f\n\r",Angle_Balance);
//            printf("Moto��%d,%d\n\r",Moto1,Moto2);
//            printf("pwm��%d,%d\n\r",Balance_Pwm,Velocity_Pwm);

    OLED_Float(1, 5, Angle_Balance,6);
    OLED_ShowNumber(0, 2, Moto1,4,16);
    OLED_ShowNumber(64, 2, Moto1,4,16);

}






/**************************************************************************
�������ܣ��ٶ�PI���� �޸�ǰ�������ٶȣ�����Target_Velocity
��ڲ����������ٶȡ������ٶ�
����  ֵ���ٶȿ���PWM
��    �ߣ�ƽ��С��֮��
**************************************************************************/
int velocity(int velocity_left,int velocity_right)
{  
      static float Velocity,Encoder_Least,Encoder,Movement;
	  static float Target_Velocity=5000;
	  static float Encoder_Integral;  
    
		if(1==Flag_Qian)    	Movement=Target_Velocity;	           //===ǰ����־λ��1 
		else if(1==Flag_Hou)	Movement=-Target_Velocity;           //===���˱�־λ��1
        else  Movement=0;
    
//	  if(Bi_zhang==1&&Distance<500&&Flag_Left!=1&&Flag_Right!=1)        //���ϱ�־λ��1�ҷ�ң��ת���ʱ�򣬽������ģʽ
//    Movement=-Target_Velocity;
   //=============�ٶ�PI������=======================//	
    
		Encoder_Least=Mean_Filter(velocity_left,velocity_right);          //�ٶ��˲�  
		Encoder *= 0.7;		                                                //===һ�׵�ͨ�˲���       
		Encoder += Encoder_Least*0.3;	                                    //===һ�׵�ͨ�˲���    
		Encoder_Integral +=Encoder;                                       //===���ֳ�λ�� 
		Encoder_Integral +=Movement;                                      //===����ң�������ݣ�����ǰ������
		if(Encoder_Integral>320000)  	Encoder_Integral=320000;            //===�����޷�
		if(Encoder_Integral<-320000)	Encoder_Integral=-320000;              //===�����޷�	
		Velocity=Encoder*Velocity_Kp/100+Encoder_Integral*Velocity_Ki/100;     //===�ٶȿ���	
  	    if(Turn_Off(Angle_Balance)==1)    Encoder_Integral=0;      //===����رպ��������
	  return Velocity;
}

/**************************************************************************
�������ܣ��ٶ��˲�
��ڲ������ٶ�
����  ֵ���˲�����ٶ�
**************************************************************************/
int Mean_Filter(int moto1,int moto2)
{
    u8 i;
    s32 Sum_Speed = 0; 
    s16 Filter_Speed;
    
  static  s16 Speed_Buf[FILTERING_TIMES]={0};
  
  for(i = 1 ; i<FILTERING_TIMES; i++)
  {
    Speed_Buf[i - 1] = Speed_Buf[i];
  }
  Speed_Buf[FILTERING_TIMES - 1] =moto1+moto2;

  for(i = 0 ; i < FILTERING_TIMES; i++)
  {
    Sum_Speed += Speed_Buf[i];
  }
  Filter_Speed = (s16)(Sum_Speed / FILTERING_TIMES);
	return Filter_Speed;
}




/**************************************************************************
�������ܣ���ȡ�Ƕ� 
��ڲ�������ȡ�Ƕȵ��㷨 1��DMP 
����  ֵ����
**************************************************************************/
void Get_Angle(void) 
{
    
        Read_DMP();
        Angle_Balance=-Pitch;             //===����ƽ�����
        Gyro_Balance=gyro[1];             //===����ƽ����ٶ�
        Acceleration_Z=accel[2];         //===����Z����ٶȼ�
//        printf("Pitch: %f ,%f ��%f\n\r", Angle_Balance,Gyro_Balance,Acceleration_Z);

}

/**************************************************************************
�������ܣ�ֱ��PD����
��ڲ������Ƕ�
����  ֵ��ֱ������PWM
��    �ߣ�ƽ��С��֮��
**************************************************************************/
int balance(float Angle ,float Gyro)
{  
     float Bias;    //����DΪ��
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	 int balancel;
	 Bias=Angle;                          //===���ƽ��ĽǶ���ֵ �ͻ�е���
	 balancel=Balance_Kp*Bias+Balance_Kd*Gyro;      //===����ƽ����Ƶĵ��PWM 
	 return balancel;
=======
=======
>>>>>>> parent of 3616136 (pid transplant)
=======
>>>>>>> parent of 3616136 (pid transplant)
	 int balance;
	 Bias=Angle-Zhongzhi;                          //===���ƽ��ĽǶ���ֵ �ͻ�е���
	 balance=Balance_Kp*Bias+Balance_Kd*Gyro;      //===����ƽ����Ƶĵ��PWM 
	 return balance;
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> parent of 3616136 (pid transplant)
=======
>>>>>>> parent of 3616136 (pid transplant)
=======
>>>>>>> parent of 3616136 (pid transplant)
}

/**************************************************************************
�������ܣ�����Ӧ��ֵ
��ڲ�������
����  ֵ����
**************************************************************************/
void  Get_Zhongzhi(void)
{
	    static int  count;
        if(Flag_Stop==0 && Flag_Zhongzhi==0)
		 {
		    if(myabs(Moto1)<100 && myabs(Moto2)<100)  		count++;		//����
				else			                        	count=0;	
				if(count>300)  //����3�봦��ƽ��λ�ã���ȡ��ֵ
				{	
				Zhongzhi=(int)Angle_Balance;	
				Flag_Zhongzhi=1;
				}
		 }
}


/**************************************************************************
�������ܣ��쳣�رյ��
��ڲ�������Ǻ͵�ѹ
����  ֵ��1���쳣  0������
**************************************************************************/
u8 Turn_Off(float angle)
{
    u8 temp;
    if(angle<-40||angle>40||1==Flag_Stop)
        {	                                                 //===��Ǵ���40�ȹرյ��
            temp=1;                                            //===Flag_Stop��1�رյ��
            Moto1=0;
            Moto2=0;		
            EN=0;	
            
            if(angle<-75||angle>75)                            //С��ˤ�� ֹͣ��־λ��1
            Flag_Stop=1;

        }
    else
    {	
        temp=0;
        EN=1;	
    }
    return temp;
}


/**************************************************************************
�������ܣ�����PWM��ֵ 
��ڲ�������
����  ֵ����
**************************************************************************/
void Xianfu_Pwm(void)
{	
        int Amplitude_H=5000, Amplitude_L=-5000;       
        if(Moto1<Amplitude_L)  Moto1=Amplitude_L;	
		if(Moto1>Amplitude_H)  Moto1=Amplitude_H;	
        if(Moto2<Amplitude_L)  Moto2=Amplitude_L;	
		if(Moto2>Amplitude_H)  Moto2=Amplitude_H;	
}

/**************************************************************************
�������ܣ���ֵ��PWM�Ĵ���,�����ж�ת��
��ڲ���������PWM������PWM
����  ֵ����
**************************************************************************/
void Set_Pwm(int moto1,int moto2)
{
      if(moto1>0)		   Right_Direction=1;
			else 	       Right_Direction=0;
	  if(moto2>0)		   Left_Direction=0;
			else 	       Left_Direction=1;
    

	    Final_Moto1=Linear_Conversion(moto1);  //���Ի�
    	Final_Moto2=Linear_Conversion(moto2);
    printf("pwm:%d",moto2);
}

/**************************************************************************
�������ܣ��Կ��������PWM���Ի�,���ڸ�ϵͳ�Ĵ�����ֵ
��ڲ�����PWM
����  ֵ�����Ի����PWM
**************************************************************************/
//float Linear_Conversion(int moto)
//{ 
//	 float temp;
//     float Linear_Moto;
//    
//        temp=36000000.0/(PRESCALER+1)/13000.0*(5000.0/myabs(moto));
//	 if(temp>65535.0) Linear_Moto=65535.0;
//	 else if(temp<0.0) Linear_Moto=0.0;
//	 else Linear_Moto=temp;
//    
//	 return Linear_Moto;
//}	

float Linear_Conversion(int moto)
{ 
    uint16_t Linear_Moto;
    moto = myabs(moto);
    if(moto >65535)
    {
        moto = 65535;
    }
    Linear_Moto = 65535-moto;
   return Linear_Moto;
//	 float temp;
//     float Linear_Moto;
//    
//        temp=36000000.0/(PRESCALER+1)/13000.0*(5000.0/myabs(moto));
//	 if(temp>65535.0) Linear_Moto=65535.0;
//	 else if(temp<0.0) Linear_Moto=0.0;
//	 else Linear_Moto=temp;
//    
//	 return Linear_Moto;
}	
/**************************************************************************
�������ܣ�����ֵ����
��ڲ�����int
����  ֵ��unsigned int
**************************************************************************/
long long myabs(int a)
{ 		   
	  long long temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}

