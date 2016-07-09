# Hey Emacs, this is a -*- makefile -*-
#----------------------------------------------------------------------------
# 
# General Atmel AVR  Makefile template.
#
# author: Peter Malmberg <peter.malmberg@gmail.com>
#  
#----------------------------------------------------------------------------
# On command line:
#
# make all = Make software.
#
# make clean = Clean out built project files.
#
# make coff = Convert ELF to AVR COFF.
#
# make extcoff = Convert ELF to AVR Extended COFF.
#
# make program = Download the hex file to the device, using avrdude.
#                Please customize the avrdude settings below first!
#
# make debug = Start either simulavr or avarice as specified for debugging, 
#              with avr-gdb or avr-insight as the front end for debugging.
#
# make filename.s = Just compile filename.c into the assembler code only.
#
# make filename.i = Create a preprocessed source file for use in submitting
#                   bug reports to the GCC project.
#
# To rebuild project do "make clean" then "make all".
#----------------------------------------------------------------------------


# Output format. (can be srec, ihex, binary)
FORMAT = ihex

# Target file name (without extension).
TARGET = main

# List C source files here. (C dependencies are automatically generated.)
SRC = src/$(TARGET).c \
      FreeRTOS/Source/croutine.c \
      FreeRTOS/Source/queue.c \
      FreeRTOS/Source/event_groups.c \
      FreeRTOS/Source/tasks.c \
      FreeRTOS/Source/list.c   \
      FreeRTOS/Source/timers.c \
      FreeRTOS/Source/portable/GCC/ATMega323/port.c \
      FreeRTOS/Source/portable/MemMang/heap_1.c

# List C++ source files here. (C dependencies are automatically generated.)
CPPSRC = 

# List Assembler source files here.
#     Make them always end in a capital .S.  
ASRC =

# Include directories
INCLUDE = inc \
          src \
          FreeRTOS/Source/include \
          FreeRTOS/Source/portable/GCC/ATMega323
LIB  = 

# Object files directory
#     To put object files in current directory, use a dot (.), do NOT make
#     this an empty or blank macro!
OBJDIR = .

# Output directory
OUTDIR = output

# Optimization level, can be [0, 1, 2, 3, s]. 
#     0 = turn off optimization. s = optimize for size.
OPT = s



# Compiler flag to set the C Standard level.
# [ gnu99 gnu11 c++98 c++03 c++11 c++14 ] 
CSTANDARD = -std=gnu99

<<<<<<< HEAD:examples/avr-FreeRTOS/Makefile
# Place -D or -U options here for C sources
CDEFS = -DF_CPU=$(F_CPU)UL


# Place -D or -U options here for ASM sources
ADEFS = -DF_CPU=$(F_CPU)


# Place -D or -U options here for C++ sources
CPPDEFS = -DF_CPU=$(F_CPU)UL
#CPPDEFS += -D__STDC_LIMIT_MACROS
#CPPDEFS += -D__STDC_CONSTANT_MACROS
=======
# C Macro definitions
CDEFS = 

# ASM  Macro definitions
ADEFS = 

# C++ Macro definitions
CPPDEFS = 
>>>>>>> 0844b056bed6e7009073b24369858df323002f8b:examples/avr/Makefile



#---------------- Compiler Options C ----------------
#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC manual
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -adhlns...: create assembler listing
CFLAGS = -g$(DEBUG)
CFLAGS += $(patsubst %,-D%,$(CDEFS))
CFLAGS += -O$(OPT)
CFLAGS += -funsigned-char
CFLAGS += -funsigned-bitfields
CFLAGS += -fpack-struct
CFLAGS += -fshort-enums
CFLAGS += -Wall
CFLAGS += -Wstrict-prototypes
#CFLAGS += -mshort-calls
#CFLAGS += -fno-unit-at-a-time
#CFLAGS += -Wundef
CFLAGS += -Wunreachable-code
#CFLAGS += -Wsign-compare
#CFLAGS += -Wa,-adhlns=$(<:%.c=$(OBJDIR)/%.lst)
CFLAGS += $(patsubst %,-I%,$(INCLUDE))
CFLAGS += $(CSTANDARD)



#---------------- Compiler Options C++ ----------------
#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC manual and avr-libc documentation
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -adhlns...: create assembler listing
CPPFLAGS = -g$(DEBUG)
CPPFLAGS += $(patsubst %,-D%,$(CPPDEFS))
CPPFLAGS += -O$(OPT)
CPPFLAGS += -funsigned-char
CPPFLAGS += -funsigned-bitfields
CPPFLAGS += -fpack-struct
CPPFLAGS += -fshort-enums
CPPFLAGS += -fno-exceptions
CPPFLAGS += -Wall
CPPFLAGS += -Wundef
#CPPFLAGS += -mshort-calls
#CPPFLAGS += -fno-unit-at-a-time
#CPPFLAGS += -Wstrict-prototypes
#CPPFLAGS += -Wunreachable-code
#CPPFLAGS += -Wsign-compare
CPPFLAGS += -Wa,-adhlns=$(<:%.cpp=$(OBJDIR)/%.lst)
CPPFLAGS += $(patsubst %,-I%,$(INCLUDE))
#CPPFLAGS += $(CSTANDARD)


