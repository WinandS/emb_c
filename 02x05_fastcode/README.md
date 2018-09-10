Instructions for 02x05_fastcode
===============================


### GOAL
Understand location of code (`.text` section vs `.fastcode` section)


### POINTS OF INTEREST
| Subject                                                   | Location             | Documentation|
| ----------------------------------------------------------|----------------------|--------------| 
|** .fastcode section**                                     |                      |              |
|- defined in <br> `__attribute__ ((section (".fastcode")))`| src/main.c           |              |
|- located in Flash AND RAM in <br> `RAM AT > FLASH` <br> RAM     = VMA (virtual memory address) <br> FLASH   = LMO (load memory address)                                   |  stm32.ld            |              |
|- copied from Flash to RAM in <br> `copy_fastcode()`       | src/low_level_init.c |              |
|- Compilation output visible in <br> `> objdump --syms obj/main.o` |    obj/main.o|              |
|- Linking output visible in <br> `> arm-none-eabi-readelf --section-headers` <br> Note: linker decides where to put sections| out/main.elf |      |



### Running the code
```bash
> arm-none-eabi-gdb out/main.elf
> layout asm
> b main.c:33
> stepi         # step through the assembly instructions
# notice the veneer when entering fast_increment():
# A veneer is inserted by the linker because we jump beyond the max branch range 
```