# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'mpTerminal.ui'
#
# Created by: PyQt5 UI code generator 5.5.1
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(923, 530)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.centralwidget)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.verticalLayout_4 = QtWidgets.QVBoxLayout()
        self.verticalLayout_4.setSpacing(2)
        self.verticalLayout_4.setObjectName("verticalLayout_4")
        self.pbOpen = QtWidgets.QPushButton(self.centralwidget)
        self.pbOpen.setObjectName("pbOpen")
        self.verticalLayout_4.addWidget(self.pbOpen)
        self.comboBox = QtWidgets.QComboBox(self.centralwidget)
        self.comboBox.setObjectName("comboBox")
        self.verticalLayout_4.addWidget(self.comboBox)
        self.verticalLayout_6 = QtWidgets.QVBoxLayout()
        self.verticalLayout_6.setObjectName("verticalLayout_6")
        self.verticalLayout_4.addLayout(self.verticalLayout_6)
        self.formLayout = QtWidgets.QFormLayout()
        self.formLayout.setSpacing(2)
        self.formLayout.setObjectName("formLayout")
        self.label_2 = QtWidgets.QLabel(self.centralwidget)
        self.label_2.setObjectName("label_2")
        self.formLayout.setWidget(0, QtWidgets.QFormLayout.LabelRole, self.label_2)
        self.cbPort = QtWidgets.QComboBox(self.centralwidget)
        self.cbPort.setEditable(False)
        self.cbPort.setCurrentText("")
        self.cbPort.setObjectName("cbPort")
        self.formLayout.setWidget(0, QtWidgets.QFormLayout.FieldRole, self.cbPort)
        self.label_3 = QtWidgets.QLabel(self.centralwidget)
        self.label_3.setObjectName("label_3")
        self.formLayout.setWidget(1, QtWidgets.QFormLayout.LabelRole, self.label_3)
        self.cbBitrate = QtWidgets.QComboBox(self.centralwidget)
        self.cbBitrate.setObjectName("cbBitrate")
        self.formLayout.setWidget(1, QtWidgets.QFormLayout.FieldRole, self.cbBitrate)
        self.label_4 = QtWidgets.QLabel(self.centralwidget)
        self.label_4.setObjectName("label_4")
        self.formLayout.setWidget(2, QtWidgets.QFormLayout.LabelRole, self.label_4)
        self.cbStopBits = QtWidgets.QComboBox(self.centralwidget)
        self.cbStopBits.setObjectName("cbStopBits")
        self.formLayout.setWidget(2, QtWidgets.QFormLayout.FieldRole, self.cbStopBits)
        self.label_5 = QtWidgets.QLabel(self.centralwidget)
        self.label_5.setObjectName("label_5")
        self.formLayout.setWidget(3, QtWidgets.QFormLayout.LabelRole, self.label_5)
        self.cbBits = QtWidgets.QComboBox(self.centralwidget)
        self.cbBits.setObjectName("cbBits")
        self.formLayout.setWidget(3, QtWidgets.QFormLayout.FieldRole, self.cbBits)
        self.label_6 = QtWidgets.QLabel(self.centralwidget)
        self.label_6.setObjectName("label_6")
        self.formLayout.setWidget(4, QtWidgets.QFormLayout.LabelRole, self.label_6)
        self.cbParity = QtWidgets.QComboBox(self.centralwidget)
        self.cbParity.setObjectName("cbParity")
        self.formLayout.setWidget(4, QtWidgets.QFormLayout.FieldRole, self.cbParity)
        self.label_9 = QtWidgets.QLabel(self.centralwidget)
        self.label_9.setObjectName("label_9")
        self.formLayout.setWidget(5, QtWidgets.QFormLayout.LabelRole, self.label_9)
        self.cbFlowControl = QtWidgets.QComboBox(self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Ignored, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.cbFlowControl.sizePolicy().hasHeightForWidth())
        self.cbFlowControl.setSizePolicy(sizePolicy)
        self.cbFlowControl.setObjectName("cbFlowControl")
        self.formLayout.setWidget(5, QtWidgets.QFormLayout.FieldRole, self.cbFlowControl)
        self.verticalLayout_4.addLayout(self.formLayout)
        self.formLayout_2 = QtWidgets.QFormLayout()
        self.formLayout_2.setSpacing(2)
        self.formLayout_2.setObjectName("formLayout_2")
        self.label = QtWidgets.QLabel(self.centralwidget)
        self.label.setObjectName("label")
        self.formLayout_2.setWidget(0, QtWidgets.QFormLayout.LabelRole, self.label)
        self.cbNewline = QtWidgets.QComboBox(self.centralwidget)
        self.cbNewline.setObjectName("cbNewline")
        self.formLayout_2.setWidget(0, QtWidgets.QFormLayout.FieldRole, self.cbNewline)
        self.label_7 = QtWidgets.QLabel(self.centralwidget)
        self.label_7.setObjectName("label_7")
        self.formLayout_2.setWidget(1, QtWidgets.QFormLayout.LabelRole, self.label_7)
        self.cbDisplay = QtWidgets.QComboBox(self.centralwidget)
        self.cbDisplay.setObjectName("cbDisplay")
        self.formLayout_2.setWidget(1, QtWidgets.QFormLayout.FieldRole, self.cbDisplay)
        self.verticalLayout_4.addLayout(self.formLayout_2)
        spacerItem = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.verticalLayout_4.addItem(spacerItem)
        self.horizontalLayout.addLayout(self.verticalLayout_4)
        self.textEdit = QtWidgets.QPlainTextEdit(self.centralwidget)
        font = QtGui.QFont()
        font.setFamily("Bitstream Vera Sans Mono")
        self.textEdit.setFont(font)
        self.textEdit.setObjectName("textEdit")
        self.horizontalLayout.addWidget(self.textEdit)
        self.verticalLayout_3 = QtWidgets.QVBoxLayout()
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.widget = QtWidgets.QWidget(self.centralwidget)
        self.widget.setObjectName("widget")
        self.verticalLayout_3.addWidget(self.widget)
        self.gbDebug = QtWidgets.QGroupBox(self.centralwidget)
        self.gbDebug.setObjectName("gbDebug")
        self.verticalLayout_7 = QtWidgets.QVBoxLayout(self.gbDebug)
        self.verticalLayout_7.setObjectName("verticalLayout_7")
        self.bpTest1 = QtWidgets.QPushButton(self.gbDebug)
        self.bpTest1.setObjectName("bpTest1")
        self.verticalLayout_7.addWidget(self.bpTest1)
        self.bpTest2 = QtWidgets.QPushButton(self.gbDebug)
        self.bpTest2.setObjectName("bpTest2")
        self.verticalLayout_7.addWidget(self.bpTest2)
        self.pushButton = QtWidgets.QPushButton(self.gbDebug)
        self.pushButton.setObjectName("pushButton")
        self.verticalLayout_7.addWidget(self.pushButton)
        self.verticalLayout_3.addWidget(self.gbDebug)
        spacerItem1 = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.verticalLayout_3.addItem(spacerItem1)
        self.horizontalLayout.addLayout(self.verticalLayout_3)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 923, 25))
        self.menubar.setObjectName("menubar")
        self.menuFile = QtWidgets.QMenu(self.menubar)
        self.menuFile.setObjectName("menuFile")
        self.menuHelp = QtWidgets.QMenu(self.menubar)
        self.menuHelp.setObjectName("menuHelp")
        self.menuAction = QtWidgets.QMenu(self.menubar)
        self.menuAction.setObjectName("menuAction")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setLayoutDirection(QtCore.Qt.RightToLeft)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.actionExit = QtWidgets.QAction(MainWindow)
        self.actionExit.setObjectName("actionExit")
        self.actionAbout = QtWidgets.QAction(MainWindow)
        self.actionAbout.setObjectName("actionAbout")
        self.actionNew = QtWidgets.QAction(MainWindow)
        self.actionNew.setObjectName("actionNew")
        self.actionClear = QtWidgets.QAction(MainWindow)
        self.actionClear.setObjectName("actionClear")
        self.actionReset_port = QtWidgets.QAction(MainWindow)
        self.actionReset_port.setObjectName("actionReset_port")
        self.menuFile.addAction(self.actionNew)
        self.menuFile.addAction(self.actionExit)
        self.menuHelp.addAction(self.actionAbout)
        self.menuAction.addAction(self.actionClear)
        self.menuAction.addAction(self.actionReset_port)
        self.menubar.addAction(self.menuFile.menuAction())
        self.menubar.addAction(self.menuAction.menuAction())
        self.menubar.addAction(self.menuHelp.menuAction())

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.pbOpen.setText(_translate("MainWindow", "Open"))
        self.label_2.setText(_translate("MainWindow", "Port"))
        self.label_3.setText(_translate("MainWindow", "Bitrate"))
        self.label_4.setText(_translate("MainWindow", "StopBit"))
        self.label_5.setText(_translate("MainWindow", "Bits"))
        self.label_6.setText(_translate("MainWindow", "Parity"))
        self.label_9.setText(_translate("MainWindow", "Hw Flow"))
        self.label.setText(_translate("MainWindow", "Newline"))
        self.label_7.setText(_translate("MainWindow", "Display "))
        self.gbDebug.setTitle(_translate("MainWindow", "Debug"))
        self.bpTest1.setText(_translate("MainWindow", "Test1"))
        self.bpTest2.setText(_translate("MainWindow", "Test2"))
        self.pushButton.setText(_translate("MainWindow", "PushButton"))
        self.menuFile.setTitle(_translate("MainWindow", "File"))
        self.menuHelp.setTitle(_translate("MainWindow", "Help"))
        self.menuAction.setTitle(_translate("MainWindow", "Action"))
        self.actionExit.setText(_translate("MainWindow", "Exit"))
        self.actionAbout.setText(_translate("MainWindow", "About"))
        self.actionNew.setText(_translate("MainWindow", "New"))
        self.actionClear.setText(_translate("MainWindow", "Clear"))
        self.actionReset_port.setText(_translate("MainWindow", "Reset port"))

