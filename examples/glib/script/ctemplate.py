#
# C template code generator
#
# Version 0.1
# 
# History
#
# Ver 0.1 2016-02-19

# Todo 
# 


import parser
import os
import struct
import logging
from optparse import OptionParser
from datetime import datetime, date, time

usage="""
usage: %prog infile outfile
"""

def addHeader(file, fileName, brief, date):
    file.write( 
    "/**\n"
    " *---------------------------------------------------------------------------\n"
    " * @file    "+fileName+"\n"
    " * @brief   "+brief+"\n"
    " *\n"
    " * @author  __AUTHOR__\n"
    " * @date    "+date+"\n"
    " * @licence __LICENCE__\n"
    " *\n"
    " *---------------------------------------------------------------------------\n"
    " */\n\n")
 

def addSection(file, desc):
    file.write(                \
    "/**\n"                    \
    " * "+desc+"\n"            \
    " *------------------------------------------------------------------\n" \
    " */\n\n") 
    

def addSentinelBegin(file):
    file.write(                \
    "#ifndef $sentinel"        \
    "#define $sentinel\n\n\n") \

    
#def addSentinelEnd(file):
    

def newModule():
    print("New module")
    brief = input("Enter brief description:> ")
    date = datetime.now().strftime("%Y-%m-%d")

    # Open input file
    fName="nisse"
    fileNameC = fName + ".c"
    fileNameH = fName + ".h"
    
    try:
        fileC = open(fileNameC, 'w')
    except IOError:
        logging.debug("Could not open input file %s" % (fileNameC))
        return

    try:
        fileH = open(fileNameH, 'w')
    except IOError:
        logging.debug("Could not open input file %s" % (fileNameH))
        return

    addHeader(fileC, fileNameC, brief, date)
    
    addSection(fileC, "Macro declarations")
    addSection(fileC, "Variable declarations")
    addSection(fileC, "Prototype declarations")
    addSection(fileC, "Code")    
    
    addHeader(fileH, fileNameH, brief, date)
    
    addSection(fileH, "Macro declarations")
    addSection(fileH, "Variable declarations")
    addSection(fileH, "Function declarations")
    
    fileC.close()
    fileH.close()

if __name__ == "__main__":
    logging.basicConfig(level=logging.DEBUG)
    
    # create parser object
    parser = OptionParser(usage)                      

    # options table
#    parser.add_option("-i","--infile",        action="store", dest="infile",      type="string", help="Input file")
#    parser.add_option("-o","--outfile",       action="store", dest="outfile",     type="string", help="Output file")
#    parser.add_option("-b","--ignore",        action="store", dest="ignoreBytes", type="int",    help="Nr of bytes to ignore in begining",  default=0)
#    parser.add_option("-e","--endian",        action="store", dest="endian",      type="string", help="Endian [l, b]",                      default='l')
#    parser.add_option("-a","--arrayname",     action="store", dest="arrayName",   type="string", help="Name of array",                      default='')
    parser.add_option("-n","--newmodule", action="store_true", dest="newmodule",         help="Create new C and H file",                      default=False)
    
     # parse options
    (options, args) = parser.parse_args()              
    
    if options.newmodule:
        newModule()
        
