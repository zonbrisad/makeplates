
###SETTINGS_BEGIN###
# MCU name
MCU = __MCU__

# MCU frequency. (1000000  1843200  2000000 3686400 4000000 7372800 8000000 11059200 14745600)
F_CPU = 16000000
###SETTINGS_END###


###PLATFORM-SPECIFIC_BEGIN###
# ARM options ---------------------------------------------------------
CFLAGS += -mcpu=$(MCU)
CPPFLAGS += -mcpu=$(MCU)
ASFLAGS  += -mcpu=$(MCU)

CFLAGS += 

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
SIZEFLAGS = --format=berkely  

# objdump flags -------------------------------------------------------------
ODFLAGS  = -h  # Display the contents of the section headers  
ODFLAGS += -S  # Intermix source code with disassembly
ODFLAGS += -z  #
#ODFLAGS += -r  # Display the relocation entries in the file

# object copy flags ---------------------------------------------------------
#OCFLAGS = -O $(FORMAT) -R .eeprom -R .fuse -R .lock -R .signature

# Library Options -----------------------------------------------------------

LDFLAGS += -nostdlib
#LDFLAGS += $(PRINTF_LIB) $(SCANF_LIB) $(MATH_LIB)

###PLATFORM-SPECIFIC_END###

###BUILD_BEGIN###
build: elf hex lss sym size

elf: $(TRGFILE)
lss: $(OUTDIR)/$(TARGET).lss
sym: $(OUTDIR)/$(TARGET).sym
hex: $(OUTDIR)/$(TARGET).hex
#eep: $(OUTDIR)/$(TARGET).eep
###BUILD_END###

###TARGETS_BEGIN###
###TARGETS_END###


###RUNDEBUG_BEGIN###
#
# ARM simulator
#============================================================================
.PHONY: sim term

# QEMU machine type		
QMACHINE = virt

# tcp port for QEMU terminal output
QPORT = 5678

QFLAGS  = -machine $(QMACHINE)
QFLAGS += -bios $(TRGFILE)
QFLAGS += -serial tcp::$(QPORT),server=on,wait=off
QFLAGS += -nographic

sim: ##D Run program in qemu ARM simulator
	@echo 
	@echo Starting QEMU arm simulator. 
	@echo Terminal output available on tcp port $(QPORT). 
	@echo
	@qemu-system-arm $(QFLAGS)
	
term: ##D Connect to QEMU terminal output with telnet 
	@$(MPUTILS) sermon $(QPORT)
###RUNDEBUG_END###


###INSTALL_BEGIN###
###INSTALL_END###


###UTILS_BEGIN###
###UTILS_END###


###TOOLS_BEGIN###
###TOOLS_END###
