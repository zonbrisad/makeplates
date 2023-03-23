
###SETTINGS_BEGIN###
###SETTINGS_END###


###PLATFORM-SPECIFIC_BEGIN###
 # Linux options -------------------------------------------------------------

# Target filename
TRGFILE=$(OUTDIR)/$(TARGET)

# Toolchain base directory
TCHAIN_BASE=/usr/bin

# Toolchain prefix 
TCHAIN_PREFIX=

# Handle pkg-config libraries -----------------------------------------------
CFLAGS   += $(foreach X, $(PKGLIBS), $(shell pkg-config --cflags $(X)) )
CPPFLAGS += $(foreach X, $(PKGLIBS), $(shell pkg-config --cflags $(X)) )
LDFLAGS  += $(foreach X, $(PKGLIBS), $(shell pkg-config --libs $(X))   )

# Size flags ----------------------------------------------------------------
SIZEFLAGS = --format=berkley  # format = {sysv|berkeley}

# objdump flags -------------------------------------------------------------
ODFLAGS  = -h  # Display the contents of the section headers  
ODFLAGS += -S  # Intermix source code with disassembly
ODFLAGS += -C  #
ODFLAGS += -r  # Display the relocation entries in the file

# Output format. (can be srec, ihex, binary) --------------------------------
FORMAT = ihex

# object copy flags ---------------------------------------------------------
OCFLAGS = -O $(FORMAT) 
###PLATFORM-SPECIFIC_END###

###BUILD_BEGIN###
build: elf lss sym size

elf: $(TRGFILE)
lss: $(OUTDIR)/$(TARGET).lss
sym: $(OUTDIR)/$(TARGET).sym
###BUILD_END###


###TARGETS_BEGIN###
###TARGETS_END###


###RUNDEBUG_BEGIN###
run:    ##D Run application
	@$(OUTDIR)/$(TARGET)

debug: ##D Debug program
	@$(GDB) $(TRGFILE) 
###RUNDEBUG_END###


###INSTALL_BEGIN###
# Install options -----------------------------------------------------------
.PHONY: install 

# Install directory
INSTALL_DIR      = ~/bin

# Owner of binary
INSTALL_OWNER    = $${USER}

# Group owner of binary
# #INSTALL_GROUP    = $${USER}
INSTALL_GROUP    = users

# Install options
INSTALL_OPTIONS =  --owner ${INSTALL_OWNER}
INSTALL_OPTIONS += --group ${INSTALL_GROUP}
INSTALL_OPTIONS += -D
INSTALL_OPTIONS += --preserve-timestamps
#INSTALL_OPTIONS += --verbose

install: $(TRGFILE) ##D Install program
	@echo -e $(MSG_INSTALLING) "$(E_BR_GREEN)$(TARGET) $(E_END)"
	@${INSTALL} ${INSTALL_OPTIONS} $(TRGFILE) ${INSTALL_DIR}

###INSTALL_END###


###UTILS_BEGIN###
###UTILS_END###

###TOOLS_BEGIN###
###TOOLS_END###