#---------------- Assembler Options ----------------
#  -Wa,...:   tell GCC to pass this to the assembler.
#  -adhlns:   create listing
#  -gstabs:   have the assembler create line number information; note that
#             for use in COFF files, additional information about filenames
#             and function names needs to be present in the assembler source
#             files -- see avr-libc docs [FIXME: not yet described there]
#  -listing-cont-lines: Sets the maximum number of continuation lines of hex 
#       dump that will be displayed for a given single line of source input.
ASFLAGS =  $(patsubst %,-D%,$(ASDEFS))
ASFLAGS += -Wa,-adhlns=$(<:%.S=$(OBJDIR)/%.lst),-gstabs,--listing-cont-lines=100

<<<<<<< HEAD:examples/avr-FreeRTOS/Makefile
=======
# Linker Options ------------------------------------------------------------
#  -Wl,...:     tell GCC to pass this to linker.
#    -Map:      create map file
#    --cref:    add cross reference to  map file
LDFLAGS = -Wl,-Map=$(OUTDIR)/$(TARGET).map,--cref
LDFLAGS += $(EXTMEMOPTS)
LDFLAGS += $(patsubst %,-L%,$(INCLUDE))

#
# Platform specific options
#============================================================================

# Linux options -------------------------------------------------------------
ifeq ($(TARGET_PLATFORM), linux)

# Target filename
TRGFILE=$(OUTDIR)/$(TARGET)

# Toolchain base directory
TCHAIN_BASE=/usr/bin

# Toolchain prefix 
TCHAIN_PREFIX=

endif
# Windows options -----------------------------------------------------------
ifeq ($(TARGET_PLATFORM), win32)

# Target filename
TRGFILE=$(OUTDIR)/$(TARGET).exe

# Toolchain base directory
TCHAIN_BASE=/usr/bin

# Toolchain prefix 
TCHAIN_PREFIX=

endif
# ARM Cortex options --------------------------------------------------------

ifeq ($(TARGET_PLATFORM), arm)

CFLAGS += -mcpu=$(MCU)
CFLAGS += -mthumb
#CFLAGS += -mfpu=fpv4-sp-d16 
#CFLAGS += -mfloat-abi=hard 

LDSCRIPT = stm32_flash.ld
#LDSCRIPT = arm-gcc-link.ld
LDFLAGS += -T$(LDSCRIPT) -mthumb -mcpu=$(MCU) -nostdlib 
>>>>>>> 0b0411e726916f6f580389db0cace1cd82513846:examples/avr/Makefile

<<<<<<< HEAD:examples/avr-FreeRTOS/Makefile
#---------------- Library Options ----------------
=======
# Toolchain base directory
TCHAIN_BASE=/usr/bin
# Toolchain prefix 
TCHAIN_PREFIX=arm-none-eabi-

TRGFILE=$(OUTDIR)/$(TARGET).elf

endif

# Atmel AVR options ---------------------------------------------------------

ifeq ($(TARGET_PLATFORM), avr)
# MCU name
MCU = atmega2560

# Processor frequency.
# Some common values:
#  1000000  1843200  2000000 3686400 4000000 7372800 8000000 11059200 14745600
F_CPU = 8000000

CFLAGS   += -mmcu=$(MCU)
CPPFLAGS += -mmcu=$(MCU)
ASFLAGS  += -mmcu=$(MCU)

# Output format. (can be srec, ihex, binary)
FORMAT = ihex

# Debugging format.
#     Native formats for AVR-GCC's -g are dwarf-2 [default] or stabs.
#     AVR Studio 4.10 requires dwarf-2.
#     AVR [Extended] COFF format requires stabs, plus an avr-objcopy run.
DEBUG = dwarf-2

CDEFS   += F_CPU=$(F_CPU)UL
ADEFS   += F_CPU=$(F_CPU)UL

# Toolchain base directory
TCHAIN_BASE=/usr/bin
# Toolchain prefix 
TCHAIN_PREFIX=avr-

TRGFILE=$(OUTDIR)/$(TARGET).elf

# Library Options ------------------------------------------------------------
>>>>>>> 0844b056bed6e7009073b24369858df323002f8b:examples/avr/Makefile
# Minimalistic printf version
PRINTF_LIB_MIN = -Wl,-u,vfprintf -lprintf_min

# Floating point printf version (requires MATH_LIB = -lm below)
PRINTF_LIB_FLOAT = -Wl,-u,vfprintf -lprintf_flt

# If this is left blank, then it will use the Standard printf version.
PRINTF_LIB = 
#PRINTF_LIB = $(PRINTF_LIB_MIN)
#PRINTF_LIB = $(PRINTF_LIB_FLOAT)


# Minimalistic scanf version
SCANF_LIB_MIN = -Wl,-u,vfscanf -lscanf_min

# Floating point + %[ scanf version (requires MATH_LIB = -lm below)
SCANF_LIB_FLOAT = -Wl,-u,vfscanf -lscanf_flt

# If this is left blank, then it will use the Standard scanf version.
SCANF_LIB = 
#SCANF_LIB = $(SCANF_LIB_MIN)
#SCANF_LIB = $(SCANF_LIB_FLOAT)


MATH_LIB = -lm


