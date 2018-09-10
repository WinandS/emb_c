================================
Where to get these header files?
================================

* uController = STM32F4
** Check ST Microcontrollers website for Reference manual + APIs
    stm32f4xx.h         # Main entry: wrapper for registers + Vector Table
    system_stm32f4xx.h

* Processor = ARM Cortex M4
** Check out CMSIS: an API that exposes features of ARM Cortex M CPUs
    core_cm4.h          # Main entry for an ARM Cortex M4
    core_cm4_simd.h     # M4 can use SIMD instructions (google it)
    core_cmFunc.h       # Generic getters/setters for CPU internal registers
    core_cmInstr.h      # Generic tasks for ARM Cortex M CPUs (e.g. power mode)
