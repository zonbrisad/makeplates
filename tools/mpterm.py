#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# -----------------------------------------------------------------------
# 
# asdf sfda
#
# File:    __FILE__
# Author:  
# Date:    2017-05-29
# License: 
# Python:  >=3
# QT       5
# 
# -----------------------------------------------------------------------
# This file is generated from pyplate Python template generator.
# Pyplate is developed by
# Peter Malmberg <peter.malmberg@gmail.com>
#

# Imports -------------------------------------------------------------------

import sys
import os
import subprocess
import traceback
import logging
import argparse
from datetime import datetime, date, time
#from PyQt5.QtCore import *
#from PyQt5.QtGui import *
#from PyQt5.QtWidgets import *
#from PyQt5.QtCore import pyqtSlot
from ui_MainWindow import Ui_MainWindow
from PyQt5.QtWidgets import QApplication, QWidget, QMainWindow

from PyQt5.QtSerialPort import QSerialPort
#import PyQt5.QtSerialPort
#import PyQt5.QtSerialPortInfo


import serial
from serial.tools.list_ports import comports
from serial.tools import hexlify_codec

# Settings ------------------------------------------------------------------

# Application settings
AppName     = "__FILE__"
AppVersion  = "0.1"
AppLicense  = ""
AppAuthor   = ""
AppDesc     = "Pyplate description text"

# Code ----------------------------------------------------------------------


# Absolute path to script itself        
scriptPath = os.path.abspath(os.path.dirname(sys.argv[0]))

# Uncomment to use logfile
#LogFile     = "pyplate.log"


class MainForm(QMainWindow):
    def __init__(self, parent=None):
        super(MainForm, self).__init__(parent)
        
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        
        self.ui.pushButton.pressed.connect(self.kalle)
        self.ui.comboBox.addItem("300")
        self.ui.comboBox.addItem("600")
        self.ui.comboBox.addItem("1200")
        self.ui.comboBox.addItem("2400")
        self.ui.comboBox.addItem("4800")
        self.ui.comboBox.addItem("9600")
        self.ui.comboBox.addItem("19200")
        self.ui.comboBox.addItem("28400")
        self.ui.comboBox.addItem("57600")        
        self.ui.comboBox.addItem("115200")       
        
        self.ui.comboBox.activated.connect(self.change)
        self.ui.actionNew.triggered.connect(self.new)
        self.ui.actionExit.triggered.connect(self.quit)
        
        self.ui.plainTextEdit.setReadOnly(True)
        #self.ui.plainTextEdit.returnPressed.connect(self.kalle)
#        self.ui.plainTextEdit.textChanged.connect(self.kalle)
#        self.ui.plainTextEdit.keyPressEvent.connect(self.kalle)

        
    def keyPressEvent(e,a):
        print("A")
        
        print("  ",a.key(), "  ",a.text())
        
    def kalle(e):
        print("Kalle")
        print(e)
        
    def change(e):
        print(e.ui.comboBox.currentText())
        
    def quit(e):
        sys.exit(0)
            
    def new(e):
#        subprocess.Popen(["/usr/bin/meld", ""], shell=False)
        subprocess.Popen([scriptPath+"/aaa.py", ""], shell=False)


def findPorts():
    ports = []
    for n, (port, desc, hwid) in enumerate(sorted(comports()), 1):
        sys.stderr.write('--- {:2}: {:20} {}\n'.format(n, port, desc))
        ports.append(port)
        
def findPorts2():        
    spi =  QSerialPortInfo.availablePorts()
    print(spi)
    

def main():
#    findPorts2()
    
    app = QApplication(sys.argv)
    mainForm = MainForm()
    mainForm.show()
    sys.exit(app.exec_())
    return


# Absolute path to script itself        
scriptPath = os.path.abspath(os.path.dirname(sys.argv[0]))


# Main program handle  
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
