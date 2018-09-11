========================================
Instructions for 02x05_fastcode_solution
========================================

+------+
| GOAL |
+------+
Understand difference between soft float and hard float


+--------------------+
| POINTS OF INTEREST |
+--------------------+

# use float in a "heavy" function 
#*  sinf()                             src/main.c
# soft float vs hard float
#*  Hard float                          Makefile
        CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16 -nostdlib
        use specific ABI instructions (during compilation) for the FPU of the STM32F4
        -nostdlib (no need for libC, as we can use the FPU instead)
#*  Soft float                          Makefile
        CFLAGS += -mfloat-abi=soft	             -lc -lnosys
        use generic instructions for float calculations (during compilation)
        These generic instruction require libC (-lc -lnosys) (see module 3)
#*  Link to the external function sinf(): add the math library: -lm
        LDFLAGS = -lm                   Makefile
        Offered to the linker after offering the object files that need the library.
        No need to compile it, as it is already compiled for your toolchain

# Running the code
#**     Compile for soft float
            count number of LED toggles in 10s
        Compile for hard float
            count number of LED toggles in 10s 
