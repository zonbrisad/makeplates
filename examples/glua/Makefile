# Hey Emacs, this is a -*- makefile -*-
#----------------------------------------------------------------------------
# 
# Makeplate glib lua example project
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
TARGET = glua

# List C source files here. (C dependencies are automatically generated.)
SRC = src/main.c \
      src/gp_log.c \
      src/lua-5.2.3/src/lstrlib.c \
			src/lua-5.2.3/src/lvm.c \
			src/lua-5.2.3/src/lzio.c \
			src/lua-5.2.3/src/lfunc.c \
			src/lua-5.2.3/src/ldo.c \
			src/lua-5.2.3/src/lgc.c \
			src/lua-5.2.3/src/lbitlib.c \
			src/lua-5.2.3/src/ldump.c \
			src/lua-5.2.3/src/lctype.c \
			src/lua-5.2.3/src/lauxlib.c \
			src/lua-5.2.3/src/lundump.c \
			src/lua-5.2.3/src/lmem.c \
			src/lua-5.2.3/src/ltm.c \
			src/lua-5.2.3/src/ldebug.c \
			src/lua-5.2.3/src/lmathlib.c \
			src/lua-5.2.3/src/ltablib.c \
			src/lua-5.2.3/src/lapi.c \
			src/lua-5.2.3/src/loadlib.c \
			src/lua-5.2.3/src/llex.c \
			src/lua-5.2.3/src/lstring.c \
			src/lua-5.2.3/src/lbaselib.c \
			src/lua-5.2.3/src/lobject.c \
			src/lua-5.2.3/src/loslib.c \
			src/lua-5.2.3/src/lstate.c \
			src/lua-5.2.3/src/lparser.c \
			src/lua-5.2.3/src/ltable.c \
			src/lua-5.2.3/src/lopcodes.c \
			src/lua-5.2.3/src/linit.c \
			src/lua-5.2.3/src/lcorolib.c \
			src/lua-5.2.3/src/lcode.c \
			src/lua-5.2.3/src/liolib.c \
			src/lua-5.2.3/src/ldblib.c \
			src/SWILL-0.3/Source/SWILL/encoding.c \
			src/SWILL-0.3/Source/SWILL/handlers.c \
			src/SWILL-0.3/Source/SWILL/io.c \
			src/SWILL-0.3/Source/SWILL/log.c \
			src/SWILL-0.3/Source/SWILL/mime.c \
			src/SWILL-0.3/Source/SWILL/parse.c \
			src/SWILL-0.3/Source/SWILL/security.c \
			src/SWILL-0.3/Source/SWILL/sock.c \
			src/SWILL-0.3/Source/SWILL/ssl.c \
			src/SWILL-0.3/Source/SWILL/web.c \
			src/SWILL-0.3/Source/Objects/base.c \
			src/SWILL-0.3/Source/Objects/file.c \
			src/SWILL-0.3/Source/Objects/fio.c \
			src/SWILL-0.3/Source/Objects/hash.c \
			src/SWILL-0.3/Source/Objects/list.c \
			src/SWILL-0.3/Source/Objects/memory.c \
			src/SWILL-0.3/Source/Objects/string.c \
			src/SWILL-0.3/Source/Objects/void.c 


# List C++ source files here. (C dependencies are automatically generated.)
CPPSRC = 

# List Assembler source files here.
#     Make them always end in a capital .S.  
ASRC =

# Include directories
INCLUDE = inc \
          src \
					src/iniparser3.1/src \
					src/lua-5.2.3/src \
					src/argtable2-13/src \
			    src/SWILL-0.3/Include   \
			    src/SWILL-0.3/Source/SWILL \
			    src/SWILL-0.3/Source/Objects 


# Libraries to link
LIB  = -lm 
LIB += $(shell pkg-config --libs glib-2.0)
LIB += $(shell pkg-config --libs gthread-2.0)
#LIB += $(shell pkg-config --libs ncurses)
#LIB += $(shell pkg-config --libs lua5.1)

# Object files directory
#     To put object files in current directory, use a dot (.), do NOT make
#     this an empty or blank macro!
OBJDIR = .

# Output directory
OUTDIR = output

# Optimization level, can be [0, 1, 2, 3, s]. 
#     0 = turn off optimization. s = optimize for size.
OPT = 2

# Compiler flag to set the C Standard level.
# [ gnu99 gnu11 c++98 c++03 c++11 c++14 ] 
CSTANDARD = -std=gnu99

CDEFS = -DHAVE_CONFIG_H \
        -DLUA_USE_MKSTEMP 

# Place -D or -U options here for ASM sources
ADEFS = 

# Place -D or -U options here for C++ sources
CPPDEFS = 

