================================
Where to get these source files?
================================

* uController = STM32F4
** Check ST Microcontrollers website for Reference manual + APIs
    stm32f4xx_gpio.c    # GPIO API                      (or use raw registers)
    stm32f4xx_rcc.c     # Reset and clock control API   (or use raw registers)
    stm32f4xx_tim.c     # Timer API

* Processor = ARM Cortex M4
** Check out CMSIS: an API that exposes features of ARM Cortex M CPUse)
    misc.c              # Miscellaneous tasks for ARM Cortex M CPUs (e.g. NVIC)

=================================
Why did we not need these before?
=================================
* In previous exercices, we were only interested in symbols (in header).
  Now, we will also use the functions, which are implemented in these source files
  
