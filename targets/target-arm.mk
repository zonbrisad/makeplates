
###SETTINGS_BEGIN###
# MCU name
MCU = __MCU__

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

CDEFS   += F_CPU=$(F_CPU)UL
ADEFS   += F_CPU=$(F_CPU)UL
CPPDEFS += F_CPU=$(F_CPU)UL

# Toolchain base directory
TCHAIN_BASE=/usr/bin
# Toolchain prefix 
TCHAIN_PREFIX=arm-none-eabi-

TRGFILE=$(OUTDIR)/$(TARGET).elf

# Size flags ----------------------------------------------------------------
SIZEFLAGS = --format=berkely  # format = {sysv|berkeley}

# objdump flags -------------------------------------------------------------
ODFLAGS  = -h  # Display the contents of the section headers  
ODFLAGS += -S  # Intermix source code with disassembly
ODFLAGS += -z  #
#ODFLAGS += -r  # Display the relocation entries in the file

# object copy flags ---------------------------------------------------------
OCFLAGS = -O $(FORMAT) -R .eeprom -R .fuse -R .lock -R .signature

# Library Options -----------------------------------------------------------


LDFLAGS += $(PRINTF_LIB) $(SCANF_LIB) $(MATH_LIB)
###PLATFORM-SPECIFIC_END###

###BUILD_BEGIN###
build: elf hex lss sym size

elf: $(TRGFILE)
lss: $(OUTDIR)/$(TARGET).lss
sym: $(OUTDIR)/$(TARGET).sym
hex: $(OUTDIR)/$(TARGET).hex
eep: $(OUTDIR)/$(TARGET).eep
###BUILD_END###

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


###RUNDEBUG_BEGIN###
#
# AVR simulator
#============================================================================
.PHONY: sim term

# QEMU machine type		
QMACHINE = 

# tcp port for QEMU virtual serial port
QPORT = 5678

sim: ##D Run program in qemu ARM simulator
	@echo 
	@echo Starting QEMU arm simulator. Connect to tcp port $(QPORT). 
	@echo
	@qemu-system-arm -machine $(QMACHINE) -bios $(TRGFILE) -serial tcp::$(QPORT),server=on,wait=off -nographic
	
term: ##D Connect to QEMU virtual serial port via telnet terminal 
	@$(MPUTILS) sermon $(QPORT)
###RUNDEBUG_END###


###INSTALL_BEGIN###
###INSTALL_END###


###UTILS_BEGIN###
###UTILS_END###


###TOOLS_BEGIN###
###TOOLS_END###
