/*
 * main.c
 *
 *  Created on: 14 Feb 2013
 *      Author: Maxime Vincent
 * Description: Example of code executed from RAM
 *              functions part of the fastcode section will be copied to RAM
 *              at run-time, to (potentially) speed up code execution.
 *
 *     Purpose: Purpose is to compare code executed from FLASH vs RAM.
 *              
 *     Exercise:    Benchmark the different floating point instructions.
 *
 *     Context: Written in the context of the Embedded C course by TASS Belgium.
 */

/* Includes */
#include "main.h"
#include <stdint.h>

/* Defines */
#define EVER        (;;)

void fast_increment(uint32_t * i);

/* main C entry point - should never return */
void main(void)
{
    uint32_t i=0;
    uint32_t result;

    for EVER
    {
        i++;
        fast_increment(&i);
    }
}

__attribute__ ((section (".fastcode"))) 
void fast_increment(uint32_t * i)
{
    (*i)++;
}

