
###SETTINGS_BEGIN###
# MCU name
MCU = atmega328

# MCU frequency. (1000000  1843200  2000000 3686400 4000000 7372800 8000000 11059200 14745600)
F_CPU = 16000000
###SETTINGS_END###


###PLATFORM-SPECIFIC_BEGIN###
# Atmel AVR options ---------------------------------------------------------
CFLAGS   += -mmcu=$(MCU)
CPPFLAGS += -mmcu=$(MCU)
ASFLAGS  += -mmcu=$(MCU)

# Output format. (can be srec, ihex, binary) --------------------------------
FORMAT = ihex

# Debugging format.
#     Native formats for AVR-GCC's -g are dwarf-2 [default] or stabs.
#     AVR Studio 4.10 requires dwarf-2.
#     AVR [Extended] COFF format requires stabs, plus an avr-objcopy run.
DEBUG = dwarf-2

CDEFS   += F_CPU=$(F_CPU)UL
ADEFS   += F_CPU=$(F_CPU)UL
CPPDEFS += F_CPU=$(F_CPU)UL

# Toolchain base directory
TCHAIN_BASE=/usr/bin
# Toolchain prefix 
TCHAIN_PREFIX=avr-

TRGFILE=$(OUTDIR)/$(TARGET).elf

# Size flags ----------------------------------------------------------------
SIZEFLAGS = --mcu=$(MCU) --format=avr  # format = {sysv|berkeley}

# objdump flags -------------------------------------------------------------
ODFLAGS  = -h  # Display the contents of the section headers  
ODFLAGS += -S  # Intermix source code with disassembly
ODFLAGS += -z  #
#ODFLAGS += -r  # Display the relocation entries in the file

# object copy flags ---------------------------------------------------------
OCFLAGS = -O $(FORMAT) -R .eeprom -R .fuse -R .lock -R .signature

# Library Options -----------------------------------------------------------
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

LDFLAGS += $(PRINTF_LIB) $(SCANF_LIB) $(MATH_LIB)
###PLATFORM-SPECIFIC_END###


###TOOLS_BEGIN###
###TOOLS_END###


###DEBUG_BEGIN###
###DEBUG_END###


###UTILS_BEGIN###
###UTILS_END###


###INSTALL_BEGIN###
#
# Avrdude settings 
# ----------------------------------------------------------
.PHONY: program
	
AVRDUDE = avrdude	
# Programming hardware
# Type: avrdude -c ?
# to get a full listing.
#
#AVRDUDE_PROGRAMMER = stk500v2
AVRDUDE_PROGRAMMER = arduino
 
# com1 = serial port. Use lpt1 to connect to parallel port.
AVRDUDE_PORT = /dev/ttyUSB1    # programmer connected to serial device

AVRDUDE_BITRATE = 57600 
 
AVRDUDE_WRITE_FLASH = -U flash:w:$(OUTDIR)/$(TARGET).hex:i
#AVRDUDE_WRITE_EEPROM = -U eeprom:w:$(TARGET).eep
  
# Uncomment the following if you want avrdude's erase cycle counter.
# Note that this counter needs to be initialized first using -Yn,
# see avrdude manual.
#AVRDUDE_ERASE_COUNTER = -y

# Uncomment the following if you do /not/ wish a verification to be
# performed after programming the device.
#AVRDUDE_NO_VERIFY = -V

# Increase verbosity level.  
AVRDUDE_VERBOSE = -v -v
 
AVRDUDE_FLAGS = -p $(MCU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER) -b ${AVRDUDE_BITRATE} -D
AVRDUDE_FLAGS += $(AVRDUDE_NO_VERIFY)
AVRDUDE_FLAGS += $(AVRDUDE_VERBOSE)
AVRDUDE_FLAGS += $(AVRDUDE_ERASE_COUNTER)

# Program the device.
program: $(TARGET).hex # $(TARGET).eep  ## Burn program into flash 
	@$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH) # $(AVRDUDE_WRITE_EEPROM)

#
# AVR simulator
#============================================================================
.PHONY: sim

sim:  ## Run AVR simulator 
#	simavr --mcu $(MCU) --freq $(F_CPU)  $(TRGFILE) 
# -W 0x20,- -R 0x22,- -T exit --irqstatistic
	simulavr -d $(MCU) -F $(F_CPU) --file $(TRGFILE) -W 0x20,- -R 0x22,- -T exit --irqstatistic
###INSTALL_END###


###TARGETS_BEGIN###
#
# AVR specific targets
#============================================================================

coff: $(TRGFILE)
	@echo
	@echo -e $(MSG_COFF)"\n             $(E_FG_BR_CYAN)" $(TARGET).cof "$(E_RESET)"
	$(COFFCONVERT) -O coff-avr $< $(TARGET).cof

extcoff: $(TRGFILE)
	@echo
	@echo -e $(MSG_EXTENDED_COFF)"\n             $(E_FG_BR_CYAN)" $(TARGET).cof "$(E_RESET)"
	@$(COFFCONVERT) -O coff-ext-avr $< $(TARGET).cof

%.eep: $(TRGFILE)
	@echo
	@echo -en $(MSG_EEPROM)"\n               "
	@echo -e $@ $(F_SOURCE)
	@$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 --no-change-warnings -O $(FORMAT) $< $@ || exit 0
###TARGETS_END###