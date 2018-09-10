/*
 * main.c
 *
 *  Created on: 14 Feb 2013
 *      Author: Maxime Vincent
 * Description: Virtually the most simple demo that can be run on an ARM MCU.
 *
 *     Purpose: Purpose is to demonstrate an openocd-gdb setup to flash and 
 *              step through code on the target.
 *
 *     Context: Written in the context of the Embedded C course by TASS Belgium.
 */

/* Includes */ 
#include "stm32f4xx.h"
#include "main.h"

/* Defines */
#define EVER        (;;)
#define LOOP_TIME_MS    (5)

static uint32_t sys_tick_ms = 0;

void delay(void);
void task1(void);
void task2(void);
void task3(void);
void TIM2_Config(void);


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

        ++sys_tick_ms;
    }
}

/* main C entry point - should never return */
void main(void)
{
    uint32_t endOfLoop=0;

    TIM2_Config();

    for EVER
    {
        /* Set the time in ms at which this loop has to end*/
        endOfLoop = sys_tick_ms + LOOP_TIME_MS;
        task1();
        task2();
        task3();
        /* Wait till sys_tick reaches your endOfLoopValue*/
        /* Will not work for uint32_t overflow*/
        while(sys_tick_ms < endOfLoop);
    }
}

void TIM2_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    /* Enable the TIM2 global Interrupt on the highest available priority: 0*/
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);


    /* Enable the TIM2 clock peripheral*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    // RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    
    /* Time base configuration: TICK every ms */
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    TIM_TimeBaseStructure.TIM_Period = 2000 - 1;      /* 2000 * 1/1000th of a second = 2*/
    TIM_TimeBaseStructure.TIM_Prescaler = 42000 - 1; /* 84 MHz div by 42.000 = 2000*/
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    /* Enable the TIM2 interrupt*/
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

     /* Start the TIM2 counter*/
    TIM_Cmd(TIM2, ENABLE);
}

void task1(void)
{
    delay();
}
void task2(void)
{
    delay();
}
void task3(void)
{
    delay();
}

void delay(void)
{
    uint32_t i = 0;
    while (i < 100000) /* waste some clocks */
    { i++; }
}

