/*
 * main.c
 *
 *  Created on: 14 Feb 2013
 *      Author: Maxime Vincent
 * Description: Virtually the most simple demo that can be run on an ARM MCU.
 *              The target is barely running - all clocks are off, the core is
 *              just executing a few simple instructions.
 *
 *     Purpose: Purpose is to demonstrate an openocd-gdb setup to flash and 
 *              step through code on the target.
 *
 *     Context: Written in the context of the Embedded C course by TASS Belgium.
 */

/* Includes */
#include "main.h"
#include <stdint.h>

/* Defines */
#define EVER        (;;)

struct Object_t {
    uint32_t index;
    uint8_t  data[8];
};

void fast_increment(uint32_t * i);
void copyObject(struct Object_t objectByValue);


/* main C entry point - should never return */
void main(void)
{
    uint32_t i=0;
    uint32_t result;
    struct Object_t object = {1, {1,2,3,4,5,6,7,8}};

    for EVER
    {
        i++;
        fast_increment(&i);
        copyObject(object);
    }
}

__attribute__ ((section (".fastcode"))) 
void fast_increment(uint32_t * i)
{
    (*i)++;
}

void copyObject(struct Object_t objectByValue)
{
    (void) objectByValue;
}