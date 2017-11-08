# Hey Emacs, this is a -*- makefile -*-
#----------------------------------------------------------------------------
#
# Brief:   __BRIEF__
# 
# Name:    __NAME__
# Author:  __AUTHOR__
# Date:    __DATE__
# Org:     __ORG__
# 
# License: __LICENSE__
# 
#----------------------------------------------------------------------------
# [Makeplates]
# This script is generated from makeplates Makefile project generator.
#
# Makeplates is developed by:
# Peter Malmberg <peter.malmberg@gmail.com>
#
# Makeplates is available at:
# https://github.com/zonbrisad/makeplates
# 
# [Disclaimer] 
# Use on your own risk.
#----------------------------------------------------------------------------
# [Help]
# 
# Enter "make help" to get information about different targets.
# 
#----------------------------------------------------------------------------


#
# Message/Filter settings
#============================================================================

# Color definitions ---------------------------------------------------------
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
E_ON_BLACK     = \033[40m
E_ON_RED       = \033[41m
E_ON_GREEN     = \033[42m
E_ON_YELLOW    = \033[43m
E_ON_BLUE      = \033[44m
E_ON_MAGENTA   = \033[45m
E_ON_CYAN      = \033[46m
E_ON_WHITE     = \033[47m

# ANSI Text attributes
E_ATTR_BOLD=\e[1m
E_ATTR_LOWI=\e[2m
E_ATTR_UNDERLINE=\e[4m
E_ATTR_BLINK=\e[5m
E_ATTR_REVERSE=\e[7m

# System color definitions
C_OK=$(E_BR_GREEN)
C_WARNING=$(E_BR_YELLOW)
C_ERROR=$(E_BR_RED)
C_FILE=$(E_BR_CYAN)
C_DIR=$(E_CYAN)
C_NOTE=$(E_BR_GREEN)
C_MSG=$(E_BR_GREEN)
C_ACTION=$(E_BR_MAGENTA)
C_VALUE=$(E_WHITE)$(E_ON_BLUE)
C_IDENTIFIER=$(E_WHITE)

# Messages ------------------------------------------------------------------
MSG_LINE             = "$(E_WHITE)------------------------------------------------------------------$(E_END)"
MSG_BEGIN            = "${E_WHITE}-------------------------------- Begin ---------------------------${E_END}"
MSG_END              = "${E_WHITE}-------------------------------- End -----------------------------${E_END}"
MSG_ERRORS_NONE      = "${C_OK}Errors: none ${E_END}"
MSG_STRIP            = "${C_ACTION}Striping:${E_END}"
MSG_LINKING          = "${C_ACTION}Linking:${E_END}"
MSG_COMPILING        = "${C_ACTION}Compiling C:  ${E_END}"
MSG_COMPILING_CPP    = "${C_ACTION}Compiling C++:${E_END}"
MSG_ASSEMBLING       = "${C_ACTION}Assembling:${E_END}"
MSG_CLEANING         = "$(C_ACTION)Cleaning project:$(E_END)"
MSG_EXTENDED_LISTING = "${C_ACTION}Creating Extended Listing/Disassembly:$(E_END)"
MSG_SYMBOL_TABLE     = "${C_ACTION}Creating Symbol Table:$(E_END)"
MSG_HEX_FILE         = "${C_ACTION}Creating Hex file:$(E_END)"
MSG_FORMATERROR      = "${C_ERROR}Can not handle output-format${E_END}"
MSG_ASMFROMC         = "${C_ACTION}Creating asm-File from C-Source:$(E_END)"
MSG_SIZE_BEFORE      = "${C_ACTION}Size before:${E_END}"
MSG_SIZE_AFTER       = "${C_ACTION}Size after build:${E_END}"
MSG_LOAD_FILE        = "${C_ACTION}Creating load file:${E_END}"
MSG_ARCHIVING        = "${C_ACTION}Creating tar archive:${E_END}"
MSG_CREATING_LIBRARY = "${C_ACTION}Creating library:${E_END}"
MSG_FLASH            = "${C_ACTION}Creating load file for Flash:${E_END}"
MSG_EEPROM           = "${C_ACTION}Creating load file for EEPROM:${E_END}"
MSG_COFF             = "${C_ACTION}Converting to AVR COFF:${E_END}"
MSG_EXTENDED_COFF    = "${C_ACTION}Converting to AVR Extended COFF:${E_END}"
MSG_MOC              = "${C_ACTION}Creating MOC file:${E_END}"
MSG_UI               = "${C_ACTION}Generating UI header:${E_END}"
MSG_BACKUP           = "${C_ACTION}Making incremental backup of project:${E_END}"
MSG_SRC              = "${C_MSG}Source files $(E_GREEN)-----------------------------------------------------${E_END}"
MSG_FLAGS            = "${C_MSG}Compiler Flags $(E_GREEN)---------------------------------------------------${E_END}"
MSG_LINKER           = "${C_MSG}Linker Flags $(E_GREEN)-----------------------------------------------------${E_END}"
MSG_PROJECT          = "${C_MSG}Project info $(E_GREEN)-----------------------------------------------------${E_END}"
MSG_INCLUDES         = "${C_MSG}Include directories $(E_GREEN)----------------------------------------------${E_END}"
MSG_OBJECTS          = "${C_MSG}Object files $(E_GREEN)-----------------------------------------------------${E_END}"	
MSG_DEFS             = "${C_MSG}Macro definitions $(E_GREEN)------------------------------------------------${E_END}"
MSG_INSTALL_INFO     = "${C_MSG}Install settings $(E_GREEN)-------------------------------------------------${E_END}"
MSG_INSTALLING       = "${C_ACTION}Installing:   ${E_END}"
MSG_BUILDING         = "$(C_ACTION)Building:     "
	
# Compiler output colorizer filter ------------------------------------------
F_SOURCE=| sed -e "s/\(.*\/\)\(.*\)/$$(printf "$(C_DIR)")\1$$(printf "$(C_FILE)")\2$$(printf "$(E_END)")/"
F_INF="s/In function/$$(printf "$(E_BR_GREEN)")&$$(printf "$(E_END)")/i"
F_NOTE="s/note:/$$(printf "$(C_NOTE)")&$$(printf "$(E_END)")/i"
F_WARNING="s/warning:/$$(printf "$(C_WARNING)")&$$(printf "$(E_END)")/i"
F_ERROR="s/error:/$$(printf "$(C_ERROR)")&$$(printf "$(E_END)")/i"
F_FATAL_ERROR="s/fatal error:/$$(printf "$(C_ERROR)")&$$(printf "$(E_END)")/i"
F_WARNING1="s/defined but not used/$$(printf "$(C_WARNING)")&$$(printf "$(E_END)")/i"
F_WARNING2="s/unused variable/$$(printf "$(C_WARNING)")&$$(printf "$(E_END)")/i"
F_WARNING3="s/may be used uninitialized in this function/$$(printf "$(C_WARNING)")&$$(printf "$(E_END)")/i"
F_WARNING4="s/implicit declaration of function/$$(printf "$(C_WARNING)")&$$(printf "$(E_END)")/i"
F_WARNING5="s/value computed is not used/$$(printf "$(C_WARNING)")&$$(printf "$(E_END)")/i"
F_BRACKET="s/\[\(.*\)\]/[$$(printf "$(E_GREEN)")\1$$(printf "$(E_END)")]/"	
F_VARIABLE="s/\‘\(.*\)[\’\‘]/'$$(printf "$(C_IDENTIFIER)")\1$$(printf "$(E_END)")'/g"
F_FILE="s/[^: ]*/$$(printf "$(C_FILE)")&$$(printf "$(E_END)")/"
F_ROWNR="s/:\([0-9]*\):\([0-9]*\):/:$$(printf "$(C_VALUE)")\1$$(printf "$(E_END)"):$$(printf "$(C_VALUE)")\2$$(printf "$(E_END)"):/"

C_FILTER   = | sed -u -e $(F_BRACKET) -e $(F_FILE) -e $(F_ROWNR)          \
                      -e $(F_INF) -e $(F_NOTE)                            \
 	                  -e $(F_WARNING) -e $(F_ERROR) -e $(F_FATAL_ERROR)   \
                      -e $(F_WARNING1) -e $(F_WARNING2) -e $(F_WARNING3)  \
                      -e $(F_WARNING4) -e $(F_WARNING5)                   \
                      -e $(F_VARIABLE)

CPP_FILTER = $(C_FILTER)

LD_ERROR1="s/undefined reference/$$(printf "$(C_ERROR)")&$$(printf "$(E_END)")/i"
LD_ERROR2="s/No such file or directory/$$(printf "$(C_ERROR)")&$$(printf "$(E_END)")/i"
LD_FILTER = | sed -ru -e $(LD_ERROR1) -e $(LD_ERROR2)
	
