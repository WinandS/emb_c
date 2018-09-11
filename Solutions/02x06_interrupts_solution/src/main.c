/*
 * main.c
 *
 *  Created on: 14 Feb 2013
 *      Author: Maxime Vincent
 * Description: A guideline to implement a timer and link an interrupt to it
 *
 *     Purpose: Get familiar with using APIs and documentation
 *              Offer hints to indicate the order of execution
 *
 *     Exercise:    Use the TIMER2 interrupt handler to toggle 4 LEDs
 *
 *     Context: Written in the context of the Embedded C course by TASS Belgium.
 */

/* Includes */ 
#include "stm32f4xx.h"
#include "main.h"

/* Defines */
#define EVER        (;;)

/* Prototypes */
int main(void);

void GPIO_Config(void);
void INTTIM_Config(void);


/* main C entry point */
int main(void)
{
    int i=0;

    // GPIOD config
    GPIO_Config();
    // TIMER2 config
    INTTIM_Config();

    for EVER
    {
        // regular task processing
        i++;
    }
}

void GPIO_Config(void)
{
    /* RCC clock config */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    
    /*-------------------------- GPIO Configuration ----------------------------*/
    /* GPIOD Configuration: Pins 12, 13, 14 and 15 in output push-pull          */
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 |
                                  GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    // When configured, toggle only PIN13 and PIN15, keep PIN12 and 14 as they are
    GPIO_ToggleBits(GPIOD, GPIO_Pin_13 | GPIO_Pin_15);
}


void INTTIM_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    
    NVIC_InitTypeDef NVIC_InitStructure;
    /* Enable the TIM2 global Interrupt on the highest available priority: 0*/
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
     
    /* Enable the TIM2 clock peripheral*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    // RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // Direct register access would also enable TIM2
    
    /* Time base configuration: Toggle on 1Hz */
    TIM_TimeBaseStructure.TIM_Period = 2000 - 1; 
    TIM_TimeBaseStructure.TIM_Prescaler = 42000 - 1; /* 84 MHz div by 42.000 */
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    
    /* Enable the TIM2 interrupt*/
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    
    /* Start the TIM2 counter*/
    TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(void)
{
    /* In case we enabled more than just the 'TIM_IT_Update'-interrupt, 
       we should first figure out what triggered this interrupt*/
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        /* Clear pending interrupt flags, in case other (non-TIM_IT_Update) 
        interrupts would fire causing us to again handle the same*/
        // Note: during the ISR, the same ISR can not be called
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
    }
}