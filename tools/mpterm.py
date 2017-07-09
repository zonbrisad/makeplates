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
# -----------------------------------------------------------------------
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

from ui_MainWindow import Ui_MainWindow
#from PyQt5.QtWidgets import QApplication, QWidget, QMainWindow, QScrollBar, QLabel, QDialog

#from PyQt5.QtGui import QPalette, QColor
#from PyQt5.QtCore import QIODevice
#from PyQt5.QtCore import QCoreApplication
#from PyQt5.QtCore import QSettings
#from PyQt5.QtCore import Qt

from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

#from PyQt5 import QtCore, QtGui, QtWidgets


from PyQt5.QtSerialPort import QSerialPort
from PyQt5.QtSerialPort import QSerialPortInfo

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


# Definitions ---------------------------------------------------------------

class MpTerm():
    # Display modes
    Ascii    = 0
    Hex      = 1
    AsciiHex = 2
    
    # Newline modes
    Nl       = 0
    Cr       = 1
    NlCr     = 2
    
    

# Code ----------------------------------------------------------------------    
    
aboutHtml='''
<h3>About '''+AppName+'''</h3>
<br>
<b>Version: </b> '''+AppVersion+'''
<br>
<b>Author: </b>'''+AppName+'''
<br><br>
'''+AppDesc+'''
'''

class AboutDialog(QDialog):
    def __init__(self, parent = None):
        super(AboutDialog, self).__init__(parent)

        self.setWindowTitle("About " + AppName)
        self.setWindowModality(Qt.ApplicationModal)
        
        # Set dialog size. 
        self.resize(400, 300)
                                
        self.verticalLayout = QVBoxLayout(self)
        self.verticalLayout.setSpacing(2)
        #horizontalLayout.addLayout(self.verticalLayout)
        
        self.mainLayout = QHBoxLayout()
        self.mainLayout.setContentsMargins(2, 2, 2, 2)
        self.mainLayout.setSpacing(2)

        self.buttonLayout = QHBoxLayout()
        self.buttonLayout.setContentsMargins(2, 2, 2, 2)
        self.buttonLayout.setSpacing(2)

        self.setLayout(self.verticalLayout)
                
        # TextEdit
        self.textEdit = QTextEdit(self)
        self.textEdit.setReadOnly(True)
        self.verticalLayout.addWidget(self.textEdit)

        # Buttonbox
        self.buttonBox = QDialogButtonBox(self)
        self.buttonBox.setOrientation(Qt.Horizontal)
        self.buttonBox.setStandardButtons( QDialogButtonBox.Ok | QDialogButtonBox.Cancel )
        self.buttonBox.accepted.connect(self.accept)
        self.buttonBox.rejected.connect(self.reject)
        self.verticalLayout.addWidget(self.buttonBox)
        
        self.textEdit.insertHtml(aboutHtml)
        
    @staticmethod
    def about(parent = None):
        dialog = AboutDialog(parent)
        result = dialog.exec_()
        return (result == QDialog.Accepted)
    
settings = { 'alias':str,     
             'port':   str,  
             'bitrate':str,  
             'bits':  int,   
             'parity':str,   
             'stopbits':int, 
             }
             
#print(settings)
    
class mpProfile():
    def __init__(self, group):
        self.settings = QSettings(AppOrg, AppName)
        self.group    = group
        self.setDefaults()
        
    def setDefaults(self):
        self.alias       = "Default"
        self.port        = "ttyUSB1"
        self.bitrate     = '9600'
        self.databits    = QSerialPort.Data8
        self.parity      = QSerialPort.NoParity
        self.stopbits    = QSerialPort.OneStop
        self.flowcontrol = QSerialPort.NoFlowControl
        self.display     = MpTerm.Ascii

    def load(self):
        self.settings.sync()
        self.settings.beginGroup(self.group)
        self.alias       = self.settings.value("alias",       type=str)
        self.port        = self.settings.value("port",        type=str)
        self.bitrate     = self.settings.value("bitrate",     type=str)
        self.databits    = self.settings.value("databits",    type=str)
        self.parity      = self.settings.value("parity",      type=str)
        self.stopbits    = self.settings.value("stopbits",    type=str)
        self.flowcontrol = self.settings.value("flowcontrol", type=str)
        self.display     = self.settings.value("display",     type=str)
        self.settings.endGroup()
        
        self.print()
        
    def print(self):
        print("Port:     ", self.port)
        print("Bitrate:  ", self.bitrate)
        
    def write(self):
        self.settings.beginGroup(self.group)
        self.settings.setValue("alias",       self.alias)
        self.settings.setValue("port",        self.port)
        self.settings.setValue("bitrate",     self.bitrate)
        self.settings.setValue("databits",    self.databits)
        self.settings.setValue("parity",      self.parity)
        self.settings.setValue("stopbits",    self.stopbits)
        self.settings.setValue("flowcontrol", self.flowcontrol)
        self.settings.setValue("display",     self.display)
        self.settings.endGroup()
        self.settings.sync()
        return

