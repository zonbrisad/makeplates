
###SETTINGS_BEGIN###
# CPU model
CPU = cortex-m0plus

# Pico SDK directory
PICOSDK = /pico/sdk

###SETTINGS_END###


###PLATFORM-SPECIFIC_BEGIN###
# ARM options ---------------------------------------------------------

# Target filename
TRGFILE=$(OUTDIR)/$(TARGET).elf

# Toolchain base directory
TCHAIN_BASE=/usr/bin

# Toolchain prefix 
TCHAIN_PREFIX=arm-none-eabi-

CFLAGS += -fpic                  # Position independet code
CFLAGS += -nostartfiles
CFLAGS += -mthumb  
CFLAGS += -ffreestanding  
CFLAGS += -c 
CFLAGS += -mfloat-abi=soft

# Output format. (can be srec, ihex, binary) --------------------------------
FORMAT = ihex

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
LDFLAGS += -g 
LDFLAGS += -T link_carlos.ld  
LDFLAGS += --entry 0x20040001


###PLATFORM-SPECIFIC_END###

###BUILD_BEGIN###
build: elf hex uf2 lss sym size

elf: $(TRGFILE)
lss: $(OUTDIR)/$(TARGET).lss
sym: $(OUTDIR)/$(TARGET).sym
hex: $(OUTDIR)/$(TARGET).hex
uf2: $(OUTDIR)/$(TARGET).uf2
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
.PHONY: flash flashu run

DBG_INTERFACE = interface/cmsis-dap.cfg
DBG_TARGET = target/rp2040.cfg
DBG_SPEED = 5000

flash: ##D Flash program to mcu via debugprobe(openocd)
	@openocd -f $(DBG_INTERFACE)  -f $(DBG_TARGET) -c "adapter speed $(DBG_SPEED)" -c "program $(OUTDIR)/$(TARGET).elf verify reset exit"

flashu: ##D Flash program to mcu via USB drive(UF2)
	@$(MPUTILS) rp_usb_flash $(OUTDIR)/$(TARGET).uf2

run: ##D Run program in RAM, download via debugprobe(openocd)
	@openocd -f $(DBG_INTERFACE)  -f $(DBG_TARGET) -c "adapter speed $(DBG_SPEED)" -c "init" -c "reset halt" -c "load_image $(OUTDIR)/$(TARGET).elf" -c "reset halt" -c "resume 0x20040001" -c "shutdown"

###INSTALL_END###


###UTILS_BEGIN###
###UTILS_END###

###TOOLS_BEGIN###
###TOOLS_END###
