# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'WorkFiles/ConfigGUI/NextShowsConfig.ui'
#
# Created: Sun May 27 23:57:15 2007
#      by: PyQt4 UI code generator 4.2
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

class Ui_NextShowsConfig(object):
    def setupUi(self, NextShowsConfig):
        NextShowsConfig.setObjectName("NextShowsConfig")
        NextShowsConfig.resize(QtCore.QSize(QtCore.QRect(0,0,537,563).size()).expandedTo(NextShowsConfig.minimumSizeHint()))
        NextShowsConfig.setWindowIcon(QtGui.QIcon(":/images/icons/images/icons/nextShows.png"))

        self.gridlayout = QtGui.QGridLayout(NextShowsConfig)
        self.gridlayout.setMargin(9)
        self.gridlayout.setSpacing(6)
        self.gridlayout.setObjectName("gridlayout")

        self.tabWidget = QtGui.QTabWidget(NextShowsConfig)
        self.tabWidget.setObjectName("tabWidget")

        self.tabShows = QtGui.QWidget()
        self.tabShows.setObjectName("tabShows")

        self.gridlayout1 = QtGui.QGridLayout(self.tabShows)
        self.gridlayout1.setMargin(9)
        self.gridlayout1.setSpacing(6)
        self.gridlayout1.setObjectName("gridlayout1")

        self.vboxlayout = QtGui.QVBoxLayout()
        self.vboxlayout.setMargin(0)
        self.vboxlayout.setSpacing(6)
        self.vboxlayout.setObjectName("vboxlayout")

        spacerItem = QtGui.QSpacerItem(20,101,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Expanding)
        self.vboxlayout.addItem(spacerItem)

        self.btnShowAdd = QtGui.QToolButton(self.tabShows)
        self.btnShowAdd.setEnabled(False)
        self.btnShowAdd.setIcon(QtGui.QIcon(":/images/icons/images/icons/rightarrow.png"))
        self.btnShowAdd.setObjectName("btnShowAdd")
        self.vboxlayout.addWidget(self.btnShowAdd)

        spacerItem1 = QtGui.QSpacerItem(20,20,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Fixed)
        self.vboxlayout.addItem(spacerItem1)

        self.btnShowRemove = QtGui.QToolButton(self.tabShows)
        self.btnShowRemove.setEnabled(False)
        self.btnShowRemove.setIcon(QtGui.QIcon(":/images/icons/images/icons/leftarrow.png"))
        self.btnShowRemove.setObjectName("btnShowRemove")
        self.vboxlayout.addWidget(self.btnShowRemove)

        spacerItem2 = QtGui.QSpacerItem(20,101,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Expanding)
        self.vboxlayout.addItem(spacerItem2)
        self.gridlayout1.addLayout(self.vboxlayout,4,1,1,1)

        self.vboxlayout1 = QtGui.QVBoxLayout()
        self.vboxlayout1.setMargin(0)
        self.vboxlayout1.setSpacing(6)
        self.vboxlayout1.setObjectName("vboxlayout1")

        self.lblSearchResults = QtGui.QLabel(self.tabShows)

        font = QtGui.QFont()
        font.setWeight(75)
        font.setBold(True)
        self.lblSearchResults.setFont(font)
        self.lblSearchResults.setAlignment(QtCore.Qt.AlignHCenter|QtCore.Qt.AlignTop)
        self.lblSearchResults.setObjectName("lblSearchResults")
        self.vboxlayout1.addWidget(self.lblSearchResults)

        self.listSearchResults = QtGui.QListWidget(self.tabShows)
        self.listSearchResults.setEnabled(False)
        self.listSearchResults.setObjectName("listSearchResults")
        self.vboxlayout1.addWidget(self.listSearchResults)

        self.hboxlayout = QtGui.QHBoxLayout()
        self.hboxlayout.setMargin(0)
        self.hboxlayout.setSpacing(6)
        self.hboxlayout.setObjectName("hboxlayout")

        self.chkbxFilter = QtGui.QCheckBox(self.tabShows)
        self.chkbxFilter.setEnabled(False)
        self.chkbxFilter.setChecked(True)
        self.chkbxFilter.setObjectName("chkbxFilter")
        self.hboxlayout.addWidget(self.chkbxFilter)

        self.lblResultsDisplayed = QtGui.QLabel(self.tabShows)
        self.lblResultsDisplayed.setEnabled(False)
        self.lblResultsDisplayed.setAlignment(QtCore.Qt.AlignRight|QtCore.Qt.AlignTrailing|QtCore.Qt.AlignVCenter)
        self.lblResultsDisplayed.setObjectName("lblResultsDisplayed")
        self.hboxlayout.addWidget(self.lblResultsDisplayed)
        self.vboxlayout1.addLayout(self.hboxlayout)
        self.gridlayout1.addLayout(self.vboxlayout1,4,0,1,1)

        self.vboxlayout2 = QtGui.QVBoxLayout()
        self.vboxlayout2.setMargin(0)
        self.vboxlayout2.setSpacing(6)
        self.vboxlayout2.setObjectName("vboxlayout2")

        self.lblMyShows = QtGui.QLabel(self.tabShows)

        font = QtGui.QFont()
        font.setWeight(75)
        font.setBold(True)
        self.lblMyShows.setFont(font)
        self.lblMyShows.setAlignment(QtCore.Qt.AlignHCenter|QtCore.Qt.AlignTop)
        self.lblMyShows.setObjectName("lblMyShows")
        self.vboxlayout2.addWidget(self.lblMyShows)

        self.listMyShows = QtGui.QListWidget(self.tabShows)
        self.listMyShows.setEnabled(False)
        self.listMyShows.setObjectName("listMyShows")
        self.vboxlayout2.addWidget(self.listMyShows)

        self.hboxlayout1 = QtGui.QHBoxLayout()
        self.hboxlayout1.setMargin(0)
        self.hboxlayout1.setSpacing(6)
        self.hboxlayout1.setObjectName("hboxlayout1")

        spacerItem3 = QtGui.QSpacerItem(20,22,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Fixed)
        self.hboxlayout1.addItem(spacerItem3)

        self.lblTrackedShows = QtGui.QLabel(self.tabShows)
        self.lblTrackedShows.setAlignment(QtCore.Qt.AlignRight|QtCore.Qt.AlignTrailing|QtCore.Qt.AlignVCenter)
        self.lblTrackedShows.setObjectName("lblTrackedShows")
        self.hboxlayout1.addWidget(self.lblTrackedShows)
        self.vboxlayout2.addLayout(self.hboxlayout1)
        self.gridlayout1.addLayout(self.vboxlayout2,4,2,1,1)

        self.line_3 = QtGui.QFrame(self.tabShows)
        self.line_3.setFrameShape(QtGui.QFrame.HLine)
        self.line_3.setFrameShadow(QtGui.QFrame.Sunken)
        self.line_3.setObjectName("line_3")
        self.gridlayout1.addWidget(self.line_3,3,0,1,3)

        self.hboxlayout2 = QtGui.QHBoxLayout()
        self.hboxlayout2.setMargin(0)
        self.hboxlayout2.setSpacing(6)
        self.hboxlayout2.setObjectName("hboxlayout2")

        self.labSearchFor = QtGui.QLabel(self.tabShows)
        self.labSearchFor.setObjectName("labSearchFor")
        self.hboxlayout2.addWidget(self.labSearchFor)

        self.leditLookup = QtGui.QLineEdit(self.tabShows)
        self.leditLookup.setObjectName("leditLookup")
        self.hboxlayout2.addWidget(self.leditLookup)

        self.btnLeditLookupClear = QtGui.QToolButton(self.tabShows)
        self.btnLeditLookupClear.setIcon(QtGui.QIcon(":/images/icons/images/icons/clear.png"))
        self.btnLeditLookupClear.setObjectName("btnLeditLookupClear")
        self.hboxlayout2.addWidget(self.btnLeditLookupClear)

        self.btnLookup = QtGui.QPushButton(self.tabShows)
        self.btnLookup.setEnabled(False)
        self.btnLookup.setCheckable(True)
        self.btnLookup.setAutoDefault(True)
        self.btnLookup.setDefault(True)
        self.btnLookup.setObjectName("btnLookup")
        self.hboxlayout2.addWidget(self.btnLookup)
        self.gridlayout1.addLayout(self.hboxlayout2,2,0,1,3)

        self.line_2 = QtGui.QFrame(self.tabShows)
        self.line_2.setFrameShape(QtGui.QFrame.HLine)
        self.line_2.setFrameShadow(QtGui.QFrame.Sunken)
        self.line_2.setObjectName("line_2")
        self.gridlayout1.addWidget(self.line_2,1,0,1,3)

        self.label_4 = QtGui.QLabel(self.tabShows)

        font = QtGui.QFont()
        font.setPointSize(10)
        font.setWeight(75)
        font.setStrikeOut(False)
        font.setBold(True)
        self.label_4.setFont(font)
        self.label_4.setAlignment(QtCore.Qt.AlignCenter)
        self.label_4.setObjectName("label_4")
        self.gridlayout1.addWidget(self.label_4,0,0,1,3)
        self.tabWidget.addTab(self.tabShows,"")

        self.tabWidget1 = QtGui.QWidget()
        self.tabWidget1.setObjectName("tabWidget1")

        self.gridlayout2 = QtGui.QGridLayout(self.tabWidget1)
        self.gridlayout2.setMargin(9)
        self.gridlayout2.setSpacing(6)
        self.gridlayout2.setObjectName("gridlayout2")

        self.line_4 = QtGui.QFrame(self.tabWidget1)
        self.line_4.setFrameShape(QtGui.QFrame.HLine)
        self.line_4.setFrameShadow(QtGui.QFrame.Sunken)
        self.line_4.setObjectName("line_4")
        self.gridlayout2.addWidget(self.line_4,1,0,1,1)

        self.lblTabWidgetInfo = QtGui.QLabel(self.tabWidget1)

        font = QtGui.QFont()
        font.setPointSize(10)
        font.setWeight(75)
        font.setBold(True)
        self.lblTabWidgetInfo.setFont(font)
        self.lblTabWidgetInfo.setAlignment(QtCore.Qt.AlignCenter)
        self.lblTabWidgetInfo.setObjectName("lblTabWidgetInfo")
        self.gridlayout2.addWidget(self.lblTabWidgetInfo,0,0,1,1)

        self.tabWidgetWidget = QtGui.QTabWidget(self.tabWidget1)
        self.tabWidgetWidget.setObjectName("tabWidgetWidget")

        self.tabDisplay = QtGui.QWidget()
        self.tabDisplay.setObjectName("tabDisplay")

        self.gridlayout3 = QtGui.QGridLayout(self.tabDisplay)
        self.gridlayout3.setMargin(9)
        self.gridlayout3.setSpacing(6)
        self.gridlayout3.setObjectName("gridlayout3")

        spacerItem4 = QtGui.QSpacerItem(20,20,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Fixed)
        self.gridlayout3.addItem(spacerItem4,7,0,1,1)

        spacerItem5 = QtGui.QSpacerItem(20,20,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Fixed)
        self.gridlayout3.addItem(spacerItem5,1,0,1,1)

        self.hboxlayout3 = QtGui.QHBoxLayout()
        self.hboxlayout3.setMargin(0)
        self.hboxlayout3.setSpacing(6)
        self.hboxlayout3.setObjectName("hboxlayout3")

        spacerItem6 = QtGui.QSpacerItem(18,25,QtGui.QSizePolicy.Fixed,QtGui.QSizePolicy.Minimum)
        self.hboxlayout3.addItem(spacerItem6)

        self.lblMaxDispLines = QtGui.QLabel(self.tabDisplay)
        self.lblMaxDispLines.setEnabled(False)
        self.lblMaxDispLines.setObjectName("lblMaxDispLines")
        self.hboxlayout3.addWidget(self.lblMaxDispLines)

        spacerItem7 = QtGui.QSpacerItem(22,20,QtGui.QSizePolicy.Fixed,QtGui.QSizePolicy.Minimum)
        self.hboxlayout3.addItem(spacerItem7)

        self.spinMaxDispLines = QtGui.QSpinBox(self.tabDisplay)
        self.spinMaxDispLines.setEnabled(False)
        self.spinMaxDispLines.setMaximum(50)
        self.spinMaxDispLines.setMinimum(2)
        self.spinMaxDispLines.setProperty("value",QtCore.QVariant(10))
        self.spinMaxDispLines.setObjectName("spinMaxDispLines")
        self.hboxlayout3.addWidget(self.spinMaxDispLines)
        self.gridlayout3.addLayout(self.hboxlayout3,6,0,1,1)

        self.radioDispFixedLines = QtGui.QRadioButton(self.tabDisplay)
        self.radioDispFixedLines.setChecked(True)
        self.radioDispFixedLines.setObjectName("radioDispFixedLines")
        self.gridlayout3.addWidget(self.radioDispFixedLines,2,0,1,1)

        self.hboxlayout4 = QtGui.QHBoxLayout()
        self.hboxlayout4.setMargin(0)
        self.hboxlayout4.setSpacing(6)
        self.hboxlayout4.setObjectName("hboxlayout4")

        spacerItem8 = QtGui.QSpacerItem(18,25,QtGui.QSizePolicy.Fixed,QtGui.QSizePolicy.Minimum)
        self.hboxlayout4.addItem(spacerItem8)

        self.lblFixedDispLines = QtGui.QLabel(self.tabDisplay)
        self.lblFixedDispLines.setObjectName("lblFixedDispLines")
        self.hboxlayout4.addWidget(self.lblFixedDispLines)

        spacerItem9 = QtGui.QSpacerItem(22,20,QtGui.QSizePolicy.Fixed,QtGui.QSizePolicy.Minimum)
        self.hboxlayout4.addItem(spacerItem9)

        self.spinFixedDispLines = QtGui.QSpinBox(self.tabDisplay)
        self.spinFixedDispLines.setMaximum(50)
        self.spinFixedDispLines.setMinimum(1)
        self.spinFixedDispLines.setProperty("value",QtCore.QVariant(10))
        self.spinFixedDispLines.setObjectName("spinFixedDispLines")
        self.hboxlayout4.addWidget(self.spinFixedDispLines)
        self.gridlayout3.addLayout(self.hboxlayout4,3,0,1,1)

        self.radioDispAutoResize = QtGui.QRadioButton(self.tabDisplay)
        self.radioDispAutoResize.setObjectName("radioDispAutoResize")
        self.gridlayout3.addWidget(self.radioDispAutoResize,4,0,1,1)

        self.hboxlayout5 = QtGui.QHBoxLayout()
        self.hboxlayout5.setMargin(0)
        self.hboxlayout5.setSpacing(6)
        self.hboxlayout5.setObjectName("hboxlayout5")

        spacerItem10 = QtGui.QSpacerItem(18,25,QtGui.QSizePolicy.Fixed,QtGui.QSizePolicy.Minimum)
        self.hboxlayout5.addItem(spacerItem10)

        self.lblMinDispLines = QtGui.QLabel(self.tabDisplay)
        self.lblMinDispLines.setEnabled(False)
        self.lblMinDispLines.setObjectName("lblMinDispLines")
        self.hboxlayout5.addWidget(self.lblMinDispLines)

        spacerItem11 = QtGui.QSpacerItem(22,20,QtGui.QSizePolicy.Fixed,QtGui.QSizePolicy.Minimum)
        self.hboxlayout5.addItem(spacerItem11)

        self.spinMinDispLines = QtGui.QSpinBox(self.tabDisplay)
        self.spinMinDispLines.setEnabled(False)
        self.spinMinDispLines.setMaximum(49)
        self.spinMinDispLines.setMinimum(1)
        self.spinMinDispLines.setProperty("value",QtCore.QVariant(1))
        self.spinMinDispLines.setObjectName("spinMinDispLines")
        self.hboxlayout5.addWidget(self.spinMinDispLines)
        self.gridlayout3.addLayout(self.hboxlayout5,5,0,1,1)

        self.hboxlayout6 = QtGui.QHBoxLayout()
        self.hboxlayout6.setMargin(0)
        self.hboxlayout6.setSpacing(6)
        self.hboxlayout6.setObjectName("hboxlayout6")

        self.lblNumPastDays = QtGui.QLabel(self.tabDisplay)
        self.lblNumPastDays.setObjectName("lblNumPastDays")
        self.hboxlayout6.addWidget(self.lblNumPastDays)

        spacerItem12 = QtGui.QSpacerItem(37,20,QtGui.QSizePolicy.Fixed,QtGui.QSizePolicy.Minimum)
        self.hboxlayout6.addItem(spacerItem12)

        self.spinNumPastDays = QtGui.QSpinBox(self.tabDisplay)
        self.spinNumPastDays.setMaximum(30)
        self.spinNumPastDays.setProperty("value",QtCore.QVariant(1))
        self.spinNumPastDays.setObjectName("spinNumPastDays")
        self.hboxlayout6.addWidget(self.spinNumPastDays)
        self.gridlayout3.addLayout(self.hboxlayout6,0,0,1,1)

        spacerItem13 = QtGui.QSpacerItem(20,40,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Expanding)
        self.gridlayout3.addItem(spacerItem13,11,0,1,1)

        self.lblFormatPreview = QtGui.QLabel(self.tabDisplay)
        self.lblFormatPreview.setObjectName("lblFormatPreview")
        self.gridlayout3.addWidget(self.lblFormatPreview,10,0,1,1)

        self.lblFormatExample = QtGui.QLabel(self.tabDisplay)
        self.lblFormatExample.setWordWrap(True)
        self.lblFormatExample.setObjectName("lblFormatExample")
        self.gridlayout3.addWidget(self.lblFormatExample,9,0,1,1)

        self.hboxlayout7 = QtGui.QHBoxLayout()
        self.hboxlayout7.setMargin(0)
        self.hboxlayout7.setSpacing(6)
        self.hboxlayout7.setObjectName("hboxlayout7")

        self.lblFormat = QtGui.QLabel(self.tabDisplay)
        self.lblFormat.setObjectName("lblFormat")
        self.hboxlayout7.addWidget(self.lblFormat)

        self.leditFormat = QtGui.QLineEdit(self.tabDisplay)
        self.leditFormat.setObjectName("leditFormat")
        self.hboxlayout7.addWidget(self.leditFormat)

        self.btnFormatInfos = QtGui.QToolButton(self.tabDisplay)
        self.btnFormatInfos.setIcon(QtGui.QIcon(":/images/icons/images/icons/info.png"))
        self.btnFormatInfos.setCheckable(True)
        self.btnFormatInfos.setObjectName("btnFormatInfos")
        self.hboxlayout7.addWidget(self.btnFormatInfos)
        self.gridlayout3.addLayout(self.hboxlayout7,8,0,1,1)
        self.tabWidgetWidget.addTab(self.tabDisplay,"")

        self.tabColors = QtGui.QWidget()
        self.tabColors.setObjectName("tabColors")

        self.gridlayout4 = QtGui.QGridLayout(self.tabColors)
        self.gridlayout4.setMargin(9)
        self.gridlayout4.setSpacing(6)
        self.gridlayout4.setObjectName("gridlayout4")

        self.grpbxCol = QtGui.QGroupBox(self.tabColors)
        self.grpbxCol.setObjectName("grpbxCol")

        self.gridlayout5 = QtGui.QGridLayout(self.grpbxCol)
        self.gridlayout5.setMargin(9)
        self.gridlayout5.setSpacing(6)
        self.gridlayout5.setObjectName("gridlayout5")

        self.radioSingleDay = QtGui.QRadioButton(self.grpbxCol)
        self.radioSingleDay.setChecked(True)
        self.radioSingleDay.setObjectName("radioSingleDay")
        self.gridlayout5.addWidget(self.radioSingleDay,0,0,1,1)

        self.hboxlayout8 = QtGui.QHBoxLayout()
        self.hboxlayout8.setMargin(0)
        self.hboxlayout8.setSpacing(6)
        self.hboxlayout8.setObjectName("hboxlayout8")

        spacerItem14 = QtGui.QSpacerItem(18,25,QtGui.QSizePolicy.Fixed,QtGui.QSizePolicy.Minimum)
        self.hboxlayout8.addItem(spacerItem14)

        self.lblColorsDay = QtGui.QLabel(self.grpbxCol)
        self.lblColorsDay.setObjectName("lblColorsDay")
        self.hboxlayout8.addWidget(self.lblColorsDay)

        self.spinColorsSingleDay = QtGui.QSpinBox(self.grpbxCol)
        self.spinColorsSingleDay.setMinimum(-99)
        self.spinColorsSingleDay.setObjectName("spinColorsSingleDay")
        self.hboxlayout8.addWidget(self.spinColorsSingleDay)
        self.gridlayout5.addLayout(self.hboxlayout8,1,0,1,1)

        self.radioDayRange = QtGui.QRadioButton(self.grpbxCol)
        self.radioDayRange.setObjectName("radioDayRange")
        self.gridlayout5.addWidget(self.radioDayRange,2,0,1,1)

        self.hboxlayout9 = QtGui.QHBoxLayout()
        self.hboxlayout9.setMargin(0)
        self.hboxlayout9.setSpacing(6)
        self.hboxlayout9.setObjectName("hboxlayout9")

        spacerItem15 = QtGui.QSpacerItem(18,25,QtGui.QSizePolicy.Fixed,QtGui.QSizePolicy.Minimum)
        self.hboxlayout9.addItem(spacerItem15)

        self.lblColorsFrom = QtGui.QLabel(self.grpbxCol)
        self.lblColorsFrom.setEnabled(False)
        self.lblColorsFrom.setObjectName("lblColorsFrom")
        self.hboxlayout9.addWidget(self.lblColorsFrom)

        self.spinColorsFrom = QtGui.QSpinBox(self.grpbxCol)
        self.spinColorsFrom.setEnabled(False)
        self.spinColorsFrom.setMaximum(98)
        self.spinColorsFrom.setMinimum(-99)
        self.spinColorsFrom.setProperty("value",QtCore.QVariant(-99))
        self.spinColorsFrom.setObjectName("spinColorsFrom")
        self.hboxlayout9.addWidget(self.spinColorsFrom)
        self.gridlayout5.addLayout(self.hboxlayout9,3,0,1,1)

        self.hboxlayout10 = QtGui.QHBoxLayout()
        self.hboxlayout10.setMargin(0)
        self.hboxlayout10.setSpacing(6)
        self.hboxlayout10.setObjectName("hboxlayout10")

        spacerItem16 = QtGui.QSpacerItem(18,25,QtGui.QSizePolicy.Fixed,QtGui.QSizePolicy.Minimum)
        self.hboxlayout10.addItem(spacerItem16)

        self.lblColorsTo = QtGui.QLabel(self.grpbxCol)
        self.lblColorsTo.setEnabled(False)
        self.lblColorsTo.setObjectName("lblColorsTo")
        self.hboxlayout10.addWidget(self.lblColorsTo)

        self.spinColorsTo = QtGui.QSpinBox(self.grpbxCol)
        self.spinColorsTo.setEnabled(False)
        self.spinColorsTo.setMinimum(-98)
        self.spinColorsTo.setProperty("value",QtCore.QVariant(99))
        self.spinColorsTo.setObjectName("spinColorsTo")
        self.hboxlayout10.addWidget(self.spinColorsTo)
        self.gridlayout5.addLayout(self.hboxlayout10,4,0,1,1)

        spacerItem17 = QtGui.QSpacerItem(20,20,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Fixed)
        self.gridlayout5.addItem(spacerItem17,5,0,1,1)

        self.hboxlayout11 = QtGui.QHBoxLayout()
        self.hboxlayout11.setMargin(0)
        self.hboxlayout11.setSpacing(6)
        self.hboxlayout11.setObjectName("hboxlayout11")

        self.btnSelectColor = QtGui.QPushButton(self.grpbxCol)

        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Policy(3),QtGui.QSizePolicy.Policy(0))
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.btnSelectColor.sizePolicy().hasHeightForWidth())
        self.btnSelectColor.setSizePolicy(sizePolicy)
        self.btnSelectColor.setObjectName("btnSelectColor")
        self.hboxlayout11.addWidget(self.btnSelectColor)

        spacerItem18 = QtGui.QSpacerItem(15,20,QtGui.QSizePolicy.Fixed,QtGui.QSizePolicy.Minimum)
        self.hboxlayout11.addItem(spacerItem18)

        self.lblSelectColor = QtGui.QLabel(self.grpbxCol)

        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Policy(0),QtGui.QSizePolicy.Policy(0))
        sizePolicy.setHorizontalStretch(48)
        sizePolicy.setVerticalStretch(48)
        sizePolicy.setHeightForWidth(self.lblSelectColor.sizePolicy().hasHeightForWidth())
        self.lblSelectColor.setSizePolicy(sizePolicy)
        self.lblSelectColor.setPixmap(QtGui.QPixmap(":/images/misc/images/blank_36x36.png"))
        self.lblSelectColor.setObjectName("lblSelectColor")
        self.hboxlayout11.addWidget(self.lblSelectColor)
        self.gridlayout5.addLayout(self.hboxlayout11,6,0,1,1)

        spacerItem19 = QtGui.QSpacerItem(20,21,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Expanding)
        self.gridlayout5.addItem(spacerItem19,7,0,1,1)
        self.gridlayout4.addWidget(self.grpbxCol,2,0,1,1)

        self.hboxlayout12 = QtGui.QHBoxLayout()
        self.hboxlayout12.setMargin(0)
        self.hboxlayout12.setSpacing(6)
        self.hboxlayout12.setObjectName("hboxlayout12")

        spacerItem20 = QtGui.QSpacerItem(11,20,QtGui.QSizePolicy.Fixed,QtGui.QSizePolicy.Minimum)
        self.hboxlayout12.addItem(spacerItem20)

        self.btnSetDefaultColor = QtGui.QPushButton(self.tabColors)

        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Policy(3),QtGui.QSizePolicy.Policy(0))
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.btnSetDefaultColor.sizePolicy().hasHeightForWidth())
        self.btnSetDefaultColor.setSizePolicy(sizePolicy)
        self.btnSetDefaultColor.setObjectName("btnSetDefaultColor")
        self.hboxlayout12.addWidget(self.btnSetDefaultColor)

        spacerItem21 = QtGui.QSpacerItem(15,20,QtGui.QSizePolicy.Fixed,QtGui.QSizePolicy.Minimum)
        self.hboxlayout12.addItem(spacerItem21)

        self.lblDefaultColor = QtGui.QLabel(self.tabColors)
        self.lblDefaultColor.setPixmap(QtGui.QPixmap(":/images/misc/images/blank_36x36.png"))
        self.lblDefaultColor.setObjectName("lblDefaultColor")
        self.hboxlayout12.addWidget(self.lblDefaultColor)

        spacerItem22 = QtGui.QSpacerItem(11,20,QtGui.QSizePolicy.Fixed,QtGui.QSizePolicy.Minimum)
        self.hboxlayout12.addItem(spacerItem22)
        self.gridlayout4.addLayout(self.hboxlayout12,1,0,1,1)

        spacerItem23 = QtGui.QSpacerItem(20,17,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Fixed)
        self.gridlayout4.addItem(spacerItem23,0,0,1,1)

        self.vboxlayout3 = QtGui.QVBoxLayout()
        self.vboxlayout3.setMargin(0)
        self.vboxlayout3.setSpacing(6)
        self.vboxlayout3.setObjectName("vboxlayout3")

        spacerItem24 = QtGui.QSpacerItem(20,101,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Expanding)
        self.vboxlayout3.addItem(spacerItem24)

        self.btnColorAdd = QtGui.QToolButton(self.tabColors)
        self.btnColorAdd.setEnabled(True)
        self.btnColorAdd.setIcon(QtGui.QIcon(":/images/icons/images/icons/rightarrow.png"))
        self.btnColorAdd.setObjectName("btnColorAdd")
        self.vboxlayout3.addWidget(self.btnColorAdd)

        spacerItem25 = QtGui.QSpacerItem(20,20,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Fixed)
        self.vboxlayout3.addItem(spacerItem25)

        self.btnColorRemove = QtGui.QToolButton(self.tabColors)
        self.btnColorRemove.setEnabled(False)
        self.btnColorRemove.setIcon(QtGui.QIcon(":/images/icons/images/icons/leftarrow.png"))
        self.btnColorRemove.setObjectName("btnColorRemove")
        self.vboxlayout3.addWidget(self.btnColorRemove)

        spacerItem26 = QtGui.QSpacerItem(20,101,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Expanding)
        self.vboxlayout3.addItem(spacerItem26)
        self.gridlayout4.addLayout(self.vboxlayout3,0,1,3,1)

        self.vboxlayout4 = QtGui.QVBoxLayout()
        self.vboxlayout4.setMargin(0)
        self.vboxlayout4.setSpacing(6)
        self.vboxlayout4.setObjectName("vboxlayout4")

        self.lblMyCustomColors = QtGui.QLabel(self.tabColors)

        font = QtGui.QFont()
        font.setWeight(75)
        font.setBold(True)
        self.lblMyCustomColors.setFont(font)
        self.lblMyCustomColors.setAlignment(QtCore.Qt.AlignCenter)
        self.lblMyCustomColors.setObjectName("lblMyCustomColors")
        self.vboxlayout4.addWidget(self.lblMyCustomColors)

        self.listMyColors = QtGui.QListWidget(self.tabColors)
        self.listMyColors.setObjectName("listMyColors")
        self.vboxlayout4.addWidget(self.listMyColors)
        self.gridlayout4.addLayout(self.vboxlayout4,0,2,3,1)
        self.tabWidgetWidget.addTab(self.tabColors,"")

        self.tabMisc = QtGui.QWidget()
        self.tabMisc.setObjectName("tabMisc")

        self.gridlayout6 = QtGui.QGridLayout(self.tabMisc)
        self.gridlayout6.setMargin(9)
        self.gridlayout6.setSpacing(6)
        self.gridlayout6.setObjectName("gridlayout6")

        self.vboxlayout5 = QtGui.QVBoxLayout()
        self.vboxlayout5.setMargin(0)
        self.vboxlayout5.setSpacing(6)
        self.vboxlayout5.setObjectName("vboxlayout5")

        self.hboxlayout13 = QtGui.QHBoxLayout()
        self.hboxlayout13.setMargin(0)
        self.hboxlayout13.setSpacing(6)
        self.hboxlayout13.setObjectName("hboxlayout13")

        self.label_10 = QtGui.QLabel(self.tabMisc)
        self.label_10.setObjectName("label_10")
        self.hboxlayout13.addWidget(self.label_10)

        self.spinCacheExpiration = QtGui.QSpinBox(self.tabMisc)
        self.spinCacheExpiration.setMaximum(30)
        self.spinCacheExpiration.setMinimum(1)
        self.spinCacheExpiration.setProperty("value",QtCore.QVariant(1))
        self.spinCacheExpiration.setObjectName("spinCacheExpiration")
        self.hboxlayout13.addWidget(self.spinCacheExpiration)
        self.vboxlayout5.addLayout(self.hboxlayout13)

        self.hboxlayout14 = QtGui.QHBoxLayout()
        self.hboxlayout14.setMargin(0)
        self.hboxlayout14.setSpacing(6)
        self.hboxlayout14.setObjectName("hboxlayout14")

        self.label_3 = QtGui.QLabel(self.tabMisc)
        self.label_3.setObjectName("label_3")
        self.hboxlayout14.addWidget(self.label_3)

        self.leditBrowser = QtGui.QLineEdit(self.tabMisc)
        self.leditBrowser.setObjectName("leditBrowser")
        self.hboxlayout14.addWidget(self.leditBrowser)
        self.vboxlayout5.addLayout(self.hboxlayout14)

        spacerItem27 = QtGui.QSpacerItem(20,10,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Fixed)
        self.vboxlayout5.addItem(spacerItem27)

        self.label = QtGui.QLabel(self.tabMisc)
        self.label.setWordWrap(True)
        self.label.setObjectName("label")
        self.vboxlayout5.addWidget(self.label)

        spacerItem28 = QtGui.QSpacerItem(20,40,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Expanding)
        self.vboxlayout5.addItem(spacerItem28)
        self.gridlayout6.addLayout(self.vboxlayout5,0,0,1,1)
        self.tabWidgetWidget.addTab(self.tabMisc,"")
        self.gridlayout2.addWidget(self.tabWidgetWidget,2,0,1,1)
        self.tabWidget.addTab(self.tabWidget1,"")

        self.tabAbout = QtGui.QWidget()
        self.tabAbout.setObjectName("tabAbout")

        self.gridlayout7 = QtGui.QGridLayout(self.tabAbout)
        self.gridlayout7.setMargin(9)
        self.gridlayout7.setSpacing(6)
        self.gridlayout7.setObjectName("gridlayout7")

        self.vboxlayout6 = QtGui.QVBoxLayout()
        self.vboxlayout6.setMargin(0)
        self.vboxlayout6.setSpacing(6)
        self.vboxlayout6.setObjectName("vboxlayout6")

        self.lblDataProvidedBy = QtGui.QLabel(self.tabAbout)
        self.lblDataProvidedBy.setAlignment(QtCore.Qt.AlignCenter)
        self.lblDataProvidedBy.setOpenExternalLinks(True)
        self.lblDataProvidedBy.setObjectName("lblDataProvidedBy")
        self.vboxlayout6.addWidget(self.lblDataProvidedBy)

        self.lblTvRageLogo = QtGui.QLabel(self.tabAbout)
        self.lblTvRageLogo.setPixmap(QtGui.QPixmap(":/images/logos/images/logos/tvrage.jpg"))
        self.lblTvRageLogo.setAlignment(QtCore.Qt.AlignCenter)
        self.lblTvRageLogo.setObjectName("lblTvRageLogo")
        self.vboxlayout6.addWidget(self.lblTvRageLogo)
        self.gridlayout7.addLayout(self.vboxlayout6,1,0,1,1)

        self.hboxlayout15 = QtGui.QHBoxLayout()
        self.hboxlayout15.setMargin(0)
        self.hboxlayout15.setSpacing(6)
        self.hboxlayout15.setObjectName("hboxlayout15")

        self.lblNetShowsLogo = QtGui.QLabel(self.tabAbout)
        self.lblNetShowsLogo.setPixmap(QtGui.QPixmap(":/images/logos/images/logos/nextShows.png"))
        self.lblNetShowsLogo.setAlignment(QtCore.Qt.AlignHCenter|QtCore.Qt.AlignTop)
        self.lblNetShowsLogo.setObjectName("lblNetShowsLogo")
        self.hboxlayout15.addWidget(self.lblNetShowsLogo)

        self.vboxlayout7 = QtGui.QVBoxLayout()
        self.vboxlayout7.setMargin(0)
        self.vboxlayout7.setSpacing(6)
        self.vboxlayout7.setObjectName("vboxlayout7")

        self.lblNextShowsTitle = QtGui.QLabel(self.tabAbout)

        font = QtGui.QFont()
        font.setPointSize(12)
        font.setWeight(75)
        font.setBold(True)
        self.lblNextShowsTitle.setFont(font)
        self.lblNextShowsTitle.setObjectName("lblNextShowsTitle")
        self.vboxlayout7.addWidget(self.lblNextShowsTitle)

        self.lblNextShowsVersion = QtGui.QLabel(self.tabAbout)
        self.lblNextShowsVersion.setTextFormat(QtCore.Qt.AutoText)
        self.lblNextShowsVersion.setOpenExternalLinks(True)
        self.lblNextShowsVersion.setObjectName("lblNextShowsVersion")
        self.vboxlayout7.addWidget(self.lblNextShowsVersion)

        self.lbl_nextShowsGoogleCode = QtGui.QLabel(self.tabAbout)
        self.lbl_nextShowsGoogleCode.setAlignment(QtCore.Qt.AlignLeading|QtCore.Qt.AlignLeft|QtCore.Qt.AlignVCenter)
        self.lbl_nextShowsGoogleCode.setOpenExternalLinks(True)
        self.lbl_nextShowsGoogleCode.setObjectName("lbl_nextShowsGoogleCode")
        self.vboxlayout7.addWidget(self.lbl_nextShowsGoogleCode)

        spacerItem29 = QtGui.QSpacerItem(246,16,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Fixed)
        self.vboxlayout7.addItem(spacerItem29)

        self.lblLibsVersion = QtGui.QLabel(self.tabAbout)
        self.lblLibsVersion.setObjectName("lblLibsVersion")
        self.vboxlayout7.addWidget(self.lblLibsVersion)

        spacerItem30 = QtGui.QSpacerItem(246,16,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Fixed)
        self.vboxlayout7.addItem(spacerItem30)

        self.lblThanks = QtGui.QLabel(self.tabAbout)
        self.lblThanks.setObjectName("lblThanks")
        self.vboxlayout7.addWidget(self.lblThanks)

        spacerItem31 = QtGui.QSpacerItem(20,81,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Expanding)
        self.vboxlayout7.addItem(spacerItem31)
        self.hboxlayout15.addLayout(self.vboxlayout7)
        self.gridlayout7.addLayout(self.hboxlayout15,0,0,1,1)
        self.tabWidget.addTab(self.tabAbout,"")
        self.gridlayout.addWidget(self.tabWidget,0,0,1,1)

        self.hboxlayout16 = QtGui.QHBoxLayout()
        self.hboxlayout16.setMargin(0)
        self.hboxlayout16.setSpacing(6)
        self.hboxlayout16.setObjectName("hboxlayout16")

        self.lblFooterRelease = QtGui.QLabel(NextShowsConfig)
        self.lblFooterRelease.setEnabled(False)

        font = QtGui.QFont()
        self.lblFooterRelease.setFont(font)
        self.lblFooterRelease.setObjectName("lblFooterRelease")
        self.hboxlayout16.addWidget(self.lblFooterRelease)

        spacerItem32 = QtGui.QSpacerItem(251,27,QtGui.QSizePolicy.Expanding,QtGui.QSizePolicy.Minimum)
        self.hboxlayout16.addItem(spacerItem32)

        self.btnSave = QtGui.QPushButton(NextShowsConfig)
        self.btnSave.setEnabled(False)

        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Policy(0),QtGui.QSizePolicy.Policy(0))
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.btnSave.sizePolicy().hasHeightForWidth())
        self.btnSave.setSizePolicy(sizePolicy)
        self.btnSave.setIcon(QtGui.QIcon(":/images/icons/images/icons/save.png"))
        self.btnSave.setObjectName("btnSave")
        self.hboxlayout16.addWidget(self.btnSave)

        spacerItem33 = QtGui.QSpacerItem(10,20,QtGui.QSizePolicy.Fixed,QtGui.QSizePolicy.Minimum)
        self.hboxlayout16.addItem(spacerItem33)

        self.btnQuit = QtGui.QPushButton(NextShowsConfig)

        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Policy(0),QtGui.QSizePolicy.Policy(0))
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.btnQuit.sizePolicy().hasHeightForWidth())
        self.btnQuit.setSizePolicy(sizePolicy)
        self.btnQuit.setIcon(QtGui.QIcon(":/images/icons/images/icons/ok.png"))
        self.btnQuit.setAutoDefault(True)
        self.btnQuit.setObjectName("btnQuit")
        self.hboxlayout16.addWidget(self.btnQuit)
        self.gridlayout.addLayout(self.hboxlayout16,2,0,1,1)

        self.line = QtGui.QFrame(NextShowsConfig)
        self.line.setFrameShape(QtGui.QFrame.HLine)
        self.line.setFrameShadow(QtGui.QFrame.Sunken)
        self.line.setObjectName("line")
        self.gridlayout.addWidget(self.line,1,0,1,1)
        self.labSearchFor.setBuddy(self.leditLookup)
        self.lblMaxDispLines.setBuddy(self.spinMaxDispLines)
        self.lblFixedDispLines.setBuddy(self.spinFixedDispLines)
        self.lblMinDispLines.setBuddy(self.spinMinDispLines)
        self.lblNumPastDays.setBuddy(self.spinNumPastDays)
        self.lblFormat.setBuddy(self.leditFormat)
        self.lblColorsDay.setBuddy(self.spinColorsSingleDay)
        self.lblColorsFrom.setBuddy(self.spinColorsFrom)
        self.lblColorsTo.setBuddy(self.spinColorsTo)
        self.label_10.setBuddy(self.spinCacheExpiration)
        self.label_3.setBuddy(self.leditBrowser)

        self.retranslateUi(NextShowsConfig)
        self.tabWidget.setCurrentIndex(2)
        self.tabWidgetWidget.setCurrentIndex(0)
        QtCore.QMetaObject.connectSlotsByName(NextShowsConfig)
        NextShowsConfig.setTabOrder(self.tabWidget,self.leditLookup)
        NextShowsConfig.setTabOrder(self.leditLookup,self.btnLeditLookupClear)
        NextShowsConfig.setTabOrder(self.btnLeditLookupClear,self.btnLookup)
        NextShowsConfig.setTabOrder(self.btnLookup,self.listSearchResults)
        NextShowsConfig.setTabOrder(self.listSearchResults,self.chkbxFilter)
        NextShowsConfig.setTabOrder(self.chkbxFilter,self.btnShowAdd)
        NextShowsConfig.setTabOrder(self.btnShowAdd,self.btnShowRemove)
        NextShowsConfig.setTabOrder(self.btnShowRemove,self.listMyShows)
        NextShowsConfig.setTabOrder(self.listMyShows,self.btnSave)
        NextShowsConfig.setTabOrder(self.btnSave,self.btnQuit)
        NextShowsConfig.setTabOrder(self.btnQuit,self.tabWidgetWidget)
        NextShowsConfig.setTabOrder(self.tabWidgetWidget,self.spinNumPastDays)
        NextShowsConfig.setTabOrder(self.spinNumPastDays,self.radioDispFixedLines)
        NextShowsConfig.setTabOrder(self.radioDispFixedLines,self.spinFixedDispLines)
        NextShowsConfig.setTabOrder(self.spinFixedDispLines,self.radioDispAutoResize)
        NextShowsConfig.setTabOrder(self.radioDispAutoResize,self.spinMinDispLines)
        NextShowsConfig.setTabOrder(self.spinMinDispLines,self.spinMaxDispLines)
        NextShowsConfig.setTabOrder(self.spinMaxDispLines,self.leditFormat)
        NextShowsConfig.setTabOrder(self.leditFormat,self.btnFormatInfos)
        NextShowsConfig.setTabOrder(self.btnFormatInfos,self.btnSetDefaultColor)
        NextShowsConfig.setTabOrder(self.btnSetDefaultColor,self.radioSingleDay)
        NextShowsConfig.setTabOrder(self.radioSingleDay,self.spinColorsSingleDay)
        NextShowsConfig.setTabOrder(self.spinColorsSingleDay,self.radioDayRange)
        NextShowsConfig.setTabOrder(self.radioDayRange,self.spinColorsFrom)
        NextShowsConfig.setTabOrder(self.spinColorsFrom,self.spinColorsTo)
        NextShowsConfig.setTabOrder(self.spinColorsTo,self.btnSelectColor)
        NextShowsConfig.setTabOrder(self.btnSelectColor,self.btnColorAdd)
        NextShowsConfig.setTabOrder(self.btnColorAdd,self.btnColorRemove)
        NextShowsConfig.setTabOrder(self.btnColorRemove,self.listMyColors)
        NextShowsConfig.setTabOrder(self.listMyColors,self.spinCacheExpiration)
        NextShowsConfig.setTabOrder(self.spinCacheExpiration,self.leditBrowser)

    def retranslateUi(self, NextShowsConfig):
        NextShowsConfig.setWindowTitle(QtGui.QApplication.translate("NextShowsConfig", "nextShows configuration", None, QtGui.QApplication.UnicodeUTF8))
        self.btnShowAdd.setToolTip(QtGui.QApplication.translate("NextShowsConfig", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
        "p, li { white-space: pre-wrap; }\n"
        "</style></head><body style=\" font-family:\'Sans Serif\'; font-size:9pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Click to add the selected show to your tracked shows list.</p></body></html>", None, QtGui.QApplication.UnicodeUTF8))
        self.btnShowRemove.setToolTip(QtGui.QApplication.translate("NextShowsConfig", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
        "p, li { white-space: pre-wrap; }\n"
        "</style></head><body style=\" font-family:\'Sans Serif\'; font-size:9pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Click to remove the selected show from your tracked shows list.</p></body></html>", None, QtGui.QApplication.UnicodeUTF8))
        self.lblSearchResults.setText(QtGui.QApplication.translate("NextShowsConfig", "Search results:", None, QtGui.QApplication.UnicodeUTF8))
        self.chkbxFilter.setToolTip(QtGui.QApplication.translate("NextShowsConfig", "Check this if you want to filter out terminated shows", None, QtGui.QApplication.UnicodeUTF8))
        self.chkbxFilter.setText(QtGui.QApplication.translate("NextShowsConfig", "&Filter results", None, QtGui.QApplication.UnicodeUTF8))
        self.lblResultsDisplayed.setText(QtGui.QApplication.translate("NextShowsConfig", "Results displayed: %d/%d", None, QtGui.QApplication.UnicodeUTF8))
        self.lblMyShows.setText(QtGui.QApplication.translate("NextShowsConfig", "My shows:", None, QtGui.QApplication.UnicodeUTF8))
        self.lblTrackedShows.setText(QtGui.QApplication.translate("NextShowsConfig", "Tracked shows: %d", None, QtGui.QApplication.UnicodeUTF8))
        self.labSearchFor.setText(QtGui.QApplication.translate("NextShowsConfig", "&Search:", None, QtGui.QApplication.UnicodeUTF8))
        self.btnLeditLookupClear.setToolTip(QtGui.QApplication.translate("NextShowsConfig", "Clear text input", None, QtGui.QApplication.UnicodeUTF8))
        self.btnLookup.setText(QtGui.QApplication.translate("NextShowsConfig", "&Lookup...", None, QtGui.QApplication.UnicodeUTF8))
        self.label_4.setText(QtGui.QApplication.translate("NextShowsConfig", "Search / add / remove shows", None, QtGui.QApplication.UnicodeUTF8))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tabShows), QtGui.QApplication.translate("NextShowsConfig", "S&hows", None, QtGui.QApplication.UnicodeUTF8))
        self.lblTabWidgetInfo.setText(QtGui.QApplication.translate("NextShowsConfig", "Widget parameters", None, QtGui.QApplication.UnicodeUTF8))
        self.lblMaxDispLines.setText(QtGui.QApplication.translate("NextShowsConfig", "M&ax:", None, QtGui.QApplication.UnicodeUTF8))
        self.spinMaxDispLines.setSuffix(QtGui.QApplication.translate("NextShowsConfig", " line(s)", None, QtGui.QApplication.UnicodeUTF8))
        self.radioDispFixedLines.setText(QtGui.QApplication.translate("NextShowsConfig", "&Fixed number of lines:", None, QtGui.QApplication.UnicodeUTF8))
        self.lblFixedDispLines.setText(QtGui.QApplication.translate("NextShowsConfig", "N&umber:", None, QtGui.QApplication.UnicodeUTF8))
        self.spinFixedDispLines.setSuffix(QtGui.QApplication.translate("NextShowsConfig", " line(s)", None, QtGui.QApplication.UnicodeUTF8))
        self.radioDispAutoResize.setText(QtGui.QApplication.translate("NextShowsConfig", "Au&tomatic resizing:", None, QtGui.QApplication.UnicodeUTF8))
        self.lblMinDispLines.setText(QtGui.QApplication.translate("NextShowsConfig", "M&in:", None, QtGui.QApplication.UnicodeUTF8))
        self.spinMinDispLines.setSuffix(QtGui.QApplication.translate("NextShowsConfig", " line(s)", None, QtGui.QApplication.UnicodeUTF8))
        self.lblNumPastDays.setText(QtGui.QApplication.translate("NextShowsConfig", "&Number of past days to display:", None, QtGui.QApplication.UnicodeUTF8))
        self.spinNumPastDays.setSuffix(QtGui.QApplication.translate("NextShowsConfig", " day(s)", None, QtGui.QApplication.UnicodeUTF8))
        self.lblFormatPreview.setText(QtGui.QApplication.translate("NextShowsConfig", "<b>Preview:</b>", None, QtGui.QApplication.UnicodeUTF8))
        self.lblFormatExample.setText(QtGui.QApplication.translate("NextShowsConfig", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
        "p, li { white-space: pre-wrap; }\n"
        "</style></head><body style=\" font-family:\'Sans Serif\'; font-size:9pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Example:</span> <span style=\" font-weight:600;\">show:</span> Battlestar Galactica (2003), <span style=\" font-weight:600;\">title:</span> Litmus, <span style=\" font-weight:600;\">season:</span> 1, <span style=\" font-weight:600;\">episode:</span> 6</p></body></html>", None, QtGui.QApplication.UnicodeUTF8))
        self.lblFormat.setText(QtGui.QApplication.translate("NextShowsConfig", "F&ormat:", None, QtGui.QApplication.UnicodeUTF8))
        self.btnFormatInfos.setText(QtGui.QApplication.translate("NextShowsConfig", "?", None, QtGui.QApplication.UnicodeUTF8))
        self.tabWidgetWidget.setTabText(self.tabWidgetWidget.indexOf(self.tabDisplay), QtGui.QApplication.translate("NextShowsConfig", "&Display", None, QtGui.QApplication.UnicodeUTF8))
        self.grpbxCol.setTitle(QtGui.QApplication.translate("NextShowsConfig", "Custom colors", None, QtGui.QApplication.UnicodeUTF8))
        self.radioSingleDay.setText(QtGui.QApplication.translate("NextShowsConfig", "&Single day:", None, QtGui.QApplication.UnicodeUTF8))
        self.lblColorsDay.setText(QtGui.QApplication.translate("NextShowsConfig", "Da&y:", None, QtGui.QApplication.UnicodeUTF8))
        self.radioDayRange.setText(QtGui.QApplication.translate("NextShowsConfig", "Days &range:", None, QtGui.QApplication.UnicodeUTF8))
        self.lblColorsFrom.setText(QtGui.QApplication.translate("NextShowsConfig", "&From:", None, QtGui.QApplication.UnicodeUTF8))
        self.lblColorsTo.setText(QtGui.QApplication.translate("NextShowsConfig", "&To:", None, QtGui.QApplication.UnicodeUTF8))
        self.btnSelectColor.setText(QtGui.QApplication.translate("NextShowsConfig", "S&elect color", None, QtGui.QApplication.UnicodeUTF8))
        self.btnSetDefaultColor.setText(QtGui.QApplication.translate("NextShowsConfig", "Set default &color", None, QtGui.QApplication.UnicodeUTF8))
        self.btnColorAdd.setToolTip(QtGui.QApplication.translate("NextShowsConfig", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
        "p, li { white-space: pre-wrap; }\n"
        "</style></head><body style=\" font-family:\'Sans Serif\'; font-size:9pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Click to add the selected show to your tracked shows list.</p></body></html>", None, QtGui.QApplication.UnicodeUTF8))
        self.btnColorRemove.setToolTip(QtGui.QApplication.translate("NextShowsConfig", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
        "p, li { white-space: pre-wrap; }\n"
        "</style></head><body style=\" font-family:\'Sans Serif\'; font-size:9pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Click to remove the selected show from your tracked shows list.</p></body></html>", None, QtGui.QApplication.UnicodeUTF8))
        self.lblMyCustomColors.setText(QtGui.QApplication.translate("NextShowsConfig", "My custom colors:", None, QtGui.QApplication.UnicodeUTF8))
        self.tabWidgetWidget.setTabText(self.tabWidgetWidget.indexOf(self.tabColors), QtGui.QApplication.translate("NextShowsConfig", "Co&lors", None, QtGui.QApplication.UnicodeUTF8))
        self.label_10.setText(QtGui.QApplication.translate("NextShowsConfig", "Cache &expiration time:", None, QtGui.QApplication.UnicodeUTF8))
        self.spinCacheExpiration.setSuffix(QtGui.QApplication.translate("NextShowsConfig", " day(s)", None, QtGui.QApplication.UnicodeUTF8))
        self.label_3.setText(QtGui.QApplication.translate("NextShowsConfig", "B&rowser:", None, QtGui.QApplication.UnicodeUTF8))
        self.leditBrowser.setText(QtGui.QApplication.translate("NextShowsConfig", "firefox -remote \'openURL($url$,new-tab)\'", None, QtGui.QApplication.UnicodeUTF8))
        self.label.setText(QtGui.QApplication.translate("NextShowsConfig", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
        "p, li { white-space: pre-wrap; }\n"
        "</style></head><body style=\" font-family:\'Sans Serif\'; font-size:9pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" text-decoration: underline;\">Note:</span> nextShows will substitute the <span style=\" font-weight:600;\">$url$</span> variable with the corresponding episode URL.</p></body></html>", None, QtGui.QApplication.UnicodeUTF8))
        self.tabWidgetWidget.setTabText(self.tabWidgetWidget.indexOf(self.tabMisc), QtGui.QApplication.translate("NextShowsConfig", "&Misc", None, QtGui.QApplication.UnicodeUTF8))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tabWidget1), QtGui.QApplication.translate("NextShowsConfig", "&Widget", None, QtGui.QApplication.UnicodeUTF8))
        self.lblDataProvidedBy.setText(QtGui.QApplication.translate("NextShowsConfig", "Data provided by <a href=\"http://www.tvrage.com/\">www.tvrage.com</a>", None, QtGui.QApplication.UnicodeUTF8))
        self.lblNextShowsTitle.setText(QtGui.QApplication.translate("NextShowsConfig", "nextShows", None, QtGui.QApplication.UnicodeUTF8))
        self.lblNextShowsVersion.setText(QtGui.QApplication.translate("NextShowsConfig", "Version %s written by GCN.\n"
        "Released under the GNU GPL v2.", None, QtGui.QApplication.UnicodeUTF8))
        self.lbl_nextShowsGoogleCode.setText(QtGui.QApplication.translate("NextShowsConfig", "<a href=\"http://code.google.com/p/nextshows/\">http://code.google.com/p/nextshows/</a>", None, QtGui.QApplication.UnicodeUTF8))
        self.lblLibsVersion.setText(QtGui.QApplication.translate("NextShowsConfig", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
        "p, li { white-space: pre-wrap; }\n"
        "</style></head><body style=\" font-family:\'Sans Serif\'; font-size:9pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">Using:</span></p>\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">  - KDE: v%s</p>\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">  - Qt: v%s</p>\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">  - PyQt: v%s</p>\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">  - BeautifulSoup: v%s (internal)</p></body></html>", None, QtGui.QApplication.UnicodeUTF8))
        self.lblThanks.setText(QtGui.QApplication.translate("NextShowsConfig", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
        "p, li { white-space: pre-wrap; }\n"
        "</style></head><body style=\" font-family:\'Sans Serif\'; font-size:9pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">Thanks to the following people:</span></p>\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">  <img src=\":/images/flags/images/flags/es.gif\" alt=\"\" /> <span style=\" font-weight:600;\">Alexandre Vazquez</span> (testing, bug-hunting)</p>\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">  <img src=\":/images/flags/images/flags/fr.gif\" alt=\"\" /> <span style=\" font-weight:600;\">Emmanuel H.</span> (ideas, testing, bug-hunting)</p>\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">  <img src=\":/images/flags/images/flags/se.gif\" alt=\"\" /> <span style=\" font-weight:600;\">ge5239</span> (ideas, testing, bug-hunting)</p>\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">  <img src=\":/images/flags/images/flags/fr.gif\" alt=\"\" /> <span style=\" font-weight:600;\">Jean-Baptiste Sannier</span> (Qt4 help &amp; tips)</p>\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">  <img src=\":/images/flags/images/flags/fr.gif\" alt=\"\" /> <span style=\" font-weight:600;\">Joachim I.</span> (ideas, testing, bug-hunting)</p></body></html>", None, QtGui.QApplication.UnicodeUTF8))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tabAbout), QtGui.QApplication.translate("NextShowsConfig", "A&bout", None, QtGui.QApplication.UnicodeUTF8))
        self.lblFooterRelease.setText(QtGui.QApplication.translate("NextShowsConfig", "v%s", None, QtGui.QApplication.UnicodeUTF8))
        self.btnSave.setText(QtGui.QApplication.translate("NextShowsConfig", "S&ave", None, QtGui.QApplication.UnicodeUTF8))
        self.btnQuit.setText(QtGui.QApplication.translate("NextShowsConfig", "&Quit", None, QtGui.QApplication.UnicodeUTF8))

import NextShowsConfig_rc
