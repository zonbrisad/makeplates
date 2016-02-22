#/usr/bin/python3
# -----------------------------------------------------------------------
# 
# Convert binary file to a hex encoded array for inclusion in C projects
#
# File:   bin2array.py
# Author: Peter Malmberg <peter.malmberg@gmail.com>
# Date:   2016-02-19
# Version: 1.2
# Python:  >=3
# 
# -----------------------------------------------------------------------
# History
#
# Todo 
#   - C++ support

import parser
import os
import struct
import logging
import argparse

def readChunk(fd, size, nullTerminate):
    buf = fd.read(size)
    
    if len(buf)<size and nullTerminate:
        buf = buf + "0x00"
        
    return buf

class BinToArray:
    def __init__(self):
        pass
    
    def ConvertFileToArray(self, strInFile, strOutFile, integerSize, ignoreBytes, endianNess, arrayName, nullTerminate, append):
        """ Reads binary file at location strInFile and writes out a C array of hex values
        Parameters -
        strInFile - Path and filename of binary file to convert
        strOutFile - Path and filename of output. Suggested extension is .c or .cpp
        integerSize - Size in bytes of output array elements. Array generated is always
        of type uint8, uint16, uint32. These types would need to be defined using
        typedef if they don't exist, or the user can replace the type name with the
        appropriate keyword valid for the compiler size conventions
        ignoreBytes - Number of bytes to ignore at the beginning of binary file. Helps
        strip out file headers and only encode the payload/data.
        endianNess - Only used for integerSize of 2 or 4. 'l' for Little Endian, 'b' for
        Big Endian
        append - append to existing file
        """
        # Check integerSize value
        if integerSize not in (1, 2, 4):
            logging.debug("Integer Size parameter must be 1, 2 or 4")
            return
        # endif
        
        # Open input file
        try:
            fileIn = open(strInFile, 'rb')
        except IOError:
            logging.debug("Could not open input file %s" % (strInFile))
            return
        # end try
        
        # Open output file
        try:
            if (append>0):
                fileOut = open(strOutFile+'.c','a')     # append to file
            else:
                fileOut = open(strOutFile+'.c','w')      # overwrite file
                
        except IOError:
            logging.debug("Could not open output file %s" % (strOutFile))
            return
        # end try
            
        # Open include file
        try:
            if (append>0):
                fileInclude = open(strOutFile+'.h','a')     # append to file
            else:
                fileInclude = open(strOutFile+'.h','w')      # overwrite file
                
                #            fileInclude = open(strOutFile+'.h','w')
        except IOError:
            logging.debug("Could not open output file %s" % (strOutFile))
            return
        # end try
        
        # Start array definition preamble
        inFileName = os.path.basename(strInFile)
        
        strVarType = "uint%d_t" % (integerSize * 8)
        
        if not append:
            fileOut.write("#include <stdint.h>\n\n")
            
        # if no arrayname is given use filename
        if arrayName=='':
            spl = strInFile.split('.')
            arrayName = spl[0] + '_' + spl[1]
            
                
        fileOut.write("// Array representation of binary file %s\n" % (inFileName))
        fileOut.write("%s %s[] = {\n" % (strVarType,arrayName))
                
                
        if not append:
            fileInclude.write("/**\n")
            #fileInclude.write(" * Array representation of binary file %s\n" % (inFileName))
            fileInclude.write(" *\n")
            fileInclude.write(" */\n\n")
            fileInclude.write("#include <stdint.h>\n\n")
            
        fileInclude.write("extern %s %s[];\n\n" % (strVarType,arrayName))
                    
        # Convert and write array into C file
        fileIn.seek(ignoreBytes)
        if integerSize == 1:
            bufChunk = fileIn.read(20)
            #bufChunk = readChunk(fileIn, 20, nullTerminate)
            print(bufChunk)
            #print "Length ", len(bufChunk)
            #if len(bufChunk) < 20 and nullTerminate:
            #    bufChunk = bufChunk + "0x00"
                
                
            while bufChunk:
                fileOut.write("        ")
                for byteVal in bufChunk:
                    print(byteVal)
                    #fileOut.write("0x%02x, " % ord(byteVal))
                    fileOut.write("0x%02x, " % byteVal)
                # end for
                    
                fileOut.write("\n")
                bufChunk = fileIn.read(20)
            # end while
        else:
            if   endianNess == 'l' and integerSize == 2:
                endianFormatter = '<H'
                maxWordsPerLine = 10
            elif endianNess == 'l' and integerSize == 4:
                endianFormatter = '<L'
                maxWordsPerLine = 6
            elif endianNess == 'b' and integerSize == 2:
                endianFormatter = '>H'
                maxWordsPerLine = 10
            elif endianNess == 'b' and integerSize == 4:
                endianFormatter = '>L'
                maxWordsPerLine = 6
            # endif
            bufChunk = fileIn.read(integerSize)
            i = 0
            fileOut.write("        ")
            while bufChunk != '':
                wordVal = struct.unpack(endianFormatter, bufChunk)
                if integerSize == 2:
                    fileOut.write("0x%04x, " % wordVal)
                else:
                    fileOut.write("0x%08x, " % wordVal)
                # endif
                i += 1
                if i == maxWordsPerLine:
                    fileOut.write("\n        ")
                    i = 0
                # endif
                bufChunk = fileIn.read(integerSize)
            # end while
        # end if
        
        # nullterminate if wanted
        if (nullTerminate):
            fileOut.write("0x0");
            
        # Close array definition
        fileOut.write("};\n")
        fileIn.close()
        fileOut.close()
        fileInclude.close()
        
