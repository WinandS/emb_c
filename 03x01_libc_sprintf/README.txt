===================================
Instructions for 03x01_libc_sprintf
===================================

+------+
| GOAL |
+------+
1. Understand linker:
        local functions
        external functions (libraries)
        binary size
        automatic code optimization         


+--------------------+
| POINTS OF INTEREST |
+--------------------+


#* -lc -lnosys are optional                                 Makefile
#* -ffreestanding                                           Makefile
      full libc will be added to binary       
        See code size                                       
         > arm-non-eabi-size main.elf 
        See MAP                                             out/main.map
#* without -ffreestanding                                   Makefile
      code optimized instead of using libc...       
        See code size                                       
         > arm-non-eabi-size main.elf 
        See assembly for sprintf()                          main.lst or GDB 
#* When debugging
       step in a libc function
         No source files available, as we included the library (without debug info), not the source files  
