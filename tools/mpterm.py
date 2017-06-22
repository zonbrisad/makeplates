#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# -----------------------------------------------------------------------
# 
# asdf sfda
#
# File:    mpterm.py
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
#
# pyuic5 mpTerminal.ui -o ui_MainWindow.py
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
from PyQt5.QtWidgets import QApplication, QWidget, QMainWindow, QScrollBar, QLabel

from PyQt5.QtGui import QPalette, QColor

from PyQt5.QtCore import QIODevice
from PyQt5.QtCore import QCoreApplication
from PyQt5.QtCore import QSettings
from PyQt5.QtCore import Qt


from PyQt5.QtSerialPort import QSerialPort
from PyQt5.QtSerialPort import QSerialPortInfo
#import PyQt5.QtSerialPort
#import PyQt5.QtSerialPortInfo


#import serial
#from serial.tools.list_ports import comports
#from serial.tools import hexlify_codec

# Settings ------------------------------------------------------------------

# Application settings
AppName     = "mpterm"
AppVersion  = "0.1"
AppLicense  = ""
AppAuthor   = ""
AppDesc     = "Pyplate description text"
AppOrg      = "Mudderverk"
AppDomain   = ""

# Qt settings
QCoreApplication.setOrganizationName(AppOrg)
QCoreApplication.setOrganizationDomain(AppDomain)
QCoreApplication.setApplicationName(AppName)

# Code ----------------------------------------------------------------------

htmlTable='''
<table style="width:100%">
<tr>
<th>Firstname</th>
<th>Lastname</th> 
<th>Age</th>
</tr>
<tr>
<td>Jill</td>
<td>Smith</td> 
<td>50</td>
</tr>
<tr>
<td>Eve</td>
<td>Jackson</td> 
<td>94</td>
</tr>
</table>
'''
htmlBlock='''
<div style="background-color:blue;color:red;padding:20px;">
<h2>London</h2>
<p>London is the capital city of England. It is the most populous city in the United Kingdom, with a metropolitan area of over 13 million inhabitants.</p>
<p>Standing on the River Thames, London has been a major settlement for two millennia, its history going back to its founding by the Romans, who named it Londinium.</p>
</div> 
'''

htmlList='''
<ol>  
  <li>Coffee</li> 
  <li>Tea</li>  
  <li>Milk</li>  
</ol>
'''
htmlStyle='''
<h2 style="background-color:blue;color:white">
Background-color set by using blue
</h2>'''

htmlFont='''
<font color="Lime">Kalle
<font color="Aqua">Nisse
Normal
<b>Bold</b>
<i>Italic</i>
<h1>Heading 1</h1>
<h2>Heading 2</h2>
<h3>Heading 3</h3>
<h4>Heading 4</h4>
<a href="www.svd.se">Svenska Dagbladet</a>
'''
htmlCss='''
h1 {
    color: white;
}
h2 {
    color: red;
}
h3 {
    color: green;
}
h4 {
    color: blue;
}
'''


class mpProfile():
    def __init__(self, group):
        self.settings = QSettings(AppOrg, AppName)
        self.group    = group
        self.setDefaults()
    
    def setDefaults(self):
        self.alias    = "Default"
        self.port     = "ttyUSB1"
        self.bitrate  = "9600"
        self.bits     = 8
        self.parity   = "none"
        self.stopbits = 0
        
    def load(self):
        self.settings.sync()
        self.settings.beginGroup(self.group)
        self.alias    = self.settings.value("alias",    type=str)
        self.port     = self.settings.value("port",     type=str)
        self.bitrate  = self.settings.value("bitrate",  type=str)
        self.bits     = self.settings.value("bits",     type=int)
        self.parity   = self.settings.value("parity",   type=str)
        self.stopbits = self.settings.value("stopbits", type=int)
        self.settings.endGroup()
        
#    def print(self):
#        print("Port:     ", self.port)
#        print("Bitrate:  ", self.bitrate)
        
    def write(self):
        self.settings.beginGroup(self.group)
        self.settings.setValue("alias",    self.alias)
        self.settings.setValue("port",     self.port)
        self.settings.setValue("bitrate",  self.bitrate)
        self.settings.setValue("bits",     self.bits)
        self.settings.setValue("parity",   self.parity)
        self.settings.setValue("stopbits", self.stopbits)
        self.settings.endGroup()
        self.settings.sync()
        return

class MainForm(QMainWindow):
    def __init__(self, parent=None):
        super(MainForm, self).__init__(parent)
        
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
                
        self.mpDefault = mpProfile("Default")
#        mpDefault.write()
        self.mpDefault.load()
