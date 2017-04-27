#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# -----------------------------------------------------------------------
# 
# C/C++ template generator
#
# File:   ctemplate.py
# Author: Peter Malmberg <peter.malmberg@gmail.com>
# Date:   2016-02-19
# Version: 0.2
# Python:  >=3
# Licence: MIT
# 
# -----------------------------------------------------------------------
# History
#
# Todo 
#
# Imports -------------------------------------------------------------------

import sys
import os 
import traceback
import logging
import argparse
from datetime import datetime, date, time

# Settings ------------------------------------------------------------------


AppName     = "pyplate"
AppVersion  = "0.1"
AppLicence  = "MIT"
AppAuthor   = "Peter Malmberg <peter.malmnerg@gmail.com>"

# Uncomment to use logfile
#LogFile     = "pyplate.log"

# Code ----------------------------------------------------------------------
def query_yn(question, default="yes"):
    valid = {"yes": True, "y": True, "ye": True, "no": False, "n": False}
    if default is None:
        prompt = " [y/n] "
    elif default == "yes":
        prompt = " [Y/n] "
    elif default == "no":
        prompt = " [y/N] "
    else:
        raise ValueError("invalid default answer: '%s'" % default)
    
    while True:
        sys.stdout.write(question + prompt)
        choice = input().lower()
        if default is not None and choice == '':
            return valid[default]
        elif choice in valid:
            return valid[choice]
        else:
            sys.stdout.write("Please respond with 'yes' or 'no' (or 'y' or 'n').\n")

            
def addHeader(file, fileName, brief, date, author, licence):
    file.write( 
    "/**\n"
    " *---------------------------------------------------------------------------\n"
    " * @brief   "+brief+"\n"
    " *\n"
    " * @file    "+fileName+"\n"
    " * @author  "+author+"\n"
    " * @date    "+date+"\n"
    " * @licence "+licence+"\n"
    " *\n"
    " *---------------------------------------------------------------------------\n"
    " */\n\n")
 

def addSection(file, desc):
    line = '-' * (71 - len(desc))
    file.write("// " + desc + " " + line + "\n\n")
    
def addSection2(file, desc):
    file.write(                \
    "/**\n"                    \
    " * "+desc+"\n"            \
    " *------------------------------------------------------------------\n" \
    " */\n\n") 
    

def addSentinelBegin(file, sentinel):
    file.write(                     \
    "#ifndef "+sentinel+"_H\n"      \
    "#define "+sentinel+"_H\n\n") 

    
def addSentinelEnd(file):
    file.write("#endif\n\n")

def addCppSentinel(file):
    file.write(              \
    "#ifdef __cplusplus\n"   \
    "extern \"C\" {\n"       \
    "#endif\n\n")
     
def addCppSentinelEnd(file): 
    file.write(                        \
    "#ifdef __cplusplus\n"             \
    "} //end brace for extern \"C\"\n" \
    "#endif\n")
  

def addMethod(file, className, methodName): 
  file.write(className+"::"+methodName+"() {\n")
  file.write("\n}\n\n")


def addClass(file, className):
  file.write("class "+className+" {\n")
  file.write("    public:\n")    
  file.write("      "+className+"();\n")
  file.write("}\n")

def addInclude(file, includeFile):  
  file.write("#include <"+includeFile+">\n")  
    
def addCIncludes(file):
    addInclude(file, "stdio.h")
    addInclude(file, "stdlib.h")
    addInclude(file, "sys/types.h")
    addInclude(file, "unistd.h")
    addInclude(file, "signal.h")
    addInclude(file, "string.h")
    addInclude(file, "errno.h")
  
def addGTKIncludes(file):
    addInclude(file, "gtk/gtk.h")
  
def addQtIncludes(file):
    addInclude(file, "QApplication")
    addInclude(file, "QDebug")
    addInclude(file, "QMainWindow")
    addInclude(file, "QPushbutton")
    addInclude(file, "QLabel")
#    addInclude(file, "QtCore/QCoreApplication")
        
def addMain(file):
  file.write("int main(int argc, char *argv[]) {\n\n")
  file.write("  return 0;\n")    
  file.write("}\n")
  

def newFile(dir, fileName):
  # Open files to be generated
  try:
    file = open(dir+"/"+fileName, 'w')
    return file
  except IOError:
    logging.debug("Could not open template file %s" % (fileName))
    exit()


def askInfo(module):
    print("Creating new "+module)
    fName = input("Enter "+module+" name(no extention:>")
    brief = input("Enter brief description:> ")
    
    date = datetime.now().strftime("%Y-%m-%d")    
    return fName, brief, date
  