#---------------- Compiler Options C ----------------
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
#CFLAGS += -funsigned-bitfields
#CFLAGS += -fpack-struct
#CFLAGS += -fshort-enums
CFLAGS += -Wall
#CFLAGS += -Wstrict-prototypes
#CFLAGS += -mshort-calls
#CFLAGS += -fno-unit-at-a-time
#CFLAGS += -Wundef
CFLAGS += -Wunreachable-code
#CFLAGS += -Wsign-compare
#CFLAGS += -Wa,-adhlns=$(<:%.c=$(OBJDIR)/%.lst)
CFLAGS += $(patsubst %,-I%,$(INCLUDE))
CFLAGS += $(CSTANDARD)
CFLAGS += $(shell pkg-config --cflags glib-2.0)
CFLAGS += $(shell pkg-config --cflags gthread-2.0)
#CFLAGS += $(shell pkg-config --cflags lua5.1)


#---------------- Compiler Options C++ ----------------
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
CPPFLAGS += $(shell pkg-config --cflags glib-2.0)
CPPFLAGS += $(shell pkg-config --cflags gthread-2.0)


#---------------- Assembler Options ----------------
#  -Wa,...:   tell GCC to pass this to the assembler.
#  -adhlns:   create listing
#  -gstabs:   have the assembler create line number information; note that
#             for use in COFF files, additional information about filenames
#             and function names needs to be present in the assembler source
#             files -- see avr-libc docs [FIXME: not yet described there]
#  -listing-cont-lines: Sets the maximum number of continuation lines of hex 
#       dump that will be displayed for a given single line of source input.
ASFLAGS = $(ADEFS) -Wa,-adhlns=$(<:%.S=$(OBJDIR)/%.lst),-gstabs,--listing-cont-lines=100

#---------------- Linker Options ----------------
#  -Wl,...:     tell GCC to pass this to linker.
#    -Map:      create map file
#    --cref:    add cross reference to  map file
LDFLAGS = -Wl,-Map=$(OUTDIR)/$(TARGET).map,--cref
LDFLAGS += $(EXTMEMOPTS)
#LDFLAGS += -T linker_script.x

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
TCHAIN_PREFIX=

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
MSG_BACKUP           = "${E_BR_GREEN}Making incremental backup of project:${E_END}"

#while read x ; do echo $x ; done \
#| sed -e "s/.*error:.*/\x1b[1;36m&\x1b[0m/" \
#-e "s/.*warning:.*/\x1b[1;36m&\x1b[0m/" \
#-e "s/^\(.*\)\(required from\)/\x1b[1;36m\1\x1b[0mnote: \2/" \
#-e "s/^\(.*\)\(In instantiation of\)/\x1b[1;36m\1\x1b[0mnote: \2/" \
#-e "s/^\(.*\)\(In member\)/\x1b[1;36m\1\x1b[0mnote: \2/" \
#| sed -e "s/error:/\x1b[1;31m&\x1b[1;36m/" \
#-e "s/warning:/\x1b[1;35m&\x1b[1;36m/" \
#-e "s/note:/\x1b[1;30m&\x1b[0m/"


#https://github.com/renatosilva/colormake/blob/master/colormake.sh
#http://stackoverflow.com/questions/1032237/highlight-and-filter-gcc-compiler-messages
#https://github.com/renatosilva/colormake

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
all:	begin build finished end

# Remove colorfilter
nocolor:
	$(eval C_FILTER:= )
	
#
# Build with no color filter on compiler output
# Useful for Netbeans, Eclipse builds etc. 
#	
nc: nocolor all   ## Build with no color on compiler output


build: elf lss sym

elf: $(OUTDIR)/$(TARGET)
lss: $(OUTDIR)/$(TARGET).lss
sym: $(OUTDIR)/$(TARGET).sym
hex: $(OUTDIR)/$(TARGET).hex
bin: $(OUTDIR)/$(TARGET).bin

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

# Display compiler version information.
gccversion :  ## Display compiler version
	@$(CC) --version

# Link target
#.SECONDARY : $(TARGET)
.PRECIOUS : $(OBJS)
$(OUTDIR)/$(TARGET): $(OBJS) $(OUTDIR)
	@echo 
	@echo -e $(MSG_LINKING)"\n             $(E_BR_CYAN)" $@ "$(E_END)"
	@$(CC) $(ALL_CFLAGS) $(OBJS) --output $@ $(LDFLAGS) $(LIB) 2>&1 $(LD_FILTER)
	
# Create extended listing file/disassambly from ELF output file.
# using objdump testing: option -C
%.lss:	$(OUTDIR)/$(TARGET)
	@echo
	@echo -e $(MSG_EXTENDED_LISTING) "\n             $(E_BR_CYAN)" $@ "$(E_END)"
	@$(OBJDUMP) -h -S -C -r $< > $@
	
# Create a symbol table from ELF output file.
%.sym: $(OUTDIR)/$(TARGET)
	@echo
	@echo -e $(MSG_SYMBOL_TABLE) "\n             $(E_BR_CYAN)" $@ "$(E_END)"
	@$(NM) -n $< > $@

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

run:    ## Run application
	@output/$(TARGET)

debug:  ## Debug application


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
AUTHOR=Peter Malmberg <peter.malmberg@gmail.com>
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



	
# Listing of phony targets.
.PHONY : all clean gccversion build begin finished end elf lss sym archive edit help backup list-src list-flags newproj run install
