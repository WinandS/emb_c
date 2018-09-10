TCPREFIX = arm-none-eabi-
CC      = $(TCPREFIX)gcc
AS      = $(TCPREFIX)gcc
LD      = $(TCPREFIX)gcc
CP      = $(TCPREFIX)objcopy
OD      = $(TCPREFIX)objdump
SIZE	= $(TCPREFIX)size
GDBTUI  = $(TCPREFIX)gdb -tui

ASM_FILES := $(wildcard src/*.s)
CXX_FILES := $(wildcard src/*.c)
OBJ_FILES := $(addprefix obj/,$(notdir $(CXX_FILES:.c=.o)))
OBJ_FILES += $(addprefix obj/,$(notdir $(ASM_FILES:.s=.o)))
INC_DIRS := inc
INC_DIRS := $(addprefix -I,$(INC_DIRS))
OUT_FILE := out/main
LD_FILE := stm32.ld

CFLAGS  =  -I. $(INC_DIRS) -O0 -Wall -g
CFLAGS += -fdiagnostics-color
CFLAGS += -mcpu=cortex-m4 -mthumb -mlittle-endian -mthumb-interwork
#CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16 
CFLAGS += -mfloat-abi=soft
# CFLAGS += --specs=nano.specs 			# use newlib-nano instead of newlib => 

# TODO Choose option 1 or 2
CFLAGS += -nostartfiles  				# option 1: Build for a hosted environment target (without -ffreestanding)
# CFLAGS += -ffreestanding -nostartfiles 	# option 2: Build for a baremetal target (requires _sbrk())

# external functions (libraries)
LDFLAGS = 	-lc -lnosys				    # optional; Added by default by compiler
LFLAGS  = $(CFLAGS) -T$(LD_FILE) 
CPFLAGS = -Obinary
ODFLAGS = -S

################################################################
## Colordefinition
################################################################
WHITE_COLOR     = \x1b[37;01m

all: $(OUT_FILE).bin 
#run

clean:
	@echo -e ">>> CLEANING"
	-rm -f main.lst obj/*.o out/*.elf out/*.lst out/*.bin 

$(OUT_FILE).bin: $(OUT_FILE).elf
	@echo -e ">>> COPYING"
	$(CP) $(CPFLAGS) $(OUT_FILE).elf $(OUT_FILE).bin
	$(CP) $(CPFLAGS) $(OUT_FILE).elf -O srec --srec-len 19 $(OUT_FILE).s19
	$(CP) $(CPFLAGS) $(OUT_FILE).elf -O ihex $(OUT_FILE).hex
#the .lst is an assembly listing - just here for educational purposes
	$(OD) $(ODFLAGS) $(OUT_FILE).elf> $(OUT_FILE).lst
	$(SIZE) $(OUT_FILE).elf


$(OUT_FILE).elf: $(OBJ_FILES)
	@echo -e ">>> LINKING"
	$(LD) $(LFLAGS) -o $@ $^ $(LDFLAGS) -Wl,-Map,$(OUT_FILE).map

obj/%.o: src/%.c
	@echo -e ">>> COMPILING [C] $^"
	$(CC) -c $(CFLAGS) $< -o $@

obj/%.o: src/%.s
	@echo -e ">>> COMPILING [ASM] $^"
	$(AS) -c $(CFLAGS) $< -o $@

debug: $(OUT_FILE).elf
	@echo -e ">>> STARTING GDB"
	$(GDBTUI) $^
#	-ex "set remote hardware-breakpoint-limit 6" \ 
#	-ex "set remote hardware-watchpoint-limit 4"  $^

