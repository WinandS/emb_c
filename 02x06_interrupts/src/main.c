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
#define EVER            (;;)
#define IMPLEMENTING    (0)

/* Prototypes */
int main(void);

void INTTIM_Config(void);
void GPIO_Config(void);

/* main C entry point */
int main(void)
{
    int i=0;

    // GPIOD INIT
    GPIO_Config();
    // TIMER2 INIT
    INTTIM_Config();

    for EVER
    {
        // regular task processing here
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

    // Fill the GPIO initialization structure
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 |
                                  GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;    //Ouput
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;   //Output type: Push-Pull
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //No pull-up or pull-down
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);


    // When configured, toggle only PIN13 and PIN15, keep PIN12 and 14 as they are
    GPIO_ToggleBits(GPIOD, GPIO_Pin_13 | GPIO_Pin_15);
}

void INTTIM_Config(void)
{
    #if IMPLEMENTING
    //NVIC IRQ Channel init (Channel, priority, enable)
    NVIC_InitTypeDef NVIC_InitStructure;
    //NVIC_InitStructure.NVIC_IRQChannel = ..
    //...
    NVIC_Init(&NVIC_InitStructure);


    // RCC APB1 enable (TIM2ENR)
    
    // Configure TIMER2
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    // TIM period, prescaler, clock div, counter mode
    
    // Enable Interrupt
    TIM_ITConfig( ... )
    
    // Enable counter
    TIM_Cmd( ... )
    #endif /*IMPLEMENTING*/
}

/*Overwrites the weak pointer from startup.s*/
void TIM2_IRQHandler(void)
{
    #if IMPLEMENTING
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    
    // On timer interrupt, we will toggle all pins (PIN12 and PIN13 and PIN14 and PIN15

    #endif /*IMPLEMENTING*/
}

