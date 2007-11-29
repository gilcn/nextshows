#!/usr/bin/env python
# -*- coding: utf-8 -*-
#######################################################################
# nextShows - Configuration GUI
# Copyright (C) 2006-2007 Gilles CHAUVIN <gcnweb@gmail.com>
# $Id$
#######################################################################
# Coding: UTF-8, 4 spaces indent, LF line terminator
#######################################################################
# This file is part of nextShows.
#
# nextShows is free software; you can redistribute  it  and/or  modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either  version 2  of  the License, or
# (at your option) any later version.
#
# nextShows is distributed in the hope that  it  will  be  useful, but
# WITHOUT  ANY  WARRANTY; without  even   the   implied   warranty  of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR  PURPOSE.  See  the  GNU
# General Public License for more details.
#
# You should have received a copy of the GNU  General  Public  License
# along  with  nextShows; if  not,  write   to   the   Free   Software
# Foundation, Inc.,
# 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#######################################################################

from libs.Globals import Globals
from libs.Config  import Config
from libs.TvRage  import TvRage

import libs.tools as tools

from NextShowsConfig_ui import Ui_NextShowsConfig
from FormatHelp import FormatHelp

from PyQt4.Qt import *

import time, sys


class NextShowsConfig(QDialog):
    def __init__(self, parent=None):
        #### Attributes
        self.searchResults        = []  # Returned search results
        self.dispSearchResults    = []  # Displayable search results
        self.myShows              = []  # My Tracked Shows
        self.myColors             = {}  # My custom colors
        self.myColors['default']  = ""
        self.myColors['ranges']   = []
        #
        self.modifFlag            = False   # Set to True if modifications were made
        #
        #self.lastColorUsed        = QColor( 0xFF, 0xFF, 0xFF )
        self.lastColorUsed        = "#FFFFFF"
        #
        self.desktopSize          = QDesktopWidget().screenGeometry() # Holds the desktop's Size (QRect)
        self.uiHelpDialogGeometry = QRect()  # Holds the Format Help Window's Geometry (QRect)
        self.uiHelpDialogSize     = QSize()  # Holds the Format Help Window's Size (QSize)

        #### Init UI
        QDialog.__init__(self, parent)
        self.ui = Ui_NextShowsConfig()
        self.ui.setupUi(self)   # Setup UI

        #### Initialize form (read config, set labels, etc...)
        self.initForm()

        #### Inititialize Format Help Dialog
        self.uiHelpDialog = FormatHelp()
        self.uiHelpDialog.setWindowFlags( Qt.Window )
        self.uiHelpDialogSize = QSize( self.uiHelpDialog.width(), self.uiHelpDialog.height() )
        self.uiHelpDialog.setMinimumSize( self.uiHelpDialogSize )   # Fix the size (ugly hack)
        self.uiHelpDialog.setMaximumSize( self.uiHelpDialogSize )   # Fix the size (ugly hack)

        #### Signals / Slots
        QObject.connect( self.ui.btnLookup, SIGNAL("clicked()"),      self.lookupShow )
        QObject.connect( self.uiHelpDialog, SIGNAL("hideWindow()"),   self.resetBtnFormatInfos )
        QObject.connect( self.ui.btnQuit,   SIGNAL("clicked()"),      self, SLOT("close()") )

        #### Make sure the first tabs are shown when we 1st launch the GUI
        self.ui.tabWidgetWidget.setCurrentIndex(0)
        self.ui.tabWidget.setCurrentIndex(0)


    ###########################################################################
    ##                       REACT TO USER INTERACTIONS                      ##
    ###########################################################################
    #### "Shows" Tab
    # Text Changed in Lookup QLineEdit
    @pyqtSignature("on_leditLookup_textChanged(const QString &)")
    def on_leditLookup_textChanged(self, qstring):
        text = str( qstring.toUtf8() )
        if text != "":
            self.ui.btnLookup.setEnabled(True)
            self.ui.btnLookup.setDefault(True)
        else:
            self.ui.btnLookup.setEnabled(False)
            self.ui.btnLookup.setDefault(False)

    # Click on "Clear Text"
    @pyqtSignature("on_btnLeditLookupClear_clicked()")
    def on_btnLeditLookupClear_clicked(self):
        self.ui.leditLookup.setText(u"")

    # Item on the search results selected
    @pyqtSignature("on_listSearchResults_currentRowChanged(int)")
    def on_listSearchResults_currentRowChanged(self, rowNum):
        if rowNum == -1: return
        self.ui.btnShowAdd.setEnabled( True )

    # Item double-clicked or add button clicked
    @pyqtSignature("on_listSearchResults_activated(const QModelIndex &)")
    def on_listSearchResults_activated(self, modelIndex):
        self.addToMyShows( modelIndex.row() )
    @pyqtSignature("on_btnShowAdd_clicked()")
    def on_btnShowAdd_clicked(self):
        self.addToMyShows( self.ui.listSearchResults.currentRow() )

    # Item on my shows selected
    @pyqtSignature("on_listMyShows_currentRowChanged(int)")
    def on_listMyShows_currentRowChanged(self, rowNum):
        if rowNum == -1: return
        self.ui.btnShowRemove.setEnabled( True )

    # "My Shows" item double-clicked or remove button clicked
    @pyqtSignature("on_listMyShows_activated(const QModelIndex &)")
    def on_listMyShows_activated(self, modelIndex):
        self.removeFromMyShows( modelIndex.row() )
    @pyqtSignature("on_btnShowRemove_clicked()")
    def on_btnShowRemove_clicked(self):
        self.removeFromMyShows( self.ui.listMyShows.currentRow() )

    # Filter state changed
    @pyqtSignature("on_chkbxFilter_stateChanged(int)")
    def on_chkbxFilter_stateChanged(self, state):
        self.displaySearchResults()

    #### "Widget" Tab
    #### "Widget"->"Display" Tab
    # Past days value changed
    @pyqtSignature("on_spinNumPastDays_valueChanged(int)")
    def on_spinNumPastDays_valueChanged(self, value):
        # Need to save
        self.saveRequired()

    # Click on Fixed Size radio
    @pyqtSignature("on_radioDispFixedLines_toggled(bool)")
    def on_radioDispFixedLines_toggled(self, checked):
        if checked:
            # Enable Fixed Size
            self.ui.lblFixedDispLines.setEnabled(True)
            self.ui.spinFixedDispLines.setEnabled(True)
        else:
            # Disable Fixed Size
            self.ui.lblFixedDispLines.setEnabled(False)
            self.ui.spinFixedDispLines.setEnabled(False)
        # Need to save
        self.saveRequired()

    # Fixed lines value changed
    @pyqtSignature("on_spinFixedDispLines_valueChanged(int)")
    def on_spinFixedDispLines_valueChanged(self, value):
        # Need to save
        self.saveRequired()

    # Click on Automatic Resize radio
    @pyqtSignature("on_radioDispAutoResize_toggled(bool)")
    def on_radioDispAutoResize_toggled(self, checked):
        if checked:
            # Enable Automatic Size
            self.ui.lblMinDispLines.setEnabled(True)
            self.ui.lblMaxDispLines.setEnabled(True)
            self.ui.spinMinDispLines.setEnabled(True)
            self.ui.spinMaxDispLines.setEnabled(True)
        else:
            # Disable Automatic Size
            self.ui.lblMinDispLines.setEnabled(False)
            self.ui.lblMaxDispLines.setEnabled(False)
            self.ui.spinMinDispLines.setEnabled(False)
            self.ui.spinMaxDispLines.setEnabled(False)
        # Need to save
        self.saveRequired()

    # MinDispLines Changed
    @pyqtSignature("on_spinMinDispLines_valueChanged(int)")
    def on_spinMinDispLines_valueChanged(self, newValue):
        currentMaxValue = self.ui.spinMaxDispLines.value()
        maxMaxValue     = self.ui.spinMaxDispLines.maximum()
        if newValue >= currentMaxValue:
            if currentMaxValue < maxMaxValue:
                self.ui.spinMaxDispLines.setValue( newValue+1 )
            else:
                self.ui.spinMinDispLines.setValue( newValue-1 )
        # Need to save
        self.saveRequired()

    # MaxDispLines Changed
    @pyqtSignature("on_spinMaxDispLines_valueChanged(int)")
    def on_spinMaxDispLines_valueChanged(self, newValue):
        currentMinValue = self.ui.spinMinDispLines.value()
        minMinValue     = self.ui.spinMinDispLines.minimum()
        if newValue <= currentMinValue:
            if currentMinValue > minMinValue:
                self.ui.spinMinDispLines.setValue( newValue-1 )
            else:
                self.ui.spinMaxDispLines.setValue( newValue+1 )
        # Need to save
        self.saveRequired()

    # Click on checkable Format Info Button
    @pyqtSignature("on_btnFormatInfos_clicked()")
    def on_btnFormatInfos_clicked(self):
        # If this is the 1st time we ask for the Help Window
        # compute its geometry (relative to the main window)
        if not self.uiHelpDialogGeometry.isValid():
            # Y pos
            yPos = self.pos().y() + ( ( self.height() - self.uiHelpDialogSize.height() ) / 2 )
            # Choose the best pos (Left or Right) depending of the main window pos
            coordsRight = self.desktopSize.width() - ( self.pos().x() + self.width() )
            if coordsRight > self.pos().x():
                xPos = self.pos().x() + self.width()
            else:
                xPos = self.pos().x() - self.uiHelpDialogSize.width()
            self.uiHelpDialogGeometry = QRect( xPos,
                                                      yPos,
                                                      self.uiHelpDialogSize.width(),
                                                      self.uiHelpDialogSize.height() )

        if self.ui.btnFormatInfos.isChecked():
            self.uiHelpDialog.setGeometry( self.uiHelpDialogGeometry )
            self.uiHelpDialog.show()
        else:
            self.uiHelpDialogGeometry = self.uiHelpDialog.geometry()
            self.uiHelpDialog.hide()

    # Format text changed
    @pyqtSignature("on_leditFormat_textChanged(const QString &)")
    def on_leditFormat_textChanged(self, QString):
        text = str( QString )
        self.refreshFormatPreview(text)
        # Need to save
        self.saveRequired()

    # Resets the button state if help window is closed
    def resetBtnFormatInfos(self):
        self.ui.btnFormatInfos.setChecked(False)
        self.on_btnFormatInfos_clicked()


    #### "Widget"->"Colors" tab
    # Set Default Color clicked
    @pyqtSignature("on_btnSetDefaultColor_clicked()")
    def on_btnSetDefaultColor_clicked(self):
        selColor = QColorDialog.getColor(QColor(self.myColors['default']), self)
        if not selColor.isValid():
            tools.msgDebug(u"Canceled by user!", __name__)
            return
        tools.msgDebug( u"Selected color: #%02X%02X%02X" % ( selColor.red(), selColor.green(), selColor.blue() ), __name__ )
        self.ui.lblDefaultColor.setPixmap( self.drawPreviewColor( selColor, 36, 36 ) )
        self.myColors['default'] = str( selColor.name() )
        # Need to save
        self.saveRequired()

    # Select Color clicked
    @pyqtSignature("on_btnSelectColor_clicked()")
    def on_btnSelectColor_clicked(self):
        selColor = QColorDialog.getColor(QColor(self.lastColorUsed), self)
        if not selColor.isValid():
            tools.msgDebug(u"Canceled by user!", __name__)
            return
        tools.msgDebug( u"Selected color: #%02X%02X%02X" % ( selColor.red(), selColor.green(), selColor.blue() ), __name__ )
        self.ui.lblSelectColor.setPixmap( self.drawPreviewColor( selColor, 36, 36 ) )
        self.lastColorUsed = str( selColor.name() )

    # Click on Single Day radio
    @pyqtSignature("on_radioSingleDay_toggled(bool)")
    def on_radioSingleDay_toggled(self, checked):
        if checked:
            # Enable Single Day
            self.ui.lblColorsDay.setEnabled(True)
            self.ui.spinColorsSingleDay.setEnabled(True)
        else:
            # Disable Single Day
            self.ui.lblColorsDay.setEnabled(False)
            self.ui.spinColorsSingleDay.setEnabled(False)

    # Click on Automatic Resize radio
    @pyqtSignature("on_radioDayRange_toggled(bool)")
    def on_radioDayRange_toggled(self, checked):
        if checked:
            # Enable Range
            self.ui.lblColorsFrom.setEnabled(True)
            self.ui.lblColorsTo.setEnabled(True)
            self.ui.spinColorsFrom.setEnabled(True)
            self.ui.spinColorsTo.setEnabled(True)
        else:
            # Disable Range
            self.ui.lblColorsFrom.setEnabled(False)
            self.ui.lblColorsTo.setEnabled(False)
            self.ui.spinColorsFrom.setEnabled(False)
            self.ui.spinColorsTo.setEnabled(False)

    # Range From
    @pyqtSignature("on_spinColorsFrom_editingFinished()")
    def on_spinColorsFrom_editingFinished(self):
        fromValue  = self.ui.spinColorsFrom.value()
        toValue    = self.ui.spinColorsTo.value()
        maxToValue = self.ui.spinColorsTo.maximum()
        if fromValue >= toValue:
            if toValue < maxToValue:
                self.ui.spinColorsTo.setValue( fromValue+1 )
            else:
                self.ui.spinColorsFrom.setValue( fromValue-1 )

    # Range To
    @pyqtSignature("on_spinColorsTo_editingFinished()")
    def on_spinColorsTo_editingFinished(self):
        fromValue    = self.ui.spinColorsFrom.value()
        toValue      = self.ui.spinColorsTo.value()
        minFromValue = self.ui.spinColorsFrom.minimum()
        if toValue <= fromValue:
            if fromValue > minFromValue:
                self.ui.spinColorsFrom.setValue( toValue-1 )
            else:
                self.ui.spinColorsTo.setValue( toValue+1 )

    # Item on my colors selected
    @pyqtSignature("on_listMyColors_currentRowChanged(int)")
    def on_listMyColors_currentRowChanged(self, rowNum):
        if rowNum == -1: return
        self.ui.btnColorRemove.setEnabled( True )
        rangeStart, rangeStop, color = self.myColors['ranges'][rowNum]
        if rangeStart == rangeStop:
            self.ui.radioSingleDay.setChecked( True )
            self.ui.spinColorsSingleDay.setValue( rangeStart )
        else:
            self.ui.radioDayRange.setChecked( True )
            self.ui.spinColorsFrom.setValue( rangeStart )
            self.ui.spinColorsTo.setValue( rangeStop )
        self.lastColorUsed = color
        self.ui.lblSelectColor.setPixmap( self.drawPreviewColor( self.lastColorUsed, 36, 36 ) )

    # Color Add clicked
    @pyqtSignature("on_btnColorAdd_clicked()")
    def on_btnColorAdd_clicked(self):
        self.ui.spinColorsFrom.clearFocus()
        self.ui.spinColorsTo.clearFocus()
        self.addToMyColors()

    # "My colors" item double-clicked or remove button clicked
    @pyqtSignature("on_listMyColors_activated(const QModelIndex &)")
    def on_listMyColors_activated(self, modelIndex):
        self.removeFromMyColors( modelIndex.row() )
    @pyqtSignature("on_btnColorRemove_clicked()")
    def on_btnColorRemove_clicked(self):
        self.removeFromMyColors( self.ui.listMyColors.currentRow() )


    #### "Widget"->"Misc" tab
    # Cache expiration time changed
    @pyqtSignature("on_spinCacheExpiration_valueChanged(int)")
    def on_spinCacheExpiration_valueChanged(self, newValue):
        # Need to save
        self.saveRequired()

    # Text Changed in Browser
    @pyqtSignature("on_leditBrowser_textChanged(const QString &)")
    def on_leditBrowser_textChanged(self, qstring):
        # Need to save
        self.saveRequired()

    #### General
    # Save button clicked
    @pyqtSignature("on_btnSave_clicked()")
    def on_btnSave_clicked(self):
        # import thread
        # thread.start_new_thread( self.saveConfig, ("",) )
        self.saveConfig()

    # React to close event
    def closeEvent(self, event):
        if self.modifFlag:
            yesno = QMessageBox().question(self,
                                                 "Attention",
                                                 "Changes were made!\n" +
                                                 "Are you sure you want to quit without saving?",
                                                 QMessageBox.Yes, QMessageBox.No)
            if yesno == QMessageBox().No:
                event.ignore()
                return

        # User wants to quit
        # Make sure Config() isn't opened
        self.hide()
        self.uiHelpDialog.hide()
        while Config.LOCK:
            tools.msgDebug(u"Waiting for config to be written before exiting...", __name__)
            time.sleep(0.2)

        tools.msgDebug(u"Exiting...", __name__)

