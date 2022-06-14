/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   测试lcd
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-霸道 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx.h"
#include "./usart/bsp_debug_usart.h"	
#include "./lcd/bsp_ili9341_lcd.h"
#include "./lcd/bsp_xpt2046_lcd.h"
#include "./flash/bsp_spi_flash.h"
#include "./led/bsp_led.h" 
//#include "palette.h"
#include <string.h>

#include "lvgl/lvgl.h"
#include "lv_study.h"

void lv_example(void);

void setup(void);
 
int main(void)
{
    setup();
    
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();

	while ( 1 )
	{
        lv_task_handler();
	}
		
}



#define BASIC_TIMx_PRESCALER           71 
#define BASIC_TIMx_PERIOD              1000 
#define BASIC_TIMx                     TIM6
#define BASIC_TIM_RCC_CLK_ENABLE()     __HAL_RCC_TIM6_CLK_ENABLE()
#define BASIC_TIM_RCC_CLK_DISABLE()    __HAL_RCC_TIM6_CLK_DISABLE()
#define BASIC_TIM_IRQ                  TIM6_IRQn
#define BASIC_TIM_INT_FUN              TIM6_IRQHandler
TIM_HandleTypeDef htimx;
void setup(void) {
    /* 系统时钟初始化成72 MHz */
    SystemClock_Config();
    /* LED 端口初始化 */
    LED_GPIO_Config();	 
    /* 初始化串口 */
    DEBUG_USART_Config();

    ILI9341_Init ();             //LCD 初始化
    XPT2046_Init();
    ILI9341_GramScan ( 3 );	
    
    
    
    TIM_MasterConfigTypeDef sMasterConfig;
    
    htimx.Instance = BASIC_TIMx;
    htimx.Init.Prescaler = BASIC_TIMx_PRESCALER;
    htimx.Init.CounterMode = TIM_COUNTERMODE_UP;
    htimx.Init.Period = BASIC_TIMx_PERIOD;
    HAL_TIM_Base_Init(&htimx);
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&htimx, &sMasterConfig);
    BASIC_TIM_RCC_CLK_ENABLE();
    HAL_NVIC_SetPriority(BASIC_TIM_IRQ, 1, 0);
    HAL_NVIC_EnableIRQ(BASIC_TIM_IRQ);
    HAL_TIM_Base_Start_IT(&htimx);

}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 72000000
  *            HCLK(Hz)                       = 72000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            HSE PREDIV1                    = 2
  *            PLLMUL                         = 9
  *            Flash Latency(WS)              = 0
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef clkinitstruct = {0};
  RCC_OscInitTypeDef oscinitstruct = {0};
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  oscinitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE;
  oscinitstruct.HSEState        = RCC_HSE_ON;
  oscinitstruct.HSEPredivValue  = RCC_HSE_PREDIV_DIV1;
  oscinitstruct.PLL.PLLState    = RCC_PLL_ON;
  oscinitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE;
  oscinitstruct.PLL.PLLMUL      = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&oscinitstruct)!= HAL_OK)
  {
    /* Initialization Error */
    while(1); 
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
  clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2)!= HAL_OK)
  {
    /* Initialization Error */
    while(1); 
  }
}

//static void btn_event_cb(lv_event_t * e)
//{
//    lv_event_code_t code = lv_event_get_code(e);
//    lv_obj_t * btn = lv_event_get_target(e);
//    if(code == LV_EVENT_CLICKED) {
//        static uint8_t cnt = 0;
//        cnt++;

//        /*Get the first child of the button which is the label and change its text*/
//        lv_obj_t * label = lv_obj_get_child(btn, 0);
//        lv_label_set_text_fmt(label, "Button: %d", cnt);
//    }
//}

//void lv_example(void)
//{
//    lv_obj_t * btn = lv_btn_create(lv_scr_act());     /*Add a button the current screen*/
//    lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
//    lv_obj_set_size(btn, 120, 50);                          /*Set its size*/
//    lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
//    lv_label_set_text(label, "Button");                     /*Set the labels text*/
//    lv_obj_center(label);
//    lv_obj_t * btn = lv_btn_create(lv_scr_act());     /*Add a button the current screen*/
//    lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
//    lv_obj_set_size(btn, 120, 50);                          /*Set its size*/
//    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

//    lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
//    lv_label_set_text(label, "Button");                     /*Set the labels text*/
//    lv_obj_center(label);


//}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
