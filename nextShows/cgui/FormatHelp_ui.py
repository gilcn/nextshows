# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'WorkFiles/ConfigGUI/FormatHelp.ui'
#
# Created: Sun May 27 23:57:16 2007
#      by: PyQt4 UI code generator 4.2
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

class Ui_FormatHelp(object):
    def setupUi(self, FormatHelp):
        FormatHelp.setObjectName("FormatHelp")
        FormatHelp.resize(QtCore.QSize(QtCore.QRect(0,0,391,571).size()).expandedTo(FormatHelp.minimumSizeHint()))
        FormatHelp.setWindowIcon(QtGui.QIcon(":/images/icons/images/icons/nextShows.png"))

        self.gridlayout = QtGui.QGridLayout(FormatHelp)
        self.gridlayout.setMargin(9)
        self.gridlayout.setSpacing(6)
        self.gridlayout.setObjectName("gridlayout")

        self.vboxlayout = QtGui.QVBoxLayout()
        self.vboxlayout.setMargin(0)
        self.vboxlayout.setSpacing(6)
        self.vboxlayout.setObjectName("vboxlayout")

        spacerItem = QtGui.QSpacerItem(20,10,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Fixed)
        self.vboxlayout.addItem(spacerItem)

        self.label = QtGui.QLabel(FormatHelp)
        self.label.setAlignment(QtCore.Qt.AlignJustify|QtCore.Qt.AlignTop)
        self.label.setWordWrap(True)
        self.label.setObjectName("label")
        self.vboxlayout.addWidget(self.label)

        spacerItem1 = QtGui.QSpacerItem(20,10,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Fixed)
        self.vboxlayout.addItem(spacerItem1)

        self.label_3 = QtGui.QLabel(FormatHelp)
        self.label_3.setObjectName("label_3")
        self.vboxlayout.addWidget(self.label_3)

        self.label_2 = QtGui.QLabel(FormatHelp)
        self.label_2.setAlignment(QtCore.Qt.AlignJustify|QtCore.Qt.AlignVCenter)
        self.label_2.setWordWrap(True)
        self.label_2.setObjectName("label_2")
        self.vboxlayout.addWidget(self.label_2)

        spacerItem2 = QtGui.QSpacerItem(20,10,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Fixed)
        self.vboxlayout.addItem(spacerItem2)

        self.label_4 = QtGui.QLabel(FormatHelp)
        self.label_4.setObjectName("label_4")
        self.vboxlayout.addWidget(self.label_4)

        self.label_5 = QtGui.QLabel(FormatHelp)
        self.label_5.setAlignment(QtCore.Qt.AlignJustify|QtCore.Qt.AlignTop)
        self.label_5.setWordWrap(True)
        self.label_5.setObjectName("label_5")
        self.vboxlayout.addWidget(self.label_5)

        spacerItem3 = QtGui.QSpacerItem(20,10,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Fixed)
        self.vboxlayout.addItem(spacerItem3)

        self.btnClose = QtGui.QPushButton(FormatHelp)
        self.btnClose.setObjectName("btnClose")
        self.vboxlayout.addWidget(self.btnClose)
        self.gridlayout.addLayout(self.vboxlayout,1,0,1,1)

        self.hboxlayout = QtGui.QHBoxLayout()
        self.hboxlayout.setMargin(0)
        self.hboxlayout.setSpacing(6)
        self.hboxlayout.setObjectName("hboxlayout")

        self.lblInfoPic = QtGui.QLabel(FormatHelp)

        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Policy(0),QtGui.QSizePolicy.Policy(0))
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lblInfoPic.sizePolicy().hasHeightForWidth())
        self.lblInfoPic.setSizePolicy(sizePolicy)
        self.lblInfoPic.setPixmap(QtGui.QPixmap(":/images/icons/images/icons/info.png"))
        self.lblInfoPic.setObjectName("lblInfoPic")
        self.hboxlayout.addWidget(self.lblInfoPic)

        self.lblTitle = QtGui.QLabel(FormatHelp)

        font = QtGui.QFont()
        font.setPointSize(10)
        font.setWeight(75)
        font.setBold(True)
        self.lblTitle.setFont(font)
        self.lblTitle.setAlignment(QtCore.Qt.AlignCenter)
        self.lblTitle.setObjectName("lblTitle")
        self.hboxlayout.addWidget(self.lblTitle)
        self.gridlayout.addLayout(self.hboxlayout,0,0,1,1)

        self.retranslateUi(FormatHelp)
        QtCore.QMetaObject.connectSlotsByName(FormatHelp)

    def retranslateUi(self, FormatHelp):
        FormatHelp.setWindowTitle(QtGui.QApplication.translate("FormatHelp", "Formatting Help", None, QtGui.QApplication.UnicodeUTF8))
        self.label.setText(QtGui.QApplication.translate("FormatHelp", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
        "p, li { white-space: pre-wrap; }\n"
        "</style></head><body style=\" font-family:\'Sans Serif\'; font-size:9pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">You can customize the way you want nextShows to display your shows. For that, 4 variables are available which comes with optional parameters:</p>\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- <span style=\" font-weight:600;\">$show[:length[:trailing_chars]]$</span></p>\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- <span style=\" font-weight:600;\">$title[:length[:trailing_chars]]$</span></p>\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- <span style=\" font-weight:600;\">$season[:zero_padded_length]$</span></p>\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- <span style=\" font-weight:600;\">$episode[:zero_padded_length]$</span></p></body></html>", None, QtGui.QApplication.UnicodeUTF8))
        self.label_3.setText(QtGui.QApplication.translate("FormatHelp", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
        "p, li { white-space: pre-wrap; }\n"
        "</style></head><body style=\" font-family:\'Sans Serif\'; font-size:9pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">Examples:</span></p></body></html>", None, QtGui.QApplication.UnicodeUTF8))
        self.label_2.setText(QtGui.QApplication.translate("FormatHelp", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
        "p, li { white-space: pre-wrap; }\n"
        "</style></head><body style=\" font-family:\'Sans Serif\'; font-size:9pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Suppose <span style=\" font-weight:600;\">$show$</span> is \"Battlestar Galactica (2003)\", <span style=\" font-weight:600;\">$title$</span> is \"Litmus\", <span style=\" font-weight:600;\">$season$</span> is \"1\" and <span style=\" font-weight:600;\">$episode$ </span>is \"6\":</p>\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">#1)</span> Format: $show$-$season$x$episode$-$title$</p>\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">       Result: Battlestar Galactica (2003)-1x6-Litmus</p>\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">#2)</span> Format: $show:12$-$season$x$episode:2$-$title$</p>\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">       Result: Battlestar G-1x06-Litmus</p>\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">#3)</span> Format: $show:12:...$/S$season:2$E$episode:2$/$title$</p>\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">       Result: Battlestar G.../S01E06/Litmus</p>\n"
        "<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p></body></html>", None, QtGui.QApplication.UnicodeUTF8))
        self.label_4.setText(QtGui.QApplication.translate("FormatHelp", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
        "p, li { white-space: pre-wrap; }\n"
        "</style></head><body style=\" font-family:\'Sans Serif\'; font-size:9pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">Notes:</span></p></body></html>", None, QtGui.QApplication.UnicodeUTF8))
        self.label_5.setText(QtGui.QApplication.translate("FormatHelp", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
        "p, li { white-space: pre-wrap; }\n"
        "</style></head><body style=\" font-family:\'Sans Serif\'; font-size:9pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- When using the <span style=\" font-weight:600;\">:trailing_chars</span> parameter, if the length of the text to display is shorter than the length of the text + trailing_chars, this option will be ignored!</p>\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- When using the <span style=\" font-weight:600;\">:zero_padded_length</span> parameter and the content to display cannot fit, this value will be ignored. Example: if <span style=\" font-weight:600;\">$episode$</span>=42 and you set <span style=\" font-weight:600;\">$episode:1$</span> nextShows will display \"42\".</p></body></html>", None, QtGui.QApplication.UnicodeUTF8))
        self.btnClose.setText(QtGui.QApplication.translate("FormatHelp", "&Close", None, QtGui.QApplication.UnicodeUTF8))
        self.lblTitle.setText(QtGui.QApplication.translate("FormatHelp", "Formatting Help", None, QtGui.QApplication.UnicodeUTF8))

import NextShowsConfig_rc
