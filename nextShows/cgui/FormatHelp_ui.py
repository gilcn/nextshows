# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'WorkFiles/ConfigGUI/FormatHelp.ui'
#
# Created: Wed Jun 13 14:11:32 2007
#      by: PyQt4 UI code generator 4-snapshot-20070606
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

class Ui_FormatHelp(object):
    def setupUi(self, FormatHelp):
        FormatHelp.setObjectName("FormatHelp")
        FormatHelp.resize(QtCore.QSize(QtCore.QRect(0,0,391,604).size()).expandedTo(FormatHelp.minimumSizeHint()))
        FormatHelp.setWindowIcon(QtGui.QIcon(":/images/icons/images/icons/nextShows.png"))

        self.vboxlayout = QtGui.QVBoxLayout(FormatHelp)
        self.vboxlayout.setObjectName("vboxlayout")

        self.hboxlayout = QtGui.QHBoxLayout()
        self.hboxlayout.setObjectName("hboxlayout")

        self.lblInfoPic = QtGui.QLabel(FormatHelp)

        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Fixed,QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lblInfoPic.sizePolicy().hasHeightForWidth())
        self.lblInfoPic.setSizePolicy(sizePolicy)
        self.lblInfoPic.setPixmap(QtGui.QPixmap(":/images/icons/images/icons/info.png"))
        self.lblInfoPic.setObjectName("lblInfoPic")
        self.hboxlayout.addWidget(self.lblInfoPic)

        self.lblTitle = QtGui.QLabel(FormatHelp)

        font = QtGui.QFont()
        font.setPointSize(11)
        font.setWeight(75)
        font.setBold(True)
        self.lblTitle.setFont(font)
        self.lblTitle.setAlignment(QtCore.Qt.AlignCenter)
        self.lblTitle.setObjectName("lblTitle")
        self.hboxlayout.addWidget(self.lblTitle)
        self.vboxlayout.addLayout(self.hboxlayout)

        self.line = QtGui.QFrame(FormatHelp)
        self.line.setFrameShape(QtGui.QFrame.HLine)
        self.line.setFrameShadow(QtGui.QFrame.Sunken)
        self.line.setObjectName("line")
        self.vboxlayout.addWidget(self.line)

        self.label = QtGui.QLabel(FormatHelp)
        self.label.setMinimumSize(QtCore.QSize(0,140))
        self.label.setMaximumSize(QtCore.QSize(16777215,140))
        self.label.setAlignment(QtCore.Qt.AlignLeading|QtCore.Qt.AlignLeft|QtCore.Qt.AlignTop)
        self.label.setWordWrap(True)
        self.label.setObjectName("label")
        self.vboxlayout.addWidget(self.label)

        self.label_2 = QtGui.QLabel(FormatHelp)
        self.label_2.setObjectName("label_2")
        self.vboxlayout.addWidget(self.label_2)

        self.label_3 = QtGui.QLabel(FormatHelp)
        self.label_3.setMinimumSize(QtCore.QSize(0,150))
        self.label_3.setMaximumSize(QtCore.QSize(16777215,150))
        self.label_3.setAlignment(QtCore.Qt.AlignLeading|QtCore.Qt.AlignLeft|QtCore.Qt.AlignTop)
        self.label_3.setWordWrap(True)
        self.label_3.setObjectName("label_3")
        self.vboxlayout.addWidget(self.label_3)

        self.label_4 = QtGui.QLabel(FormatHelp)
        self.label_4.setObjectName("label_4")
        self.vboxlayout.addWidget(self.label_4)

        self.label_5 = QtGui.QLabel(FormatHelp)
        self.label_5.setAlignment(QtCore.Qt.AlignLeading|QtCore.Qt.AlignLeft|QtCore.Qt.AlignTop)
        self.label_5.setWordWrap(True)
        self.label_5.setObjectName("label_5")
        self.vboxlayout.addWidget(self.label_5)

        spacerItem = QtGui.QSpacerItem(20,40,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Expanding)
        self.vboxlayout.addItem(spacerItem)

        self.btnClose = QtGui.QPushButton(FormatHelp)
        self.btnClose.setObjectName("btnClose")
        self.vboxlayout.addWidget(self.btnClose)

        self.retranslateUi(FormatHelp)
        QtCore.QMetaObject.connectSlotsByName(FormatHelp)

    def retranslateUi(self, FormatHelp):
        FormatHelp.setWindowTitle(QtGui.QApplication.translate("FormatHelp", "Formatting Help", None, QtGui.QApplication.UnicodeUTF8))
        self.lblTitle.setText(QtGui.QApplication.translate("FormatHelp", "Formatting Help", None, QtGui.QApplication.UnicodeUTF8))
        self.label.setText(QtGui.QApplication.translate("FormatHelp", "<p align=\"justify\">You can customize the way you want nextShows to display your shows. For that, 4 variables are available which comes with optional parameters:<br />\n"
        "<b>&middot; $show[:length[:trailing_chars]]$</b><br />\n"
        "<b>&middot; $title[:length[:trailing_chars]]$</b><br />\n"
        "<b>&middot; $season[:zero_padded_length]$</b><br />\n"
        "<b>&middot; $episode[:zero_padded_length]$</b></p>", None, QtGui.QApplication.UnicodeUTF8))
        self.label_2.setText(QtGui.QApplication.translate("FormatHelp", "<p><b>Examples:</b></p>", None, QtGui.QApplication.UnicodeUTF8))
        self.label_3.setText(QtGui.QApplication.translate("FormatHelp", "<p align=\"justify\">Suppose <b>$show$</b> is \"Battlestar Galactica (2003)\", <b>$title$</b> is \"Litmus\", <b>$season$</b> is \"1\" and <b>$episode$</b> is \"6\":<br />\n"
        "<b>#1)</b> Format: $show$-$season$x$episode$-$title$<br />\n"
        "&nbsp;&nbsp;&nbsp;&nbsp;Result: Battlestar Galactica (2003)-1x6-Litmus<br />\n"
        "<b>#2)</b> Format: $show:12$-$season$x$episode:2$-$title$<br />\n"
        "&nbsp;&nbsp;&nbsp;&nbsp;Result: Battlestar G-1x06-Litmus<br />\n"
        "<b>#3)</b> Format: $show:12:...$/S$season:2$E$episode:2$/$title$<br />\n"
        "&nbsp;&nbsp;&nbsp;&nbsp;Result: Battlestar G.../S01E06/Litmus</p>", None, QtGui.QApplication.UnicodeUTF8))
        self.label_4.setText(QtGui.QApplication.translate("FormatHelp", "<p><b>Notes:</b></p>", None, QtGui.QApplication.UnicodeUTF8))
        self.label_5.setText(QtGui.QApplication.translate("FormatHelp", "<p align=\"justify\"><b>&middot;</b> When using the <b>:trailing_chars</b> parameter, if the length of the text to display is shorter than the length of the text + trailing_chars, this option will be ignored!<br />\n"
        "<b>&middot;</b> When using the <b>:zero_padded_length</b> parameter and the content to display cannot fit, this value will be ignored. Example: if <b>$episode$</b>=42 and you set <b>$episode:1$</b> nextShows will display \"42\".</p>", None, QtGui.QApplication.UnicodeUTF8))
        self.btnClose.setText(QtGui.QApplication.translate("FormatHelp", "&Close", None, QtGui.QApplication.UnicodeUTF8))

import NextShowsConfig_rc
