/*
 * main.c
 *
 *  Created on: 14 Feb 2013
 *      Author: Maxime Vincent
 * Description: Use external functions, provided by libc 
 *
 *     Purpose: Compare the impact of linking with/without libc on binary size
 *
 *     Context: Written in the context of the Embedded C course by TASS Belgium.
 */

/* Includes */
#include "main.h"
#include <stdint.h>
// STDIO Requires libc!
#include <stdio.h>

/* Defines */
#define EVER        (;;)

// const uint8_t const_test[10] = {0,1,2,3,4,5,6,7,8,9};

uint8_t test[100];
static uint8_t bss_test[100];

/* main C entry point - should never return */
int main(void)
{
    uint32_t i=0;

    sprintf((char*)&test, "Welcome to Embedded C\n");

    for EVER
    {
        i++;
    }
}

