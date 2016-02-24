# Hey Emacs, this is a -*- makefile -*-
#----------------------------------------------------------------------------
# 
# General Atmel AVR  Makefile template.
#
# author: Peter Malmberg <peter.malmberg@gmail.com>
#
#  
#----------------------------------------------------------------------------
# On command line:
# >make help 
#----------------------------------------------------------------------------

# Project Licence (GPL, GPLv2, MIT, BSD, Apache, etc.) 
LICENCE = GPLv2

# Target file name (without extension).
TARGET = avr

# List C source files here. (C dependencies are automatically generated.)
SRC = src/main.c 

# List C++ source files here. (C dependencies are automatically generated.)
CPPSRC = 

# List Assembler source files here.
#     Make them always end in a capital .S.  
ASRC =

# Include directories
INCLUDE = inc \
          src 

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


# Debugging format.
#     Native formats for AVR-GCC's -g are dwarf-2 [default] or stabs.
#     AVR Studio 4.10 requires dwarf-2.
#     AVR [Extended] COFF format requires stabs, plus an avr-objcopy run.
DEBUG = dwarf-2


# Compiler flag to set the C Standard level.
# [ gnu99 gnu11 c++98 c++03 c++11 c++14 ] 
CSTANDARD = -std=gnu99

# Place -D or -U options here for C sources
CDEFS = 

# Place -D or -U options here for ASM sources
ADEFS = 

# Place -D or -U options here for C++ sources
CPPDEFS = 

# Compiler Options C ---------------------------------------------------------
#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC manual
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -adhlns...: create assembler listing
CFLAGS = -g$(DEBUG)
CFLAGS += $(CDEFS)
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


# Compiler Options C++ -------------------------------------------------------
#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC manual and avr-libc documentation
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -adhlns...: create assembler listing
CPPFLAGS = -g$(DEBUG)
CPPFLAGS += $(CPPDEFS)
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


# Assembler Options ----------------------------------------------------------
#  -Wa,...:   tell GCC to pass this to the assembler.
#  -adhlns:   create listing
#  -gstabs:   have the assembler create line number information; note that
#             for use in COFF files, additional information about filenames
#             and function names needs to be present in the assembler source
#             files -- see avr-libc docs [FIXME: not yet described there]
#  -listing-cont-lines: Sets the maximum number of continuation lines of hex 
#       dump that will be displayed for a given single line of source input.
ASFLAGS = $(ADEFS) -Wa,-adhlns=$(<:%.S=$(OBJDIR)/%.lst),-gstabs,--listing-cont-lines=100


# Library Options ------------------------------------------------------------
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


# Linker Options -------------------------------------------------------------
#  -Wl,...:     tell GCC to pass this to linker.
#    -Map:      create map file
#    --cref:    add cross reference to  map file
LDFLAGS = -Wl,-Map=$(OUTDIR)/$(TARGET).map,--cref
LDFLAGS += $(EXTMEMOPTS)
LDFLAGS += $(patsubst %,-L%,$(INCLUDE))

# MCU Options ----------------------------------------------------------------

# MCU name
MCU = atmega2560

# Processor frequency.
# Some common values:
#  1000000  1843200  2000000 3686400 4000000 7372800 8000000 11059200 14745600
F_CPU = 8000000

CFLAGS   += -mmcu=$(MCU)
CPPFLAGS += -mmcu=$(MCU)
ASFLAGS  += -mmcu=$(MCU)

# # Atmel AVR options ---------------------------------------------------------

# Output format. (can be srec, ihex, binary)
FORMAT = ihex

CDEFS   += -DF_CPU=$(F_CPU)UL
ADEFS   += -DF_CPU=$(F_CPU)UL
CPPDEFS += -DF_CPU=$(F_CPU)UL

LDFLAGS += $(PRINTF_LIB) $(SCANF_LIB) $(MATH_LIB)

# ARM Cortex options --------------------------------------------------------

#LDFLAGS += -T linker_script.x
 
# Linux options --------------------------------------------------------------

# Windows options ------------------------------------------------------------

# Tool options ---------------------------------------------------------------

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

# Message settings -----------------------------------------------------------

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