###############################################################################


    #############################################
    ## Fills the form with the relevant values ##
    #############################################
    def initForm(self):
        # 20070920 - FEATURE LOSS
        # tvrage.com changed their markup and doesn't provide the required
        # infos anymore. No other choice but removing this option :(.
        self.ui.chkbxFilter.setVisible(False)

        # 1st tab labels
        self.ui.lblResultsDisplayed.setText( u"Displayed results: 0/0" )
        self.ui.lblTrackedShows.setText( u"Tracked shows: 0" )

        # Format Sample
        fmtSample = u"<u><b>Sample:</b></u> <b>show:</b> %s, <b>title:</b> %s, <b>season</b>: %d, <b>episode</b>: %d" % (
                      Globals().sampleEpisode['show'],
                      Globals().sampleEpisode['title'],
                      Globals().sampleEpisode['season'],
                      Globals().sampleEpisode['episode'] )
        self.ui.lblFormatSample.setText( fmtSample )

        #### Versions
        version = Globals().versions
        # nextShows Footer Release
        labelContent=str(self.ui.lblFooterRelease.text())
        self.ui.lblFooterRelease.setText(labelContent % version['nextShows'])
        # nextShows Release (About tab)
        labelContent=str(self.ui.lblNextShowsVersion.text())
        self.ui.lblNextShowsVersion.setText(labelContent % version['nextShows'])
        # Libs releases (About tab)
        # Python version
        a,b,c,d,e = sys.version_info
        pythonVersion = "%d.%d.%d" % (a, b, c)
        #
        labelContent=str(self.ui.lblLibsVersion.text())
        self.ui.lblLibsVersion.setText(labelContent % (
            pythonVersion,
            version["BeautifulSoup"],
            QT_VERSION_STR,
            PYQT_VERSION_STR,
            version["KDE"]) )


        #### Default values
        self.ui.spinNumPastDays.setMinimum(0)
        self.ui.spinNumPastDays.setMaximum(99)
        #self.ui.spinNumPastDays.setValue(1)
        self.ui.spinFixedDispLines.setMinimum(1)
        self.ui.spinFixedDispLines.setMaximum(50)
        #self.ui.spinFixedDispLines.setValue(10)
        self.ui.spinMinDispLines.setMinimum(1)
        self.ui.spinMinDispLines.setMaximum(49)
        #self.ui.spinMinDispLines.setValue(1)
        self.ui.spinMaxDispLines.setMinimum(2)
        self.ui.spinMaxDispLines.setMaximum(50)
        #self.ui.spinMaxDispLines.setValue(10)
        #
        self.ui.spinColorsSingleDay.setMinimum(-99)
        self.ui.spinColorsSingleDay.setMaximum(99)
        self.ui.spinColorsSingleDay.setValue(0)
        self.ui.spinColorsFrom.setMinimum(-99)
        self.ui.spinColorsFrom.setMaximum(98)
        self.ui.spinColorsFrom.setValue(0)
        self.ui.spinColorsTo.setMinimum(-98)
        self.ui.spinColorsTo.setMaximum(99)
        self.ui.spinColorsTo.setValue(10)

        # default color for "Select color"
        self.ui.lblSelectColor.setPixmap( self.drawPreviewColor( self.lastColorUsed, 36, 36 ) )


        ####
        #### Read config
        ####
        tools.msgDebug(u"Reading config...", __name__)
        config = Config()

        # Enable/Disable DEBUG
        if config.getboolean("main", "debug") == False:
            tools.msgDebug("Disabling debug messages !", __name__)
            Globals.DEBUG = False

        # Get Data
        self.myShows  = config.getShows()
        self.displayMyShows()
        self.myColors = config.getColors()
        self.ui.lblDefaultColor.setPixmap( self.drawPreviewColor( self.myColors['default'], 36, 36 ) )
        self.displayMyColors()

        if config.get("display", "type") == "Fixed":
            self.ui.radioDispFixedLines.setChecked( True )
        else:
            self.ui.radioDispAutoResize.setChecked( True )

        self.ui.spinNumPastDays.setValue(    int( config.get( "display", "past_days"   ) ) )
        self.ui.spinFixedDispLines.setValue( int( config.get( "display", "lines_fixed" ) ) )
        self.ui.spinMinDispLines.setValue(   int( config.get( "display", "lines_min"   ) ) )
        self.ui.spinMaxDispLines.setValue(   int( config.get( "display", "lines_max"   ) ) )
        self.ui.leditFormat.setText( config.get( "display", "format" ) )
        self.refreshFormatPreview( str(self.ui.leditFormat.text()) )

        self.ui.spinCacheExpiration.setValue( int( config.get( "misc", "cache_expiration" ) ) )
        self.ui.leditBrowser.setText( config.get( "misc", "browser" ) )

        config.close()

        # Reset "Save" button state
        self.saveRequired(False)

        tools.msgDebug(u"Done!", __name__)


    #######################################
    ## Refreshes the Format Result label ##
    #######################################
    def refreshFormatPreview(self, text):
        testFormat  = tools.formatEpisode( Globals().sampleEpisode, text )
        self.ui.lblFormatPreview.setText( u"<u><b>Preview:</b></u> %s" % testFormat )


