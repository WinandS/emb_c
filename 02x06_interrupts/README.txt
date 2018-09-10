=================================
Instructions for 02x06_interrupts
=================================

+------+
| GOAL |
+------+
1. Use reference manuals to find the right APIs
2. Start a timer
3. Configure an interrupt

+--------------------+
| POINTS OF INTEREST |
+--------------------+

# Configure the timer 2 and install an interrupt handler
#*  INTTIM_Config()                     src/main.c
#**     Enable the NVIC                 src/misc.c + research: ARM Cortex M4 Interrupts (book or internet)

#**     Enable Timer2                   src/stm32f4xx_rcc.c + research: STM32F4 enable peripherals (reference manual)

#**     Configure Timer2                src/stm32f4xx_tim.c + research: STM32F4 TIMER2 (internet for a general timer + reference manual)

#**     Enable interrupt for Timer2     src/stm32f4xx_tim.c + research: ARM Cortex M4 Interrupt flags (book or internet)

#**     Start Timer2                    src/stm32f4xx_tim.c

#*  TIM2_IRQHandler()                   src/main.c
#**     Implement interrupt handle      src/stm32f4xx_tim.c + research: ARM Cortex M4 Interrupt flags (book or internet)
