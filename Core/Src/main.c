/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************

  *
  * MPU6050 scl PB7
            SDA PB6
            INT PB5
            
    OLED    SCL PB8
            SDA PB9
    
    
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "oled.h"
#include "mpuiic.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"



#include "control.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


u8 Flag_Stop=1,Flag_Show=0;                 //ֹͣ��־λ�� ��ʾ��־λ Ĭ��ֹͣ ��ʾ��
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD

float Balance_Kp=10000,Balance_Kd=0,Velocity_Kp=0,Velocity_Ki=0;//PID����
=======
float Balance_Kp=200,Balance_Kd=0,Velocity_Kp=70,Velocity_Ki=0.7;//PID����
>>>>>>> parent of 3616136 (pid transplant)
=======
float Balance_Kp=200,Balance_Kd=0,Velocity_Kp=70,Velocity_Ki=0.7;//PID����
>>>>>>> parent of 3616136 (pid transplant)
=======
float Balance_Kp=200,Balance_Kd=0,Velocity_Kp=70,Velocity_Ki=0.7;//PID����
>>>>>>> parent of 3616136 (pid transplant)

int Moto1,Moto2,Final_Moto1,Final_Moto2;    //���PWM���� Ӧ��Motor�� ��Moto�¾�	
int Zhongzhi,Flag_Zhongzhi=0;
float Roll,Pitch,Yaw,Angle_Balance,Gyro_Balance;      //ƽ�����
float Acceleration_Z;                       //Z����ٶȼ�  

u8 Flag_Qian,Flag_Hou,Flag_Left,Flag_Right,Flag_sudu=1; //����ң����صı���

u8 state=0;

    uint8_t     uart1RxBuffer[128];
    uint8_t     MPU_dataReady = 0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
//    float pitch, roll, yaw; // Euler angles

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */


  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();

  MX_USART1_UART_Init();
  OLED_Init();
  OLED_Clear();
  MX_TIM4_Init();
    

       OLED_ShowNumber(0, 3, state,2,16);
 
  /* USER CODE BEGIN 2 */


        

    printf("Blance_Car\r\n");
//    OLED_ShowString(0,0,"Blance_Car",16);
//    OLED_ShowString(0,2,"pitch",16);
//    OLED_ShowString(0,4,"roll",16);
//    OLED_ShowString(0,6,"yaw",16);
   
    
    MPU_Init();
    state=1;
    if(mpu_dmp_init() == 0) //�������ֵΪ0����ʾMPU6050��������
    {
       OLED_ShowString(0,6,"MPU6050_Success!",8);


    }
    else //�������ֵ��Ϊ0����ʾMPU6050����
    {
        //ִ���쳣����

   OLED_ShowString(0,6,"MPU6050_Fail!",8);

    }
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
    
    HAL_Delay(2000);
    MX_TIM3_Init();
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn); // �����ض����ж�
=======
=======
>>>>>>> parent of 3616136 (pid transplant)
=======
>>>>>>> parent of 3616136 (pid transplant)
//    
//    HAL_Delay(3000);
//    MX_TIM3_Init();
  
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> parent of 3616136 (pid transplant)
=======
>>>>>>> parent of 3616136 (pid transplant)
=======
>>>>>>> parent of 3616136 (pid transplant)



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */


//    run();


      
    /* USER CODE BEGIN 3 */ 
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