class MainForm(QMainWindow):
    def __init__(self, parent=None):
        super(MainForm, self).__init__(parent)
        
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        
        self.rxLabel = QLabel("")
        self.txLabel = QLabel("")
        self.ui.statusbar.addWidget(self.rxLabel)
        self.ui.statusbar.addWidget(self.txLabel)
        
        self.rxCnt = 0
        self.txCnt = 0
               
        self.serial = QSerialPort()
        self.serial.readyRead.connect(self.read)
        
        self.updatePorts()
        
        self.ui.cbStopBits.addItem("1",   QSerialPort.OneStop)
        self.ui.cbStopBits.addItem("1.5", QSerialPort.OneAndHalfStop)
        self.ui.cbStopBits.addItem("2",   QSerialPort.TwoStop)

        self.ui.cbBits.addItem("5", QSerialPort.Data5)
        self.ui.cbBits.addItem("6", QSerialPort.Data6)
        self.ui.cbBits.addItem("7", QSerialPort.Data7)
        self.ui.cbBits.addItem("8", QSerialPort.Data8)
                
        self.ui.cbParity.addItem("None", QSerialPort.NoParity)
        self.ui.cbParity.addItem("Odd",  QSerialPort.OddParity)
        self.ui.cbParity.addItem("Even", QSerialPort.EvenParity)
        
        self.ui.cbFlowControl.addItem("No Flow Control",  QSerialPort.NoFlowControl )
        self.ui.cbFlowControl.addItem("Hardware Control", QSerialPort.HardwareControl )
        self.ui.cbFlowControl.addItem("Software Control", QSerialPort.SoftwareControl )

        self.ui.cbBitrate.addItem('300',   300    )
        self.ui.cbBitrate.addItem('600',   600    )
        self.ui.cbBitrate.addItem("1200",  1200   )
        self.ui.cbBitrate.addItem("2400",  2400   )
        self.ui.cbBitrate.addItem("4800",  4800   )
        self.ui.cbBitrate.addItem('9600',  9600   )
        self.ui.cbBitrate.addItem("19200", 19200  )
        self.ui.cbBitrate.addItem("28400", 28400  )
        self.ui.cbBitrate.addItem("57600", 57600  )        
        self.ui.cbBitrate.addItem("115200",115200 )
        
        self.ui.cbNewline.addItem("nl",    0 )
        self.ui.cbNewline.addItem("cr",    1 )
        self.ui.cbNewline.addItem("cr+nl", 2 )
        
        self.ui.cbDisplay.addItem("Ascii",       MpTerm.Ascii    )
        self.ui.cbDisplay.addItem("Hex",         MpTerm.Hex      )
        self.ui.cbDisplay.addItem("Hex + Ascii", MpTerm.AsciiHex )
        
        
        self.ui.cbBitrate.activated.connect(self.setBitrate)        
        self.ui.cbStopBits.activated.connect(self.setStopBits)
        self.ui.cbBits.activated.connect(self.setBits)
        self.ui.cbParity.activated.connect(self.setParity)
        self.ui.cbFlowControl.activated.connect(self.setFlowControl)
        
        
        self.ui.actionNew.triggered.connect(self.new)
        self.ui.actionExit.triggered.connect(self.exitProgram)
        self.ui.actionClear.triggered.connect(self.actionClear)
        self.ui.actionAbout.triggered.connect(self.about)

        self.ui.pushButton.pressed.connect(self.testing)
        self.ui.pbOpen.pressed.connect(self.openPort)
        
        self.ui.bpTest1.pressed.connect(self.test1)
        self.ui.bpTest2.pressed.connect(self.test2)

        self.ui.textEdit.setReadOnly(True)
        
        self.mpDefault = mpProfile("Default")
        self.mpDefault.load()
        self.loadProfile(self.mpDefault)
                
        
 #       self.ui.textEdit.insertPlainText("Kalle")
 #       self.ui.textEdit.appendHtml('<code>')