#        mpDefault.print()
        
        self.rxLabel = QLabel("")
        self.txLabel = QLabel("")
        self.ui.statusbar.addWidget(self.rxLabel)
        self.ui.statusbar.addWidget(self.txLabel)
        
        self.rxCnt = 0
        self.txCnt = 0
               
        self.serial = QSerialPort()
        self.serial.readyRead.connect(self.read)
        
        self.updatePorts()
        
        self.ui.cbStopBits.addItem("1")
        self.ui.cbStopBits.addItem("2")
        
        self.ui.cbBits.addItem("6")
        self.ui.cbBits.addItem("7")
        self.ui.cbBits.addItem("8")
        self.ui.cbBits.addItem("9")
        
        self.ui.cbParity.addItem("None")
        self.ui.cbParity.addItem("Odd")
        self.ui.cbParity.addItem("Even")
        
        self.ui.cbBitrate.addItem("300")
        self.ui.cbBitrate.addItem("600")
        self.ui.cbBitrate.addItem("1200")
        self.ui.cbBitrate.addItem("2400")
        self.ui.cbBitrate.addItem("4800")
        self.ui.cbBitrate.addItem("9600")
        self.ui.cbBitrate.addItem("19200")
        self.ui.cbBitrate.addItem("28400")
        self.ui.cbBitrate.addItem("57600")        
        self.ui.cbBitrate.addItem("115200")
        
        
        self.ui.cbBitrate.activated.connect(self.bitrateChange)
        
        self.ui.actionNew.triggered.connect(self.new)
        self.ui.actionExit.triggered.connect(self.exitProgram)
        self.ui.actionClear.triggered.connect(self.actionClear)

        self.ui.pushButton.pressed.connect(self.testing)
        self.ui.pbOpen.pressed.connect(self.openPort)
        

        self.ui.plainTextEdit.setReadOnly(True)
        
        self.ui.textEdit.setReadOnly(True)
        #self.ui.plainTextEdit.returnPressed.connect(self.kalle)
#        self.ui.plainTextEdit.textChanged.connect(self.kalle)
#        self.ui.plainTextEdit.keyPressEvent.connect(self.kalle)
        self.updateUi()

    def saveSetting(self):
        return
    
    def loadSettings(self):
        return


    def actionClear(self):
        self.ui.plainTextEdit.clear()

    def testing(self):
        p = self.ui.plainTextEdit.palette()
#        p = QPalette()
        c = QColor("red")
        p.setColor( QPalette.Text, c )
#        self.ui.plainTextEdit.setPalette(p)
#        self.ui.plainTextEdit.appendPlainText("A")
        #print(chr(65))        
        x = b'\n'
#        print(x.decode("utf-8"))
        self.ui.plainTextEdit.appendHtml(htmlFont)
        self.ui.plainTextEdit.appendHtml(htmlTable)
        self.ui.plainTextEdit.appendHtml(htmlBlock)
        self.ui.plainTextEdit.appendHtml(htmlList) 
        self.ui.plainTextEdit.appendHtml(htmlStyle)

        self.ui.textEdit.insertHtml(htmlCss)
        self.ui.textEdit.insertHtml(htmlFont)
        self.ui.textEdit.insertHtml(htmlTable)
        self.ui.textEdit.insertHtml(htmlBlock)
        self.ui.textEdit.insertHtml(htmlList) 
        self.ui.textEdit.insertHtml(htmlStyle)
        
        self.ui.textEdit.insertHtml('<font color="Lime">Kalle')
        self.ui.textEdit.insertHtml('<font color="Aqua">Nisse')
        
#        self.ui.plainTextEdit.appendPlainText(x.decode("utf-8"))
#        self.ui.plainTextEdit.appendPlainText(x.decode("utf-8"))
#        self.ui.plainTextEdit.insertPlainText(x.decode("utf-8"))
        #QString notifyHtml = "<font color=\"Lime\">";

        self.showMessage("Nisse")
        
        
        
    # scroll down to bottom
    def scrollDown(self):
        vsb = self.ui.plainTextEdit.verticalScrollBar()
        vsb.setValue(vsb.maximum())
        
    # Show message in status bar    
    def showMessage(self, msg):
        self.ui.statusbar.showMessage(msg, 4000)
        

    def read(self):
        data = self.serial.readAll()
        self.ui.plainTextEdit.insertPlainText(data.at(0))
        self.scrollDown()
        print("Total: ",self.rxCnt," Data: ", data.count())
        self.rxCnt += data.count()
        self.updateUi()
        
        
    def send(self, data):
        data = self.serial.readAll()
        print(data)
        self.txCnt += 1
        if (self.serial.isOpen()):
            self.serial.write(data)
            self.updateUi()
        
        
        
    def keyPressEvent(self, a):
        print("  ",a.key(),"  ",a.text())
        if a.key() == Qt.Key_Escape:
            print("Escape")
            return

        if (a.key() == Qt.Key_Enter) or (a.key() == Qt.Key_Return):
            self.send(b'\n')
            print("Enter")
            return