if __name__ == "__main__":
    logging.basicConfig(level=logging.DEBUG)
 
    # options parsing
    parser = argparse.ArgumentParser(description="File to C array converter")
    parser.add_argument("infile",  type=str, help="Input file")
    parser.add_argument("outfile", type=str, help="Output file")
    parser.add_argument("-a", "--append",  action="store_true", help="append to existing file",     default=False)
#    parser.add_argument("--licence", type=str,            help="Licence of new file", default="")
#    parser.add_argument("--author",  type=str,            help="Author of file",      default="")
#    parser.add_argument("--dir",     type=str,            help="Directory where to store file",       default=".")
    parser.add_argument("-i","--ignore",        type=int, help="Nr of bytes to ignore in begining", default=0)
    parser.add_argument("-e","--endian",        type=str, help="Endian [l, b]",                     default='l')
    parser.add_argument("-r","--arrayname",     type=str, help="Name of array",                     default='x')
    parser.add_argument("-n","--nullterminate", action="store_true",   help="nullterminate",        default=False)
    
    # parse arguments
    args = parser.parse_args()

    # create conversion object
    converter = BinToArray()                            
    
    # do the conversion
    converter.ConvertFileToArray( args.infile, args.outfile, 1, 
    args.ignore, args.endian, args.arrayname, 
    args.nullterminate, args.append)

#    print(args)
    
    exit
    
#    parser = OptionParser(usage)                      # create parser object
    
    # options table
#    parser.add_option("-i","--infile",        action="store", dest="infile",      type="string", help="Input file")
#    parser.add_option("-o","--outfile",       action="store", dest="outfile",     type="string", help="Output file")
    #    parser.add_option("-s","--integersize",   action="store", dest="integerSize", type="int",    help="Integer size = 1, 2, 4 bytes",       default=1)
#    parser.add_option("-b","--ignore",        action="store", dest="ignoreBytes", type="int",    help="Nr of bytes to ignore in begining",  default=0)
#    parser.add_option("-e","--endian",        action="store", dest="endian",      type="string", help="Endian [l, b]",                      default='l')
#    parser.add_option("-a","--arrayname",     action="store", dest="arrayName",   type="string", help="Name of array",                      default='')
#    parser.add_option("-n","--nullterminate", action="store_true", dest="nullterminate",         help="nullterminate",                      default=False)
#    parser.add_option("-p","--append",        action="store_true", dest="append",                help="append to existing file",            default=False)
    
    
#    (options, args) = parser.parse_args()               # parse options
    
    #print 'Infile       = ' + options.infile           # print the options
    #print 'Outfile      = ' + options.outfile
    #print 'Int Size     = ', options.integerSize
    #print 'Ignore bytes = ', options.ignoreBytes
    #print 'Arrayname    = ' + options.arrayName
    
#    converter = BinToArray()                            # create conversion object
    
    # do the conversion
#    converter.ConvertFileToArray( options.infile, options.outfile, 1, 
#    options.ignoreBytes, options.endian, options.arrayName, 
#    options.nullterminate, options.append)
    