#        self.ui.textEdit.insertPlainText("Nisse")
#        self.ui.textEdit.appendHtml('<b>Bold')
#        self.ui.textEdit.insertPlainText("Bold")
#        self.ui.textEdit.appendHtml("Bold")
        
        self.ui.textEdit.appendHtml('<font face="verdana" color="green">')
        self.ui.textEdit.setMaximumBlockCount(200)
        
        # Some debug widgets (comment out for production)
        self.ui.gbDebug.hide()
        
        self.updateUi()
        
    def about(self):
        AboutDialog.about()


    def actionClear(self):
        self.ui.textEdit.clear()
        
    def test1(self):
        self.send(b'ABCD')
        return
    
    def test2(self):
        self.send(b'0123456789')
        return
        
    def testing(self):
#        p = self.ui.plainTextEdit.palette()
#        p = QPalette()
#        c = QColor("red")
#        p.setColor( QPalette.Text, c )
#        self.ui.plainTextEdit.setPalette(p)
#        self.ui.plainTextEdit.appendPlainText("A")
        #print(chr(65))        
        x = b'\n'
#        print(x.decode("utf-8"))
#        self.ui.plainTextEdit.appendPlainText(x.decode("utf-8"))
#        self.ui.plainTextEdit.appendPlainText(x.decode("utf-8"))
#        self.ui.plainTextEdit.insertPlainText(x.decode("utf-8"))
        #QString notifyHtml = "<font color=\"Lime\">";

        self.showMessage("Nisse")
        self.scrollDown()
        
                
    # scroll down to bottom
    def scrollDown(self):
#        vsb = self.ui.plainTextEdit.verticalScrollBar()
#        vsb.setValue(vsb.maximum())
        
        vsb = self.ui.textEdit.verticalScrollBar()
        vsb.setValue(vsb.maximum())
        
    # Show message in status bar    
    def message(self, msg):
        self.ui.statusbar.showMessage(msg, 4000)
        # uncomment for debugging
        #print(msg)
        
        
        

    def read(self):
        data = self.serial.readAll()
#        self.ui.plainTextEdit.insertPlainText(data.at(0))
        self.ui.textEdit.moveCursor (QTextCursor.End);
        DisplayMode = self.ui.cbDisplay.itemData(self.ui.cbDisplay.currentIndex())
                
        if DisplayMode == MpTerm.Ascii:
            for i in range(0, data.count()):
                ch = data.at(i)

                if ch == '\n':
                    #self.ui.textEdit.insertHtml('<br>')
                    #                self.ui.textEdit.appendHtml('<br>')
                    self.ui.textEdit.insertPlainText('\n')
                    #                    self.ui.textEdit.appendHtml('<br>')
                    
                    #                 x=1
                else:
                    #self.ui.textEdit.insertHtml('<font color="White">'+ch)
                    #self.ui.textEdit.appendHtml(ch)
                    #self.ui.textEdit.insertPlainText(ch)
                    self.ui.textEdit.insertPlainText(ch);
                    
        elif DisplayMode == MpTerm.Hex:
#            s = 'xx xx xx xx xx xx xx xx xx xx xx xx xx xx xx xx xx xx xx'
            s = ''
            for i in range(0, data.count()):
                ch = data.at(i)                
                s = s + '{0:02x} '.format(ord(ch))
                
            self.ui.textEdit.insertPlainText(s)
            #self.ui.textEdit.insertPlainText( '{0:02x} '.format(ord(ch)))
            
                    
        self.ui.textEdit.moveCursor(QTextCursor.End);
            
        self.scrollDown()
        
        print("Total: ",self.rxCnt," Data: ", data.count())
        self.rxCnt += data.count()
        self.updateUi()
        
        
    def send(self, data):
        if (self.serial.isOpen()):
            self.serial.write(data)
            self.txCnt += len(data)
            self.updateUi()
            
    def sendStr(self, str):
        return
        
    def keyPressEvent(self, a):
        print("  ",a.key(),"  ",a.text(), "  ord: ",ord(a.text()))
        
        if a.key() == Qt.Key_Escape:
            print("Escape")
            return

        if (a.key() == Qt.Key_Enter) or (a.key() == Qt.Key_Return):
            self.send(b'\n')
            print("Enter")
            return

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
        #msg = bytearray([ a.key() ])
        msg = bytearray([ ord(a.text()) ])
        self.send(msg)
        
    def kalle(self):
