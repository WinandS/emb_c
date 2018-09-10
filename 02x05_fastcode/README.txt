===============================
Instructions for 02x05_fastcode
===============================

+------+
| GOAL |
+------+
Understand location of code (.text section vs .fastcode section)


+--------------------+
| POINTS OF INTEREST |
+--------------------+

# .fastcode section:
#*  defined in                                  src/main.c
        __attribute__ ((section (".fastcode")))
#*  located in Flash AND RAM in                 stm32.ld
        RAM AT > FLASH   
            RAM     = VMA (virtual memory address)
            FLASH   = LMO (load memory address)
#*  copied from Flash to RAM in                 src/low_level_init.c
        copy_fastcode()
#*  Compilation output visible in               obj/main.o
#**     > objdump --syms obj/main.o
#*  Linking output visible in                   out/main.elf
#**     > arm-none-eabi-readelf --section-headers out/main.elf
        Note: linker decides where to put sections   


# Running the code
#**     > arm-none-eabi-gdb out/main.elf
        > layout asm
        > b main.c:33
        > stepi         # step through the assembly instructions
        notice the veneer when entering fast_increment():
        A veneer is inserted by the linker because we jump beyond the max branch range 
