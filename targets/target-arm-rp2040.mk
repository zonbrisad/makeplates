
###SETTINGS_BEGIN###
# CPU model
CPU = cortex-m0plus

###SETTINGS_END###


###PLATFORM-SPECIFIC_BEGIN###
# ARM options ---------------------------------------------------------

# Target filename
TRGFILE=$(OUTDIR)/$(TARGET).elf

# Toolchain base directory
TCHAIN_BASE=/usr/bin

# Toolchain prefix 
TCHAIN_PREFIX=arm-none-eabi-

CFLAGS += -mcpu=$(CPU)
CXXFLAGS += -mcpu=$(CPU)
ASFLAGS  += -mcpu=$(CPU)

# Output format. (can be srec, ihex, binary) --------------------------------
FORMAT = ihex

CDEFS   += F_CPU=$(F_CPU)UL
ADEFS   += F_CPU=$(F_CPU)UL
CPPDEFS += F_CPU=$(F_CPU)UL


# Size flags ----------------------------------------------------------------
SIZEFLAGS = --format=berkely  

# objdump flags -------------------------------------------------------------
ODFLAGS  = -h  # Display the contents of the section headers  
ODFLAGS += -S  # Intermix source code with disassembly
ODFLAGS += -z  #


# object copy flags ---------------------------------------------------------
#OCFLAGS = -O $(FORMAT) 

# Library Options -----------------------------------------------------------

LDFLAGS += -nostdlib

###PLATFORM-SPECIFIC_END###

###BUILD_BEGIN###
build: elf hex lss sym size

elf: $(TRGFILE)
lss: $(OUTDIR)/$(TARGET).lss
sym: $(OUTDIR)/$(TARGET).sym
hex: $(OUTDIR)/$(TARGET).hex
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
.PHONY: flash

DBG_INTERFACE = interface/cmsis-dap.cfg

DBG_TARGET = target/rp2040.cfg

DBG_SPEED = 5000

flash: ##D Download program to flash via debugprobe(openocd)
	@openocd -f $(DBG_INTERFACE)  -f $(DBG_TARGET) -c "adapter speed $(DBG_SPEED)" -c "program $(OUTDIR)/$(TARGET).elf verify reset exit"

flashu: ##D Flash program to mcu via USB drive
	@$(MPUTILS) rp_usb_flash $(OUTDIR)/$(TARGET).uf2
###INSTALL_END###


###UTILS_BEGIN###
###UTILS_END###

###TOOLS_BEGIN###
###TOOLS_END###