###############################################################################


    #######################################################
    ## Draw a preview colour surrounded by a black frame ##
    #######################################################
    def drawPreviewColor(self, color, width, height):
        pixmap  = QPixmap( QSize( width, height ) )
        pixmap.fill( QColor( color ) )
        # Draw black frame
        painter = QPainter()
        painter.begin( pixmap )
        painter.setPen( QPen( QColor( 0x00, 0x00, 0x00 ) ) )
        painter.drawRect( 0, 0, width-1, height-1 )
        painter.end()

        return pixmap

    ############################################
    ## Draw a flag surrounded by a grey frame ##
    ############################################
    def drawFlag(self, flag):
        flagFile = ":/images/flags/images/flags/%s.gif" % flag
        if not QFile().exists( flagFile ):   # If we don't have the icon, substitute with "blank.gif"
            iconFile = ":/images/flags/images/flags/blank.gif"

        pixmapFlag = QPixmap( flagFile )
        pixmap     = QPixmap( QSize( pixmapFlag.width()+2, pixmapFlag.height()+2 ) )
        painter    = QPainter()
        painter.begin( pixmap )
        painter.drawPixmap( QPoint( 1, 1 ), pixmapFlag )
        painter.setPen( QPen( QColor( 0x77, 0x77, 0x77 ) ) )
        painter.drawRect( 0, 0, pixmapFlag.width()+1, pixmapFlag.height()+1 )
        painter.end()

        return QIcon( pixmap )    # Return a QIcon() suitable for QListWidgetItem()


    ###########################
    ## Find a show on tvrage ##
    ###########################
    def lookupShow(self):
        # Change button...
        btnOldText = self.ui.btnLookup.text()
        self.ui.btnLookup.setEnabled( False )
        self.ui.btnLookup.setText( u"Fetching..." )
        self.repaint()
        qApp.processEvents()

        # Make request
        keyword = self.ui.leditLookup.text().toUtf8()
        parser  = TvRage()
        self.searchResults = parser.search( keyword )

        # Display the results
        self.displaySearchResults()

        # Restore button
        self.ui.btnLookup.setEnabled( True )
        self.ui.btnLookup.setText( btnOldText )
        self.ui.btnLookup.setChecked( False )


    #################################
    ## Displays the search results ##
    #################################
    def displaySearchResults(self):
        # Clear the list and enable various widgets
        self.ui.listSearchResults.clear()
        self.ui.lblResultsDisplayed.setEnabled( True )
        self.ui.chkbxFilter.setEnabled( True )

        # Find displayable shows
        self.dispSearchResults = []
        if self.ui.chkbxFilter.checkState() == Qt.Unchecked:
            self.dispSearchResults = self.searchResults
        else:
            for show in self.searchResults:
                if show["year_end"] == "????":
                    self.dispSearchResults.append(show)

        # If there are no results...
        if len(self.dispSearchResults) == 0:
            self.ui.listSearchResults.setEnabled( False )
            if len(self.searchResults) == 0:
                self.ui.listSearchResults.addItem( u"No results found!" )
                self.ui.chkbxFilter.setEnabled( False )
            else:
                self.ui.listSearchResults.addItem( u"Results found but none to display!" )
            self.ui.btnShowAdd.setEnabled( False )
        else:
            self.ui.listSearchResults.setEnabled( True )
        self.ui.lblResultsDisplayed.setText( u"Displayed results: %d/%d" % ( len( self.dispSearchResults ), len( self.searchResults ) ) )

        # Proceed with display
        listIdx   = 0
        showLines = []
        for show in self.dispSearchResults:
            showLines.append( listIdx )
            showLines[listIdx] = QListWidgetItem( self.ui.listSearchResults )
            #showLines[listIdx].setText( u"[%s-%s] %s" % ( show["year_begin"], show["year_end"], show["name"] ) )
            showLines[listIdx].setText( u"%s" % show["name"] )
            showLines[listIdx].setIcon( self.drawFlag( show["flag"] ) )
            font = showLines[listIdx].font()
            if show["year_end"] == "????":
                font.setBold( True )
                showLines[listIdx].setForeground( QBrush( QColor( 0x00, 0x00, 0x00 ) ) )
            else:
                font.setItalic( True )
                showLines[listIdx].setForeground( QBrush( QColor( 0x55, 0x55, 0x55 ) ) )
            showLines[listIdx].setFont( font )
            listIdx += 1



    #################################
    ## Adds the show to "My Shows" ##
    #################################
    def addToMyShows(self, index):
        selectedShow = self.dispSearchResults[index]

        # Make sure the requested show isn't already tracked
        # For that, check the id (which is unique)
        checkShow = [ item['id'] for item in self.myShows if item['id'] == selectedShow['id']]
        if selectedShow['id'] in checkShow:
            tools.msgDebug(u"""Show already in "My Shows". Can't add!""", __name__)
            QMessageBox().information(self,
                                            "Information",
                                            'Cannot add "%s".\n' % selectedShow['name'] +
                                            'This show is already tracked.',
                                            QMessageBox.Ok)
            return

        # Tell the user if the show is terminated
        if selectedShow['year_end'] != "????":
            yesno = QMessageBox().question(self,
                                                 "Attention",
                                                 '"%s" seem to be terminated.\n' % selectedShow['name'] +
                                                 "Adding it to your list would be pointless.\n\n" +
                                                 "Are you sure you still want to continue?",
                                                 QMessageBox.Yes, QMessageBox.No)
            if yesno == QMessageBox().No:
                return

        # Add the show to our list
        self.myShows.append( selectedShow )

        # Sort the shows by names
        self.myShows = tools.sortShowsByName( self.myShows )

        # Need to save...
        self.saveRequired()


        #################################################
        ## REMOVEME
        #################################################
        #wct = TestConf( self.myShows )
        #wct.start()
        #################################################

        # Refresh list
        self.displayMyShows()


    ########################################
    ## Remove a show from "My Shows" list ##
    ########################################
    def removeFromMyShows(self, index):
        selectedShow = self.myShows[index]

        # Ask user before deletion
        yesno = QMessageBox().question(self,
                                             "Attention",
                                             'Are you sure you want to remove "%s" ?' % selectedShow['name'],
                                             QMessageBox.Yes, QMessageBox.No)
        if yesno == QMessageBox().No:
            return

        # So be it...
        tmpMyShows = []
        for show in self.myShows:
            if show['id'] != selectedShow['id']:
                tmpMyShows.append( show )
        self.myShows = tmpMyShows

        # Need to save...
        self.saveRequired()

        # Refresh List
        self.displayMyShows()


    ###################################
    ## Refreshes the "My Shows" list ##
    ###################################
    def displayMyShows(self):
        # Clear the list
        self.ui.listMyShows.clear()

        # If the list is empty...
        if len(self.myShows) == 0:
            self.ui.btnShowRemove.setEnabled( False )
            self.ui.listMyShows.setEnabled( False )
        else:
            self.ui.listMyShows.setEnabled( True )

        # Display our tracked shows
        listIdx   = 0
        showLines = []
        for show in self.myShows:
            showLines.append( listIdx )
            showLines[listIdx] = QListWidgetItem( self.ui.listMyShows )
            #showLines[listIdx].setText( u"[%s-%s] %s" % ( show["year_begin"], show["year_end"], show["name"] ) )
            showLines[listIdx].setText( u"%s" % show["name"] )
            showLines[listIdx].setIcon( self.drawFlag( show["flag"] ) )
            font = showLines[listIdx].font()
            if show["year_end"] == "????":
                font.setBold( True )
                showLines[listIdx].setForeground( QBrush( QColor( 0x00, 0x00, 0x00 ) ) )
                showLines[listIdx].setToolTip(u"Show still running...")
            else:
                font.setItalic( True )
                showLines[listIdx].setForeground( QBrush( QColor( 0x55, 0x55, 0x55 ) ) )
                showLines[listIdx].setToolTip(u"%s ended in %d!" % (show['name'], int(show["year_end"])))
            showLines[listIdx].setFont( font )
            listIdx += 1

        # Refresh Tracked shows count
        self.ui.lblTrackedShows.setText( u"Tracked shows: %d" % len(self.myShows) )


    #######################################
    ## Add selected color to "My Colors" ##
    #######################################
    def addToMyColors(self):
        if self.ui.radioSingleDay.isChecked():
            rangeStart = self.ui.spinColorsSingleDay.value()
            rangeStop  = rangeStart
        else:
            rangeStart = self.ui.spinColorsFrom.value()
            rangeStop  = self.ui.spinColorsTo.value()

        # Just keep the ranges (excluding color names)
        chkRanges = [ (range[0],range[1]) for range in self.myColors['ranges'] ]
        # Append our new range
        chkRanges.append( ( rangeStart, rangeStop ) )

        # if True, ranges are overlapping (baaaad)
        if tools.checkRangeOverlap( chkRanges ):
            if rangeStop == rangeStart:
                message = u"Overlapping detected.\nCannot add color for that day."
            else:
                message = u"Overlapping ranges detected (%d → %d).\nCannot add color for the specified range." % (rangeStart ,rangeStop)
            QMessageBox().information(self,
                                            "Information",
                                            message,
                                            QMessageBox.Ok)
            return

        # Looks like everything went fine... Adding new color...
        self.myColors['ranges'].append( ( rangeStart, rangeStop, self.lastColorUsed ) )

        # ...and sort everything
        self.myColors['ranges'] = tools.sortColorsByRange( self.myColors['ranges'] )

        # Display colors
        self.displayMyColors()

        # Need to save
        self.saveRequired()


    ##################
    ## Remove color ##
    ##################
    def removeFromMyColors(self, index):
        selectedColor = self.myColors['ranges'][index]
        rangeStart, rangeStop, selColor = selectedColor

        # Ask user before deletion
        yesno = QMessageBox().question(self,
                                             "Attention",
                                             'Are you sure you want to remove this color ?',
                                             QMessageBox.Yes, QMessageBox.No)
        if yesno == QMessageBox().No:
            return

        # So be it...
        tmpMyColors = []
        for color in self.myColors['ranges']:
            if color[0] != rangeStart and color[1] != rangeStop:
                tmpMyColors.append( color )
        self.myColors['ranges'] = tmpMyColors

        # Need to save...
        self.saveRequired()

        # Refresh List
        self.displayMyColors()


    #########################
    ## Display "My Colors" ##
    #########################
    def displayMyColors(self):
        # Clear the list
        self.ui.listMyColors.clear()

        # If the list is empty...
        if len(self.myColors['ranges']) == 0:
            self.ui.btnColorRemove.setEnabled( False )
            self.ui.listMyColors.setEnabled( False )
        else:
            self.ui.listMyColors.setEnabled( True )

        # Display My colors
        listIdx    = 0
        colorLines = []
        for color in self.myColors['ranges']:
            if color[0] == color[1]:
                text = u"Day: %d" % color[0]
            else:
                text = u"Days: %d → %d" % (color[0], color[1])
            colorLines.append( listIdx )
            colorLines[listIdx] = QListWidgetItem( self.ui.listMyColors )
            colorLines[listIdx].setText( text )
            icon = QIcon( self.drawPreviewColor( color[2], 16, 16 ) )
            colorLines[listIdx].setIcon( icon )
            listIdx +=1


    #####################################
    ## Data were changed! Need to save ##
    #####################################
    def saveRequired(self, state=True):
        if state == True:
            self.modifFlag = True
            self.ui.btnSave.setEnabled( True )
            #tools.msgDebug(u"Changes made, need to save...", __name__)
        else:
            self.modifFlag = False
            self.ui.btnSave.setEnabled( False )
            #tools.msgDebug(u"Save state reset!", __name__)


    #################
    ## Save Config ##
    #################
    #def saveConfig(self, dummy):   # Changed because of crashes with Debian/Kubuntu
    def saveConfig(self):
        self.saveRequired( False )  # Reset save button state

        # Disable quit button
        self.ui.btnQuit.setEnabled( False )

        # Save button icon & text
        s_btnIcon = self.ui.btnSave.icon()
        s_btnText = self.ui.btnSave.text()
        self.ui.btnSave.setText(u"Saving...")
        self.ui.btnSave.setIcon(QtGui.QIcon())
        self.repaint()
        QtGui.qApp.processEvents()

        tools.msgDebug(u"Saving configuration...", __name__)

        config = Config()

        # Save Data
        config.setShows( self.myShows )
        config.setColors( self.myColors )

        if self.ui.radioDispFixedLines.isChecked():
            value = "Fixed"
        else:
            value = "Automatic"
        config.set( "display", "type", value )

        config.set( "display", "past_days",     str( self.ui.spinNumPastDays.value()     ) )
        config.set( "display", "lines_fixed",   str( self.ui.spinFixedDispLines.value()  ) )
        config.set( "display", "lines_min",     str( self.ui.spinMinDispLines.value()    ) )
        config.set( "display", "lines_max",     str( self.ui.spinMaxDispLines.value()    ) )
        config.set( "display", "format",        str( self.ui.leditFormat.text()          ) )

        config.set( "misc", "cache_expiration", str( self.ui.spinCacheExpiration.value() ) )
        config.set( "misc", "browser",          str( self.ui.leditBrowser.text()         ) )

        # Set this so that the widget knows something changed
        config.set( "main", "config_changed", "True" )

        tools.msgDebug(u"Saving done!", __name__)

        config.close()  # Destroy Config()

        # Restore buttons
        self.ui.btnSave.setIcon( s_btnIcon )
        self.ui.btnSave.setText( s_btnText )
        self.ui.btnQuit.setEnabled( True )
