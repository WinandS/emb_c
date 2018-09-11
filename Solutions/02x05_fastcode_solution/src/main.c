/*
 * main.c
 *
 *  Created on: 14 Feb 2013
 *      Author: Maxime Vincent
 * Description: Example of code using divisions
 *
 *     Purpose: Purpose is to compare code execution speed / code size for
 *              soft float vs for hard float
 *
 *     Exercise:    Benchmark Soft vs Hard float + Flash vs RAM execution
 *
 *     Context: Written in the context of the Embedded C course by TASS Belgium.
 */

/* Includes */
#include "main.h"
#include <stdint.h>
#include <math.h>
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

/* Defines */
#define EVER        (;;)

void fast_increment(uint32_t * i);

float calc_float(float in)
{
    volatile float flt_in = in;
    volatile float flt_out;
    uint32_t loop = 100000;
    for (loop; loop > 0; loop--)
    {
        flt_out = sinf(flt_in);
    }
    return 0.0f;
}

/* main C entry point - should never return */
void main(void)
{
    uint32_t i=0;
    uint32_t result;
    float    flt_in, flt_out;

    /* Enable peripheral clocks */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    /* Configure pins */
    GPIOD->MODER &= ~GPIO_MODER_MODER15_1;
    GPIOD->MODER |= GPIO_MODER_MODER15_0;
    /* Speed mode configuration */
    GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR15;
    /* Output mode configuration */
    GPIOD->OTYPER &= ~GPIO_OTYPER_OT_15;
    /* Pull-up Pull down resistor configuration*/
    GPIOD->PUPDR &= ~GPIO_PUPDR_PUPDR15;

    for EVER
    {
        static uint8_t led_val = 0;
        /* toggle the led */
        led_val = !led_val;
        GPIOD->ODR = led_val?0:(GPIO_Pin_15);
        i++;
        //flt_in = (((float)i)/100.0f);
        flt_in = (100.0f);
        flt_out = calc_float(flt_in);
    }
}

__attribute__ ((section (".fastcode"))) 
void fast_increment(uint32_t * i)
{
    (*i)++;
}