def newModule(dir, author, licence):
    
    # ask for some information
    fName, brief, date = askInfo("C module")

    main = query_yn("Add main() function", "no")
    if (main):
        gtk= query_yn("GTK project", "no")
    
    
    fileNameC = fName + ".c"
    fileNameH = fName + ".h"

    # Open files to be generated
    fileC = newFile(dir, fileNameC)
    fileH = newFile(dir, fileNameH)

    # Populate C file
    addHeader(fileC, fileNameC, brief, date, author, licence)

    addSection(fileC, "Includes")
    
    if (main):
        addCincludes(fileC)
    
    fileC.write("#include \""+fileNameH+"\"\n\n");
    
    addSection(fileC, "Macros")
    addSection(fileC, "Variables")
    addSection(fileC, "Prototypes")
    addSection(fileC, "Code")    

    if (main):
        addMain(fileC)

    
    # Populate H file
    addHeader(fileH, fileNameH, brief, date, author, licence)
    addSentinelBegin(fileH, fName.upper())
    addCppSentinel(fileH)
    addSection(fileH, "Includes")
    addSection(fileH, "Macros")
    addSection(fileH, "Typedefs")
    addSection(fileH, "Variables")
    addSection(fileH, "Prototypes")
    addCppSentinelEnd(fileH)
    addSentinelEnd(fileH)
 
    
    
    # Close down files
    fileC.close()
    fileH.close()
    
def newClass(dir, author, licence):

    # ask for some information
    fName, brief, date = askInfo("C++ Class")

    fileNameC = fName + ".cpp"
    fileNameH = fName + ".h"

    # Open files to be generated
    fileC = newFile(dir, fileNameC)
    fileH = newFile(dir, fileNameH)

    # Populate C++ file
    addHeader(fileC, fileNameC, brief, date, author, licence)
    addSection(fileC, "Includes")
    fileC.write("#include \""+fileNameH+"\"\n\n");
    
    addSection(fileC, "Macros")
    addSection(fileC, "Variables")
    addSection(fileC, "Prototypes")
    addSection(fileC, "Code")    
    
    addMethod(fileC, fName, fName)
    
    # Populate H file
    addHeader(fileH, fileNameH, brief, date, author, licence)

    addSentinelBegin(fileH, fName.upper())    
    addSection(fileH, "Includes")
    addSection(fileH, "Macros")
    addSection(fileH, "Typedefs")
    addSection(fileH, "Variables")
    
    addClass(fileH, fName)
      
    addSentinelEnd(fileH)
    
    # Close down files
    fileC.close()
    fileH.close()

def printInfo():
    print("Script name    " + AppName)
    print("Script version " + AppVersion)
    print("Script path    " + os.path.realpath(__file__))

lasse="""
    signal(SIGINT, sigInt);
    signal(SIGHUP, sigHup);

  

// GTK Glade --------------------------------------------------------------------

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "gtkTest.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window2"));
    gtk_builder_connect_signals(builder, NULL);

    //g_object_unref(builder);

    GtkWidget *w;
    GtkTextIter iter;
    w = gtk_builder_get_object(builder, "textview2");
    //gtk_text_view_set_buffer(w, buf);
    buf = gtk_text_view_get_buffer(w);
    gtk_text_buffer_get_iter_at_offset(buf, &iter, 0);
    gtk_text_buffer_insert(buf, &iter, "Kalle", -1);
"""

qtExample="""
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
         
    return app.exec();
"""



print(lasse)

def main():
    logging.basicConfig(level=logging.DEBUG)
    
    # options parsing
    parser = argparse.ArgumentParser(description="C/C++ template generator")
    parser.add_argument("--newc",     action="store_true", help="Create a new C and H file set")
    parser.add_argument("--newcpp",   action="store_true", help="Create a new C++ and H file set")
    parser.add_argument("--newclass", action="store_true", help="Create a new C++ class")
    parser.add_argument("--licence",  type=str,            help="Licence of new file", default="")
    parser.add_argument("--author",   type=str,            help="Author of file",      default="")
    parser.add_argument("--dir",      type=str,            help="Directory where to store file",  default=".")
    
    args = parser.parse_args()
    
    if args.newc:
        newModule(args.dir, args.author, args.licence)
        exit
        
    if args.newclass:
        newClass(args.dir, args.author, args.licence)
        exit
        
    if args.newcpp:
        print("To be implemented.")
        exit

    exit    

if __name__ == "__main__":
    try:
        main()
        sys.exit(0)
    except KeyboardInterrupt as e: # Ctrl-C
        raise e
    except SystemExit as e:        # sys.exit()
        raise e
    except Exception as e:
        print('ERROR, UNEXPECTED EXCEPTION')
        print(str(e))
        traceback.print_exc()
        os._exit(1)