# List any extra directories to look for libraries here.
#     Each directory must be seperated by a space.
#     Use forward slashes for directory separators.
#     For a directory that has spaces, enclose it in quotes.
EXTRALIBDIRS = 




#---------------- Linker Options ----------------
#  -Wl,...:     tell GCC to pass this to linker.
#    -Map:      create map file
#    --cref:    add cross reference to  map file
LDFLAGS  = -Wl,-Map=$(OUTDIR)/$(TARGET).map,--cref
LDFLAGS += $(EXTMEMOPTS)
#LDFLAGS += -T linker_script.x
LDFLAGS += $(patsubst %,-L%,$(INCLUDE))
LDFLAGS += $(PRINTF_LIB) $(SCANF_LIB) $(MATH_LIB)

#---------------- MCU Options ------------------

# MCU name
MCU = atmega2560

# Processor frequency.
# Some common values:
#  1000000  1843200  2000000 3686400 4000000 7372800 8000000 11059200 14745600
F_CPU = 8000000


#
# Tool settings
#============================================================================

# Define programs and commands.
SHELL     = bash
REMOVE    = rm -f
REMOVEDIR = rm -rf
COPY      = cp -f 
MOVE      = mv -f
WINSHELL  = cmd
MKDIR     = mkdir -p
SED       = sed
MOC       = moc
QMAKE     = qmake
CTEMPLATE = python3 tools/ctemplate.py
BIN2ARRAY = python3 tools/bin2array.py

CPPCHECK  = cppcheck

# Toolchain base directory
TCHAIN_BASE=/usr/bin

# Toolchain prefix (i.e arm-elf- -> arm-elf-gcc.exe)
TCHAIN_PREFIX=avr-

TCHAIN = $(TCHAIN_BASE)/$(TCHAIN_PREFIX)

CC        = ${TCHAIN}gcc
OBJCOPY   = ${TCHAIN}objcopy
OBJDUMP   = ${TCHAIN}objdump
SIZE      = ${TCHAIN}size
AR        = ${TCHAIN}ar rcs
NM        = ${TCHAIN}nm

#
# Message settings
#============================================================================

