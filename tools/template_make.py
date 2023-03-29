#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# ----------------------------------------------------------------------------
#
# Makefile templates
#
# File:     template_make.py
# Author:   Peter Malmberg  <peter.malmberg@gmail.com>
# Org:      
# Date:     2023-03-13
# License:  
# Python:   >= 3.0
#
# ----------------------------------------------------------------------------

from __future__ import annotations
from dataclasses import dataclass
import json
import os

@dataclass
class TemplateMake:
    text: str = ""

    header_text: str = ""

    settings_text: str = ""
    platform_specific_text: str = ""
    build_text: str = ""
    tools_text: str = ""
    targets_text: str = ""
    rundebug_text: str = ""
    install_text: str = ""
    utils_text: str = ""

    query_text: str = ""
    query: bool = True
    incl: bool = True


    def add(self, a: TemplateMake):
        self.header_text += a.header_text

        self.settings_text += a.settings_text
        self.platform_specific_text += a.platform_specific_text
        self.build_text += a.build_text

        self.tools_text += a.tools_text
        self.targets_text += a.targets_text
        
        self.rundebug_text += a.rundebug_text
        self.install_text += a.install_text
        self.utils_text += a.utils_text


    def write_field(self, fieldname, filename: str):
        data = getattr(fieldname)
        with open(filename, "w") as file:
            file.write(data)

    def load_field(self, fieldname, filename: str):
      pass

  

t_header = TemplateMake(
    header_text="""\
/**
 *---------------------------------------------------------------------------
 * @brief    __DESCRIPTION__
 *
 * @file     __FILENAME__
 * @author   __AUTHOR__ __EMAIL__
 * @version  __VERSION__
 * @date     __DATE__
 * @license  __LICENSE__
 *
 *---------------------------------------------------------------------------
 *
 *
 */
"""
)


target_avr = TemplateMake(
  settings_text="""\
# MCU name
MCU = __MCU__
 
# MCU frequency. (1000000  1843200  2000000 3686400 4000000 7372800 8000000 11059200 14745600)
F_CPU = 16000000
""",
  platform_specific_text="""\
Atmel AVR options ---------------------------------------------------------
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
""",
  build_text="""\
build: elf hex lss sym size
 
elf: $(TRGFILE)
lss: $(OUTDIR)/$(TARGET).lss
sym: $(OUTDIR)/$(TARGET).sym
hex: $(OUTDIR)/$(TARGET).hex
eep: $(OUTDIR)/$(TARGET).eep
""",
  targets_text="""\
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
""",
  rundebug_text="""\
#
# AVR simulator
#============================================================================
.PHONY: sim term
 
# QEMU machine type     
QMACHINE = arduino-uno
 
# tcp port for QEMU virtual serial port
QPORT = 5678
 
sim: ##D Run program in qemu AVR simulator
    @echo 
    @echo Starting QEMU avr simulator. Connect to tcp port $(QPORT). 
    @echo
    @qemu-system-avr -machine $(QMACHINE) -bios $(TRGFILE) -serial tcp::$(QPORT),server=on,wait=off -nographic
    
term: ##D Connect to QEMU virtual serial port via telnet terminal 
    @$(MPUTILS) sermon $(QPORT)

"""  
)


def main() -> None:
    pass

if __name__ == "__main__":
    main()