#        if a.key() == Qt.Key_Return:
#            print("Return")
#            return
            
        if a.key() == Qt.Key_Left:
            print("Left")
            return

        if a.key() == Qt.Key_Delete:
            print("Delete")
            return            

        if a.key() == Qt.Key_Insert:
            print("Insert")
            return

        if a.key() == Qt.Key_Backspace:
            print("Backspace")
            return
            
        if a.key() == Qt.Key_End:
            print("End")
            return

        if a.key() == Qt.Key_F1:
            print("F1")
            return

#        if (self.serial.isOpen()):
#        msg = bytearray([ a.key() ])
#        self.sendByte(msg)
        msg = bytearray([ a.key() ])
        self.send(msg)
        
    def kalle(self):
        self.ui.plainTextEdit.appendPlainText("A")
        print("Kalle")
        
    def updateUi(self):
        if (self.serial.isOpen()):
            self.ui.pbOpen.setText("Close")
        else:
            self.ui.pbOpen.setText("Open")
            
        self.rxLabel.setText('RX: '+str(self.rxCnt))
        self.txLabel.setText('TX: '+str(self.txCnt))
            

    def openPort(self):
        if (self.serial.isOpen()):
            self.serial.close()
            self.updateUi()
            return

        print("Open port")
        self.serial.setPortName("/dev/"+self.ui.cbPorts.currentText())
        self.serial.setBaudRate(115200)
        self.serial.open(QIODevice.ReadWrite)
        self.updateUi() 
        
    def setBitrate(self):
        print("Current bitrate: ", self.serial.baudRate)
        print(self.serial.baudRate)
        self.serial.setBaudRate(1200)
        print("New bitrate:     ", self.ui.cbBitrate.currentText())
        
    def bitrateChange(self):
        self.setBitrate()

                
    def exitProgram(self, e):
        self.serial.close()
        sys.exit(0)
    
    def updatePorts(self):
        ports = QSerialPortInfo.availablePorts()
        for port in ports:
            self.ui.cbPorts.addItem(port.portName())
            
    def new(self):
        subprocess.Popen([scriptPath+"/mpterm.py", ""], shell=False)
        
        


def findPorts():
    ports = []
    for n, (port, desc, hwid) in enumerate(sorted(comports()), 1):
        sys.stderr.write('--- {:2}: {:20} {}\n'.format(n, port, desc))
        ports.append(port)
        
def findPorts2():        
    spi = QSerialPortInfo.availablePorts()
    for p in spi:
        print(p.portName()," ", p.description(), ' ',p.systemLocation())

def settings():
    s = QSettings()
    sys.exit(0)

def mainApplication():
#    settings()
    
    app = QApplication(sys.argv)
    mainForm = MainForm()
    mainForm.show()
    sys.exit(app.exec_())
    return

def main():
    #logging.basicConfig(level=logging.DEBUG)
    mainApplication()

    # options parsing
    parser = argparse.ArgumentParser(prog=AppName, add_help = True, description=AppDesc)
    parser.add_argument('--version', action='version', version='%(prog)s '+AppVersion)
    parser.add_argument("--info",  action="store_true", help="Information about script")

    # Some examples of parameters (rename or remove unwanted parameters)
    parser.add_argument("-a",    action="store_true",       help="Boolean type argument")
    parser.add_argument("-b",    action="store",  type=str, help="String type argument",  default="HejHopp")
    parser.add_argument("-c",    action="store",  type=int, help="Integer type argument", default=42)
    parser.add_argument("-d",    action="append", type=int, help="Append values to list", dest='dlist', default=[] )
    
    args = parser.parse_args()

    if args.info:
        printInfo()
        return
    
    if args.a:
        print("Boolean argument")
        
    if args.b:
        print("String argument = " + args.b)
            
    if args.c:
        print("Integer argument = " + str(args.c) )

    if args.dlist:
        print("List = ", args.dlist )
    
        
    return


# Absolute path to script itself        
scriptPath = os.path.abspath(os.path.dirname(sys.argv[0]))

# Uncomment to use logfile
#LogFile     = "pyplate.log"

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