#        self.ui.plainTextEdit.appendPlainText("A")
        print("Kalle")
        
    def updateUi(self):
        if (self.serial.isOpen()):
            self.setWindowTitle('MpTerm  /dev/'+self.ui.cbPort.currentText() + '  '+self.ui.cbBitrate.currentText())
            self.ui.pbOpen.setText("Close")
            self.ui.cbPort.setEnabled(0)
        else:
            self.setWindowTitle('MpTerm')
            self.ui.pbOpen.setText("Open")
            self.ui.cbPort.setEnabled(1)
            
        self.rxLabel.setText('RX: '+str(self.rxCnt))
        self.txLabel.setText('TX: '+str(self.txCnt))            

    def openPort(self):
        if (self.serial.isOpen()):
            self.serial.close()
            self.updateUi() 
            return

        self.message("Opening port")
        self.initPort()
        self.serial.clear()
        self.serial.open(QIODevice.ReadWrite)
        self.updateUi() 

    def initPort(self):
        self.setPort()
        self.setBitrate()
        self.setBits()
        self.setStopBits()
        self.setParity()
        self.setFlowControl()
        
    def setPort(self):
        self.serial.setPortName("/dev/"+self.ui.cbPort.currentText())
        
    def setBitrate(self):
        self.serial.setBaudRate( self.ui.cbBitrate.currentData())
        
    def setStopBits(self):
        self.serial.setStopBits( self.ui.cbStopBits.currentData())
        
    def setBits(self):
        self.serial.setDataBits( self.ui.cbBits.currentData())

    def setParity(self):
        print("a")
        self.serial.setParity( self.ui.cbParity.currentData())
    
    def setFlowControl(self):
        self.serial.setFlowControl( self.ui.cbFlowControl.currentData())

    def saveSetting(self):        
#        self.mpDefault.write()
        return
    
    def loadSettings(self):
        return

        
    def setCbText(self, cb, txt):
        a = cb.findText(txt)
        if a == -1:
            cb.setCurrentIndex(0)
        else:
            cb.setCurrentIndex(a)
    
    def setCbData(self, cb, data):
        a = cb.findData(data)
        if a == -1:
            cb.setCurrentIndex(0)
        else:
            cb.setCurrentIndex(a)

    def saveProfile(self, prof):
        prof.port        = self.ui.cbPort.currentText()
        prof.bitrate     = self.ui.cbBitrate.currentText()
        prof.databits    = self.ui.cbBits.currentData()
        prof.stopbits    = self.ui.cbStopBits.currentData()
        prof.parity      = self.ui.cbParity.currentData()
        prof.flowcontrol = self.ui.cbFlowControl.currentData()
        prof.display     = self.ui.cbDisplay.currentData()
        prof.write()
        
        
    def loadProfile(self, prof):
        self.setCbText(self.ui.cbPort,        prof.port)
        self.setCbText(self.ui.cbBitrate,     prof.bitrate)
        self.setCbData(self.ui.cbBits,        prof.databits)
        self.setCbData(self.ui.cbStopBits,    prof.stopbits)
        self.setCbData(self.ui.cbParity,      prof.parity)
        self.setCbData(self.ui.cbFlowControl, prof.flowcontrol)
        self.setCbData(self.ui.cbDisplay,     prof.display)
        
        
    def exitProgram(self, e):
        self.saveProfile(self.mpDefault)
        
        self.serial.close()
        self.close()
    
    def updatePorts(self):
        ports = QSerialPortInfo.availablePorts()
        for port in ports:
            self.ui.cbPort.addItem(port.portName())
            
    def new(self):
        subprocess.Popen([scriptPath+"/mpterm.py", ""], shell=False)
        
    def openFile(self):
        dlg = QFileDialog()
        dlg.setFileMode(QFileDialog.AnyFile)
        dlg.setFilter("Text files (*.txt)")
        filenames = QStringList()


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
