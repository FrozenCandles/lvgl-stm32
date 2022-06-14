/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   触摸画板实验
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-指南者 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
 
#include "stm32f10x.h"
#include "./usart/bsp_usart.h"	
#include "./lcd/bsp_ili9341_lcd.h"
#include "./lcd/bsp_xpt2046_lcd.h"
#include "./flash/bsp_spi_flash.h"
#include "./led/bsp_led.h" 

#include <string.h>

#include "lvgl.h"
#include "lv_ex_conf.h"
#include "lvgl_app/lv_study.h"

void setup(void);

void TIM_Setup(void);







int main(void)
{		
    setup();
    TIM_Setup();
    LED_RED;
    lv_init();
	
    lv_port_disp_init();
    lv_port_indev_init();
    //lv_demo_widgets();
    //lv_demo_keypad_encoder();

    while ( 1 )
    {

        lv_task_handler();
    }
		
}

#define            BASIC_TIM                   TIM6
#define            BASIC_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            BASIC_TIM_CLK               RCC_APB1Periph_TIM6
#define            BASIC_TIM_Period            1000-1
#define            BASIC_TIM_Prescaler         71
#define            BASIC_TIM_IRQ               TIM6_IRQn
#define            BASIC_TIM_IRQHandler        TIM6_IRQHandler
void TIM_Setup(void) {
printf("TIM setup begin\n");
NVIC_InitTypeDef NVIC_InitStructure; 
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIM_IRQ ;	
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);
NVIC_Init(&NVIC_InitStructure);

	
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    BASIC_TIM_APBxClock_FUN(BASIC_TIM_CLK, ENABLE);
    TIM_TimeBaseStructure.TIM_Period = BASIC_TIM_Period;	
    TIM_TimeBaseStructure.TIM_Prescaler= BASIC_TIM_Prescaler;
    //TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    //TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
    //TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
    TIM_TimeBaseInit(BASIC_TIM, &TIM_TimeBaseStructure);
    TIM_ClearFlag(BASIC_TIM, TIM_FLAG_Update);
    TIM_ITConfig(BASIC_TIM,TIM_IT_Update,ENABLE);
    TIM_Cmd(BASIC_TIM, ENABLE);	
}

void setup(void) {

	//LCD 初始化
	ILI9341_Init();  

	//触摸屏初始化
	XPT2046_Init();

	/* USART config */
	USART_Config();  
	LED_GPIO_Config();

	//其中0、3、5、6 模式适合从左至右显示文字，
	//不推荐使用其它模式显示文字	其它模式显示文字会有镜像效果			
	//其中 6 模式为大部分液晶例程的默认显示方向  
     ILI9341_GramScan ( 3 );	




}

/* ------------------------------------------end of file---------------------------------------- */