E_BLACK        = \033[0;300m
E_RED          = \033[0;31m
E_GREEN        = \033[0;32m
E_YELLOW       = \033[0;33m
E_BLUE         = \033[0;34m
E_MAGENTA      = \033[0;35m
E_CYAN         = \033[0;36m
E_GRAY         = \033[0;37m
E_DARKGRAY     = \033[1;30m
E_BR_RED       = \033[1;31m
E_BR_GREEN     = \033[1;32m
E_BR_YELLOW    = \033[1;33m
E_BR_BLUE      = \033[1;34m
E_BR_MAGENTA   = \033[1;35m
E_BR_CYAN      = \033[1;36m
E_WHITE        = \033[1;37m
E_END          = \033[0m
E_ON_BLACK     = \033[40
E_ON_RED       = \033[41
E_ON_GREEN     = \033[42
E_ON_YELLOW    = \033[43
E_ON_BLUE      = \033[44
E_ON_MAGENTA   = \033[45
E_ON_CYAN      = \033[46
E_ON_WHITE     = \033[1;47

C_OK=$(E_BR_GREEN)
C_ERROR=$(E_BR_RED)
C_WARNING=$(E_BR_YELLOW)
C_FILE=$(E_BR_CYAN)
C_NOTE=$(E_BR_GREEN)

MSG_LINE             = "$(E_WHITE)------------------------------------------------------------------$(E_END)"
MSG_BEGIN            = "${E_WHITE}-------------------------------- Begin ---------------------------${E_END}"
MSG_END              = "${E_WHITE}-------------------------------- End -----------------------------${E_END}"
MSG_ERRORS_NONE      = "${C_OK}Errors: none ${E_END}"
MSG_LINKING          = "${E_BR_MAGENTA}Linking:${E_END}"
MSG_COMPILING        = "${E_BR_MAGENTA}Compiling C:${E_END}"
MSG_COMPILING_CPP    = "${E_BR_MAGENTA}Compiling C++:${E_END}"
MSG_ASSEMBLING       = "${E_BR_MAGENTA}Assembling:${E_END}"
MSG_CLEANING         = "$(C_OK)Cleaning project:$(E_END)"
MSG_EXTENDED_LISTING = "${E_BR_MAGENTA}Creating Extended Listing/Disassembly:$(E_END)"
MSG_SYMBOL_TABLE     = "${E_BR_MAGENTA}Creating Symbol Table:$(E_END)"
MSG_FORMATERROR      = "${C_ERROR}Can not handle output-format${E_END}"
MSG_ASMFROMC         = "${E_BR_MAGENTA}Creating asm-File from C-Source:$(E_END)"
MSG_SIZE_BEFORE      = "${E_BR_MAGENTA}Size before:${E_END}"
MSG_SIZE_AFTER       = "${E_BR_MAGENTA}Size after build:${E_END}"
MSG_LOAD_FILE        = "${E_BR_MAGENTA}Creating load file:${E_END}"
MSG_ARCHIVING        = "${E_BR_MAGENTA}Creating tar archive:${E_END}"
MSG_CREATING_LIBRARY = "${E_BR_MAGENTA}Creating library:${E_END}"
MSG_FLASH            = "${E_BR_MAGENTA}Creating load file for Flash:${E_END}"
MSG_EEPROM           = "${E_BR_MAGENTA}Creating load file for EEPROM:${E_END}"
MSG_COFF             = "${E_BR_MAGENTA}Converting to AVR COFF:${E_END}"
MSG_EXTENDED_COFF    = "${E_BR_MAGENTA}Converting to AVR Extended COFF:${E_END}"
MSG_BACKUP           = "${E_BR_GREEN}Making incremental backup of project:${E_END}"
<<<<<<< HEAD:examples/avr-FreeRTOS/Makefile
=======
MSG_SRC              = "${C_MSG}Source files $(E_GREEN)-----------------------------------------------------${E_END}"
MSG_FLAGS            = "${C_MSG}Compiler Flags $(E_GREEN)---------------------------------------------------${E_END}"
MSG_LINKER           = "${C_MSG}Linker Flags $(E_GREEN)-----------------------------------------------------${E_END}"
MSG_PROJECT          = "${C_MSG}Project info $(E_GREEN)-----------------------------------------------------${E_END}"
MSG_INCLUDES         = "${C_MSG}Include directories $(E_GREEN)----------------------------------------------${E_END}"
MSG_DEFS             = "${C_MSG}Macro definitions $(E_GREEN)------------------------------------------------${E_END}"
>>>>>>> 0844b056bed6e7009073b24369858df323002f8b:examples/avr/Makefile

#while read x ; do echo $x ; done \
#| sed -e "s/.*error:.*/\x1b[1;36m&\x1b[0m/" \
#-e "s/.*warning:.*/\x1b[1;36m&\x1b[0m/" \
#-e "s/^\(.*\)\(required from\)/\x1b[1;36m\1\x1b[0mnote: \2/" \
#-e "s/^\(.*\)\(In instantiation of\)/\x1b[1;36m\1\x1b[0mnote: \2/" \
#-e "s/^\(.*\)\(In member\)/\x1b[1;36m\1\x1b[0mnote: \2/" \
#| sed -e "s/error:/\x1b[1;31m&\x1b[1;36m/" \
#-e "s/warning:/\x1b[1;35m&\x1b[1;36m/" \
#-e "s/note:/\x1b[1;30m&\x1b[0m/"

<<<<<<< HEAD:examples/avr-FreeRTOS/Makefile

#https://github.com/renatosilva/colormake/blob/master/colormake.sh
#http://stackoverflow.com/questions/1032237/highlight-and-filter-gcc-compiler-messages
#https://github.com/renatosilva/colormake

# Compiler output colorizer filter
=======
# Compiler output colorizer filter ------------------------------------------

F_INF="s/In function/$$(printf "$(E_BR_GREEN)")&$$(printf "$(E_END)")/i"
FF_INF="s/^.*In function/$$(printf "$(C_FILE)")&$$(printf "$(E_END)")/i"
>>>>>>> 0844b056bed6e7009073b24369858df323002f8b:examples/avr/Makefile
F_ERROR="s/error:/$$(printf "$(C_ERROR)")&$$(printf "$(E_END)")/i"
F_WARNING="s/warning:/$$(printf "$(C_WARNING)")&$$(printf "$(E_END)")/i"
F_NOTE="s/note:/$$(printf "$(C_NOTE)")&$$(printf "$(E_END)")/i"
FF_ERROR="s/^.*error:/$$(printf "$(C_FILE)")&$$(printf "$(E_END)")/i"
FF_WARNING="s/^.*warning:/$$(printf "$(C_FILE)")&$$(printf "$(E_END)")/i"
FF_NOTE="s/^.*note:/$$(printf "$(C_FILE)")&$$(printf "$(E_END)")/i"
F_WARNING1="s/defined but not used/$$(printf "$(C_WARNING)")&$$(printf "$(E_END)")/i"
F_WARNING2="s/unused variable/$$(printf "$(C_WARNING)")&$$(printf "$(E_END)")/i"
F_WARNING3="s/may be used uninitialized in this function/$$(printf "$(C_WARNING)")&$$(printf "$(E_END)")/i"
C_FILTER   = | sed -ru -e $(F_ERROR)  -e $(F_WARNING)  -e $(F_NOTE) \
<<<<<<< HEAD:examples/avr-FreeRTOS/Makefile
                     -e $(FF_ERROR) -e $(FF_WARNING) -e $(FF_NOTE)
=======
                       -e $(FF_ERROR) -e $(FF_WARNING) -e $(FF_NOTE) \
<<<<<<< HEAD:examples/avr-FreeRTOS/Makefile
                       -e $(F_WARNING1) -e $(F_WARNING2) -e $(F_WARNING3) 
>>>>>>> 0b0411e726916f6f580389db0cace1cd82513846:examples/avr/Makefile
=======
                       -e $(F_WARNING1) -e $(F_WARNING2) -e $(F_WARNING3) \
											 -e $(F_INF) -e $(FF_INF)
>>>>>>> 0844b056bed6e7009073b24369858df323002f8b:examples/avr/Makefile
CPP_FILTER = $(C_FILTER)

LD_ERROR1="s/undefined reference/$$(printf "$(C_ERROR)")&$$(printf "$(E_END)")/i"
LD_ERROR2="s/No such file or directory/$$(printf "$(C_ERROR)")&$$(printf "$(E_END)")/i"
LD_FILTER = | sed -ru -e $(LD_ERROR1) -e $(LD_ERROR2)

#---------------- Programming Options (avrdude) ----------------

# Programming hardware
# Type: avrdude -c ?
# to get a full listing.
#
AVRDUDE_PROGRAMMER = stk500v2

# com1 = serial port. Use lpt1 to connect to parallel port.
AVRDUDE_PORT = com1    # programmer connected to serial device

AVRDUDE_WRITE_FLASH = -U flash:w:$(TARGET).hex
#AVRDUDE_WRITE_EEPROM = -U eeprom:w:$(TARGET).eep


# Uncomment the following if you want avrdude's erase cycle counter.
# Note that this counter needs to be initialized first using -Yn,
# see avrdude manual.
#AVRDUDE_ERASE_COUNTER = -y

# Uncomment the following if you do /not/ wish a verification to be
# performed after programming the device.
#AVRDUDE_NO_VERIFY = -V

# Increase verbosity level.  Please use this when submitting bug
# reports about avrdude. See <http://savannah.nongnu.org/projects/avrdude> 
# to submit bug reports.
#AVRDUDE_VERBOSE = -v -v

AVRDUDE_FLAGS = -p $(MCU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER)
AVRDUDE_FLAGS += $(AVRDUDE_NO_VERIFY)
AVRDUDE_FLAGS += $(AVRDUDE_VERBOSE)
AVRDUDE_FLAGS += $(AVRDUDE_ERASE_COUNTER)



#---------------- Debugging Options ----------------

# For simulavr only - target MCU frequency.
DEBUG_MFREQ = $(F_CPU)

# Set the DEBUG_UI to either gdb or insight.
# DEBUG_UI = gdb
DEBUG_UI = insight

# Set the debugging back-end to either avarice, simulavr.
DEBUG_BACKEND = avarice
#DEBUG_BACKEND = simulavr

# GDB Init Filename.
GDBINIT_FILE = __avr_gdbinit

# When using avarice settings for the JTAG
JTAG_DEV = /dev/com1

# Debugging port used to communicate between GDB / avarice / simulavr.
DEBUG_PORT = 4242

# Debugging host used to communicate between GDB / avarice / simulavr, normally
#     just set to localhost unless doing some sort of crazy debugging when 
#     avarice is running on a different computer.
DEBUG_HOST = localhost

#============================================================================

# Compiler flags to generate dependency files.
GENDEPFLAGS = -MMD -MP -MF .dep/$(@F).d

# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_CFLAGS = -mmcu=$(MCU) -I. $(CFLAGS) $(GENDEPFLAGS)
ALL_CPPFLAGS = -mmcu=$(MCU) -I. -x c++ $(CPPFLAGS) $(GENDEPFLAGS)
ALL_ASFLAGS = -mmcu=$(MCU) -I. -x assembler-with-cpp $(ASFLAGS)

# Define all object files.
OBJS = $(SRC:%.c=$(OBJDIR)/%.o) $(CPPSRC:%.cpp=$(OBJDIR)/%.o) $(ASRC:%.S=$(OBJDIR)/%.o)

# Define all listing files.
LST = $(SRC:%.c=$(OBJDIR)/%.lst) $(CPPSRC:%.cpp=$(OBJDIR)/%.lst) $(ASRC:%.S=$(OBJDIR)/%.lst) 

# Default target.
<<<<<<< HEAD:examples/avr-FreeRTOS/Makefile
all: begin sizebefore build sizeafter end
=======
all:	begin build finished end
>>>>>>> 0844b056bed6e7009073b24369858df323002f8b:examples/avr/Makefile

# Remove colorfilter
nocolor:
	$(eval C_FILTER:= )
	
#
# Build with no color filter on compiler output
# Useful for Netbeans, Eclipse builds etc. 
#	
nc: nocolor all   ## Build with no color on compiler output

# Change the build target to build a HEX file or a library.
build: elf hex eep lss sym


elf: $(OUTDIR)/$(TARGET).elf
lss: $(OUTDIR)/$(TARGET).lss
sym: $(OUTDIR)/$(TARGET).sym
hex: $(OUTDIR)/$(TARGET).hex
bin: $(OUTDIR)/$(TARGET).bin
eep: $(OUTDIR)/$(TARGET).eep

# Eye candy.
begin:
	@echo -e "$(E_BR_MAGENTA)Building:     $(E_BR_GREEN)$(TARGET) $(E_END)"
	@echo -e $(MSG_BEGIN)
 
end:
	@echo
	@echo -e $(MSG_END)
	
finished:
	@echo
	@echo -e $(MSG_ERRORS_NONE)


# Display size of file.
HEXSIZE = $(SIZE) --target=$(FORMAT) $(OUTDIR)/$(TARGET).hex
ELFSIZE = $(SIZE) --mcu=$(MCU) --format=avr $(OUTDIR)/$(TARGET).elf

sizebefore:
	@if [ -f $(OUTDIR)/$(TARGET).elf ]; then echo; echo $(MSG_SIZE_BEFORE); $(ELFSIZE); \
 	2>/dev/null; echo; fi

sizeafter:
	@if [ -f $(OUTDIR)/$(TARGET).elf ]; then echo; echo -e $(MSG_SIZE_AFTER); $(ELFSIZE); \
	2>/dev/null; echo; fi



# Display compiler version information.
gccversion :  ## Display compiler version
	@$(CC) --version

# Link target
.SECONDARY : $(TARGET).elf
.PRECIOUS : $(OBJS)
%.elf: $(OBJS) $(OUTDIR)
	@echo 
	@echo -e $(MSG_LINKING)"\n             $(C_FILE)" $@ "$(E_END)"
	@$(CC) $(ALL_CFLAGS) $(OBJS) --output $@ $(LDFLAGS) $(LIB) 2>&1 $(LD_FILTER)
	
# Create extended listing file/disassambly from ELF output file.
# using objdump testing: option -C
%.lss:	$(TRGFILE)
	@echo
	@echo -e $(MSG_EXTENDED_LISTING) "\n             $(C_FILE)" $@ "$(E_END)"
	@$(OBJDUMP) -h -S -z $< > $@
	
# Create a symbol table from ELF output file.
%.sym: $(TRGFILE)
	@echo
	@echo -e $(MSG_SYMBOL_TABLE) "\n             $(C_FILE)" $@ "$(E_END)"
	@$(NM) -n $< > $@

# Create hex file from ELF output file.
%.hex: %.elf
	@echo
	@echo -e $(MSG_HEX_FILE) "\n             $(C_FILE)" $@ "$(E_END)"
	@$(OBJCOPY) -O $(FORMAT) -R .eeprom -R .fuse -R .lock -R .signature $< $@


# Program the device.  
program: $(TARGET).hex $(TARGET).eep
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH) $(AVRDUDE_WRITE_EEPROM)


# Generate avr-gdb config/init file which does the following:
#     define the reset signal, load the target file, connect to target, and set 
#     a breakpoint at main().
gdb-config: 
	@$(REMOVE) $(GDBINIT_FILE)
	@echo define reset >> $(GDBINIT_FILE)
	@echo SIGNAL SIGHUP >> $(GDBINIT_FILE)
	@echo end >> $(GDBINIT_FILE)
	@echo file $(TARGET).elf >> $(GDBINIT_FILE)
	@echo target remote $(DEBUG_HOST):$(DEBUG_PORT)  >> $(GDBINIT_FILE)
ifeq ($(DEBUG_BACKEND),simulavr)
	@echo load  >> $(GDBINIT_FILE)
endif
	@echo break main >> $(GDBINIT_FILE)

debug: gdb-config $(TARGET).elf
ifeq ($(DEBUG_BACKEND), avarice)
	@echo Starting AVaRICE - Press enter when "waiting to connect" message displays.
	@$(WINSHELL) /c start avarice --jtag $(JTAG_DEV) --erase --program --file \
	$(TARGET).elf $(DEBUG_HOST):$(DEBUG_PORT)
	@$(WINSHELL) /c pause

else
@$(WINSHELL) /c start simulavr --gdbserver --device $(MCU) --clock-freq \
$(DEBUG_MFREQ) --port $(DEBUG_PORT)
endif
@$(WINSHELL) /c start avr-$(DEBUG_UI) --command=$(GDBINIT_FILE)




# Convert ELF to COFF for use in debugging / simulating in AVR Studio or VMLAB.
COFFCONVERT = $(OBJCOPY) --debugging
COFFCONVERT += --change-section-address .data-0x800000
COFFCONVERT += --change-section-address .bss-0x800000
COFFCONVERT += --change-section-address .noinit-0x800000
COFFCONVERT += --change-section-address .eeprom-0x810000



coff: $(TARGET).elf
	@echo
	@echo -e $(MSG_COFF)"\n  " "$(E_BR_CYAN)" $(TARGET).cof "$(E_END)"
	$(COFFCONVERT) -O coff-avr $< $(TARGET).cof

extcoff: $(TARGET).elf
	@echo
	@echo -e $(MSG_EXTENDED_COFF)"\n  " "$(E_BR_CYAN)" $(TARGET).cof "$(E_END)"
	@$(COFFCONVERT) -O coff-ext-avr $< $(TARGET).cof

%.eep: %.elf
	@echo
	@echo -e $(MSG_EEPROM)"\n  " "$(E_BR_CYAN)" $@ "$(E_END)"
	@$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 --no-change-warnings -O $(FORMAT) $< $@ || exit 0

<<<<<<< HEAD:examples/avr-FreeRTOS/Makefile
# Create extended listing file/disassambly from ELF output file.
# using objdump testing: option -C
%.lss: %.elf
	@echo
	@echo -e $(MSG_EXTENDED_LISTING)"\n  " "$(E_BR_CYAN)" $@ "$(E_END)"
	@$(OBJDUMP) -h -S -z $< > $@

# Create a symbol table from ELF output file.
%.sym: %.elf
	@echo
	@echo -e $(MSG_SYMBOL_TABLE) "\n             $(E_BR_CYAN)" $@ "$(E_END)"
	@$(NM) -n $< > $@
=======
>>>>>>> 0844b056bed6e7009073b24369858df323002f8b:examples/avr/Makefile



# Compile: create object files from C source files.
$(OBJDIR)/%.o : %.c
	@echo -e $(MSG_COMPILING) "$(C_FILE)" $< "$(E_END)"
	@$(CC) -c $(ALL_CFLAGS) $< -o $@ 2>&1  $(C_FILTER)

# Compile: create object files from C++ source files.
$(OBJDIR)/%.o : %.cpp
	@echo
	@echo -e $(MSG_COMPILING_CPP) "$(C_FILE)" $< "$(E_END)"
	@$(CC) -c $(ALL_CPPFLAGS) $< -o $@ 2>&1 | $(CPP_FILTER)
	
# Assemble: create object files from assembler source files.
$(OBJDIR)/%.o : %.S
	@echo
	@echo -e $(MSG_ASSEMBLING) "$(C_FILE)" $< "$(E_END)"
	@$(CC) -c $(ALL_ASFLAGS) $< -o $@

# Compile: create assembler files from C source files.
$(OBJDIR)/%.s : %.c
	@$(CC) -S $(ALL_CFLAGS) $< -o $@

# Compile: create assembler files from C++ source files.
$(OBJDIR)/%.s : %.cpp
	@$(CC) -S $(ALL_CPPFLAGS) $< -o $@

# Create output dir
$(OUTDIR):
	@$(MKDIR) $@


#
# Various utility rules	
#============================================================================


clean:  ## Remove all build files
	@echo
	@echo -e $(MSG_CLEANING)
	@$(REMOVE) $(OUTDIR)/$(TARGET)
	@$(REMOVE) $(OUTDIR)/$(TARGET).elf
	@$(REMOVE) $(OUTDIR)/$(TARGET).hex
	@$(REMOVE) $(OUTDIR)/$(TARGET).lss
	@$(REMOVE) $(OUTDIR)/$(TARGET).map
	@$(REMOVE) $(OUTDIR)/$(TARGET).sym
	@$(REMOVE) $(OUTDIR)/$(TARGET).bin
	@$(REMOVE) $(OUTDIR)/$(TARGET).eep
	@$(REMOVE) $(OUTDIR)/$(TARGET).cof
	@$(REMOVE) $(SRC:%.c=$(OBJDIR)/%.o)
	@$(REMOVE) $(SRC:%.c=$(OBJDIR)/%.lst)
	@$(REMOVE) $(SRC:.c=.s)
	@$(REMOVE) $(SRC:.c=.d)
	@$(REMOVE) $(SRC:.c=.i)
	@$(REMOVEDIR) .dep
	@$(REMOVE) $(OBJS)
	@find . -name *~ -delete


archive: ## Make a tar archive of the source code
	@echo
	@echo -e $(MSG_ARCHIVING)
	@$(MKDIR) archive
	@tar -cvzf archive/$(TARGET).tar.gz *  \
	     --exclude='archive' \
	     --exclude='backup'  \
	     --exclude='output'  \
	     --exclude='*.o'     \
	     --exclude='*.a'     \
	     --exclude='.dep'    \
	     --exclude='.svn'    \
	     --exclude='.git'    \
	     --exclude='*.elf'   \
 	     --exclude='*.hex'   \
	     --exclude='*.bin'   \
	     --exclude='*.sym'   \
	     --exclude='*.lss'   \
	     --exclude='*.map'   \
	     --exclude='*~'      \
	     --exclude="*.old"   \

# Backup directory
BACKUP_DIR=backup

# Nr of backups
BACKUPS=100

backup: ## Make an incremental backup
	@echo
	@echo -e $(MSG_BACKUP)
	@$(MKDIR) $(BACKUP_DIR)
  # remove oldest backup
	@$(RM) -rf $(BACKUP_DIR)/backup_$(BACKUPS) 
  # rotate backups 
	@for ((x=$(BACKUPS);x>0;x--)); do                 \
	  bdir=$(BACKUP_DIR)/backup_`expr $${x} - 1` ;    \
	  # check if directory exist before renameing  it \
	  if [ -d $${bdir} ]; then                        \
	    mv -f $${bdir}  $(BACKUP_DIR)/backup_$${x} ;  \
	  fi ;                                            \
	done 
	@rsync --archive             \
	      --delete               \
				--relative             \
				--exclude="backup"     \
				--exclude="archive"    \
				--exclude="output"     \
				--exclude="*.o"        \
				--exclude=".git"       \
				--exclude=".svn"       \
				--exclude="*~"         \
				--exclude="*.old"      \
				--link-dest=$(CURDIR)/$(BACKUP_DIR)/backup_1 \
				.                      \
				$(BACKUP_DIR)/backup_0 


edit:   ## Open source and makefile in editor
	@$(EDITOR) Makefile src/gpio.c src/main.c src/gpio.h
# #	@$(EDITOR) Makefile $(SRC)


# Include the dependency files.
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

newfile:  ## Create a new C file
	@${CTEMPLATE} --newc --dir src --author "$(AUTHOR)" --licence "$(LICENCE)"
	
install: ## Install program
	@${COPY} output/${TARGET} /usr/local/bin

#
# Help information
#============================================================================

help: ## This help information
	@printf "%-30s %s\n" "target" "help"
	@echo -e $(MSG_LINE)
	@IFS=$$'\n' ;                                    \
	help_lines=(`fgrep -h "##" $(MAKEFILE_LIST) | fgrep -v fgrep | sed -e 's/\\$$//' | sed -e 's/##/:/'`); \
	for help_line in $${help_lines[@]}; do                                     \
	  IFS=$$':' ;                                                              \
		help_split=($$help_line) ;                                               \
		help_command=`echo $${help_split[0]} | sed -e 's/^ *//' -e 's/ *$$//'` ; \
		help_info=`echo $${help_split[2]} | sed -e 's/^ *//' -e 's/ *$$//'` ;    \
		printf "$(E_BR_CYAN)%-15s %s$(E_END)" $$help_command ;                 \
		printf "$(E_BR_GREEN)%s$(E_END)\n" $$help_info ;                       \
	done ; 
	@echo -e $(MSG_LINE)

list-src: ## List all source files
	@echo -e "$(E_BR_CYAN)#----------------- Source files$(E_END)"
	@export IFS=" "
	@for f in $(SRC); do      \
	  echo $${f} ;            \
	done                      \
	
list-flags: ## List compiler flags
	@echo -e "$(E_BR_CYAN)#----------------- Compiler Flags$(E_END)"
	@export IFS=" "
	@for f in $(CFLAGS); do   \
	  echo $${f} ;            \
	done                      \

list-ldflags: ## List compiler flags
	@echo -e "$(E_BR_CYAN)#----------------- Linker Flags$(E_END)"
	@export IFS=" "
	@for f in $(LDFLAGS); do   \
	  echo $${f} ;             \
	done                       \

<<<<<<< HEAD:examples/avr-FreeRTOS/Makefile
=======
check: ## Check if tools and libraries are present 
	@$(MPTOOL) ce $(CC)
	@$(MPTOOL) ce $(OBJCOPY)
	@$(MPTOOL) ce $(OBJDUMP)
	@$(MPTOOL) ce $(SIZE)
	@$(MPTOOL) ce $(AR)
	@$(MPTOOL) ce $(NM)
	@$(MPTOOL) ce $(AS)
	@$(MPTOOL) ce $(QMAKE)
	@$(MPTOOL) ce $(MOC)
	@$(MPTOOL) ce python3
	@$(MPTOOL) ce $(CPPCHECK)
	@for f in $(LIB); do               \
		${MPTOOL} cl ${CC} $${f};      \
	done                               \
	
<<<<<<< HEAD:examples/avr-FreeRTOS/Makefile
>>>>>>> 0b0411e726916f6f580389db0cace1cd82513846:examples/avr/Makefile

list-info: 
	@echo "Target: $(TARGET)"
	@echo "Outdir: $(OUTDIR)"
	
 
info: list-info list-flags list-ldflags list-src ## Print information about project
=======
list-info: 
	@echo -e $(MSG_PROJECT)
	@echo "Target:   $(TARGET)"
	@echo "Platform: $(TARGET_PLATFORM)"
	@echo "Licence:  $(LICENCE)"
	@echo "Outdir:   $(OUTDIR)"
	@echo "MCU:      $(MCU)"
	@echo "F_CPU:    $(F_CPU)"
	

list-includes: 
	@echo -e $(MSG_INCLUDES)
	@export IFS=" "
	@for f in $(INCLUDE); do   \
	  echo $${f} ;             \
	done        

list-defs: 
	@echo -e $(MSG_DEFS)
	@export IFS=" "
	@for f in $(CDEFS); do     \
	  echo $${f} ;             \
	done        

	@for f in $(CPPDEFS); do   \
	  echo $${f} ;             \
	done        

	@for f in $(ASDEFS); do    \
	  echo $${f} ;             \
	done        


info: list-info list-includes list-defs list-flags list-ldflags  ## Print information about project

files: list-src ## List source files
>>>>>>> 0844b056bed6e7009073b24369858df323002f8b:examples/avr/Makefile
	
#
# Personal settings
#============================================================================

# Only for default settings. Change value in settings.mk
AUTHOR=Your Name <your.name@yourdomain.org>
EDITOR=jed
US:=$$USER
#PERSONAL=personal_$${USER}.mk
PERSONAL=personal.mk

# Include some external settings
# If file does not exist it will be generated.
include  ${PERSONAL}

$(PERSONAL):	# Create a settings file
	@echo "#" > ${PERSONAL}
	@echo "# This file is for personal settings only." >> ${PERSONAL}
	@echo "#" >> ${PERSONAL}
	@echo "EDITOR=${EDITOR}" >> ${PERSONAL}
	@echo "AUTHOR=${AUTHOR}" >> ${PERSONAL}



#
# CppCheck static code analysis
#============================================================================
.PHONY: ccheck acheck

ccheck: ## Static code analysis using cppcheck(errors only)
	@$(CPPCHECK) --inline-suppr $(SRC) 

acheck: ## Static code analysis using cppcheck(all warnings)
	@$(CPPCHECK) --inline-suppr --enable=all $(SRC) 


<<<<<<< HEAD:examples/avr-FreeRTOS/Makefile
=======
#
# Avrdude settings 
#============================================================================
>>>>>>> 0b0411e726916f6f580389db0cace1cd82513846:examples/avr/Makefile


	
# Listing of phony targets.
.PHONY : all clean gccversion build begin finished end elf lss sym archive edit help backup list-src list-flags newproj run install