# Compiler output colorizer filter
F_ERROR="s/error:/$$(printf "$(C_ERROR)")&$$(printf "$(E_END)")/i"
F_WARNING="s/warning:/$$(printf "$(C_WARNING)")&$$(printf "$(E_END)")/i"
F_NOTE="s/note:/$$(printf "$(C_NOTE)")&$$(printf "$(E_END)")/i"
FF_ERROR="s/^.*error:/$$(printf "$(C_FILE)")&$$(printf "$(E_END)")/i"
FF_WARNING="s/^.*warning:/$$(printf "$(C_FILE)")&$$(printf "$(E_END)")/i"
FF_NOTE="s/^.*note:/$$(printf "$(C_FILE)")&$$(printf "$(E_END)")/i"

C_FILTER   = | sed -ru -e $(F_ERROR)  -e $(F_WARNING)  -e $(F_NOTE) \
                       -e $(FF_ERROR) -e $(FF_WARNING) -e $(FF_NOTE)
CPP_FILTER = $(C_FILTER)

LD_ERROR1="s/undefined reference/$$(printf "$(C_ERROR)")&$$(printf "$(E_END)")/i"
LD_ERROR2="s/No such file or directory/$$(printf "$(C_ERROR)")&$$(printf "$(E_END)")/i"
LD_FILTER = | sed -ru -e $(LD_ERROR1) -e $(LD_ERROR2)
	
#
# Build rules	
#============================================================================

# Compiler flags to generate dependency files.
GENDEPFLAGS = -MMD -MP -MF .dep/$(@F).d

# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_CFLAGS   =  -I. $(CFLAGS) $(GENDEPFLAGS)
ALL_CPPFLAGS =  -I. -x c++ $(CPPFLAGS) $(GENDEPFLAGS)
ALL_ASFLAGS  =  -I. -x assembler-with-cpp $(ASFLAGS)

# Define all object files.
OBJS = $(SRC:%.c=$(OBJDIR)/%.o) $(CPPSRC:%.cpp=$(OBJDIR)/%.o) $(ASRC:%.S=$(OBJDIR)/%.o)

# Define all listing files.
LST = $(SRC:%.c=$(OBJDIR)/%.lst) $(CPPSRC:%.cpp=$(OBJDIR)/%.lst) $(ASRC:%.S=$(OBJDIR)/%.lst) 

# Default target.
all: begin sizebefore build sizeafter end

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
#ifeq ($(DEBUG_BACKEND), avarice)
#	@echo Starting AVaRICE - Press enter when "waiting to connect" message displays.
#	@$(WINSHELL) /c start avarice --jtag $(JTAG_DEV) --erase --program --file \
#	$(TARGET).elf $(DEBUG_HOST):$(DEBUG_PORT)
#	@$(WINSHELL) /c pause
#else
#@$(WINSHELL) /c start simulavr --gdbserver --device $(MCU) --clock-freq \
#$(DEBUG_MFREQ) --port $(DEBUG_PORT)
#endif
#@$(WINSHELL) /c start avr-$(DEBUG_UI) --command=$(GDBINIT_FILE)




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



# Create final output files (.hex, .eep) from ELF output file.
%.hex: %.elf
	@echo
	@echo -e $(MSG_FLASH)"\n  " "$(E_BR_CYAN)" $@ "$(E_END)"
	@$(OBJCOPY) -O $(FORMAT) -R .eeprom -R .fuse -R .lock -R .signature $< $@

%.eep: %.elf
	@echo
	@echo -e $(MSG_EEPROM)"\n  " "$(E_BR_CYAN)" $@ "$(E_END)"
	@$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 --no-change-warnings -O $(FORMAT) $< $@ || exit 0

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


# Link: create ELF output file from object files.
.SECONDARY : $(TARGET).elf
.PRECIOUS : $(OBJS)
%.elf: $(OBJS) $(OUTDIR)
	@echo -e $(MSG_LINKING)"\n  " "$(E_BR_CYAN)" $@ "$(E_END)"
	@$(CC) $(ALL_CFLAGS) $(OBJS) --output $@ $(LDFLAGS) $(LIB)


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
	@$(EDITOR) Makefile $(SRC)


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


list-info: 
	@echo "Target: $(TARGET)"
	@echo "Outdir: $(OUTDIR)"
	
 
info: list-info list-flags list-ldflags list-src ## Print information about project
	
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

#
# Version control handling
#============================================================================

# Avrdude settings ----------------------------------------------------------

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
# 
	
# Listing of phony targets.
.PHONY : all clean gccversion build begin finished end elf lss sym archive edit help backup list-src list-flags newproj run install
