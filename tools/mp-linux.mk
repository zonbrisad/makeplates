

# Define programs and commands ----------------------------------------------
SHELL     = bash
WINSHELL  = cmd
REMOVE    = rm -f
REMOVEDIR = rm -rf
COPY      = cp -f 
MOVE      = mv -f
MKDIR     = mkdir -p
SED       = sed              # stream editor program
MOC       = moc              # Qt meta object compiler
QMAKE     = qmake            # Qt make program
UIC       = uic              # Qt resource file compiler
CTEMPLATE = python3 tools/ctemplate.py # C/C++ template tool
BIN2ARRAY = python3 tools/bin2array.py # Binary to array tool
MPTOOL    = tools/mptools    # Makeplate tools
CPPCHECK  = cppcheck
INSTALL   = install
ASTYLE    = astyle           # Code beatyfier
DOXYGEN   = doxygen          # Code documetation program

TCHAIN = $(TCHAIN_BASE)/$(TCHAIN_PREFIX)

CC        = ${TCHAIN}gcc
CPP       = ${TCHAIN}g++
OBJCOPY   = ${TCHAIN}objcopy
OBJDUMP   = ${TCHAIN}objdump
SIZE      = ${TCHAIN}size
AR        = ${TCHAIN}ar rcs
NM        = ${TCHAIN}nm
AS        = ${TCHAIN}as
GDB       = ${TCHAIN}gdb
STRIP     = ${TCHAIN}strip
