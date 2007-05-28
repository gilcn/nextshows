#!/usr/bin/env python
# -*- coding: utf-8 -*-
#######################################################################
# nextShows
# Copyright (C) 2006-2007 Gilles CHAUVIN <gcnweb@gmail.com>
# $Id$
#######################################################################
# Coding: UTF-8, 4 spaces indent, LF line terminator
#######################################################################
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2  of  the  License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be  useful, but
# WITHOUT  ANY  WARRANTY;  without  even  the   implied   warranty  of
# MERCHANTABILITY or FITNESS FOR A  PARTICULAR  PURPOSE. See  the  GNU
# General Public License for more details.
#
# You should have received a copy of the GNU  General  Public  License
# along with  this  program;  if  not,  write  to  the  Free  Software
# Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
#######################################################################

from   libs.Applet  import Applet
from   libs.Cache   import Cache
from   libs.Config  import Config
from   libs.Data    import Data
from   libs.Globals import Globals
import libs.tools   as     tools

import os, sys, thread
from datetime import date, datetime

import karamba

import warnings
warnings.simplefilter('ignore', RuntimeWarning) # Needed to wipe out os.tempnam()'s warning messages

################################################################################
## Some global variables
################################################################################
configGuiPid     = None
#
dateCheck        = date.today()
nextCacheRefresh = 0
applet           = Applet()   # Make this available globally
################################################################################


##[FIXME]#######################################################################
## Copy the widget files to the nextShows config directory !                  ##
## SuperKaramba (as provided by KDE 3.5.x) does crash when importing PyQt4:   ##
## -> just do "from PyQt4 import QtCore, QtGui" and it's dead                 ##
##                                                                            ##
## (lame) Workaround:                                                         ##
## - Extracting files from the SKZ and copying them to nextShows's config dir ##
##[/FIXME]######################################################################
def createConfigDirs():
    # Create dirs
    mode = Globals().nsDirMode
    dirs = [ Globals().superKarambaDir,
             Globals().nsConfDir,
             Globals().nsCacheDir,
             Globals().nsCGuiBaseDir ]
    for dir in Globals().nsCGuiDirs:
        dirs.append( os.path.join( Globals().nsCGuiBaseDir, dir ) )
    for dir in dirs:
        try:
            os.mkdir( dir, mode )
            tools.msgDebug("Created dir: %s" % dir, __name__)
        except OSError:
            pass


def copyThemeFilesToConfigDir(widget):
    # Copy files
    for file in Globals().nsCGuiFiles:
        source = karamba.readThemeFile( widget, file )
        dest   = open( os.path.join( Globals().nsCGuiBaseDir, file ), "w" )
        tools.msgDebug("Copying file: %s" % file, __name__)
        print >> dest, source
        dest.close()


###############################################################################
## Here begins the "pure" SuperKaramba Part                                  ##
###############################################################################
#this is called when your widget is initialized
def initWidget(widget):
    global nextCacheRefresh

    # Pass the widget reference
    Applet.widget = widget

    # Init splash
    splash = Applet().Splash()
    splash.show()

    # Create dir structure
    splash.setText("Creating config dirs (if necessary)...")
    createConfigDirs()

    # Read config
    splash.setText("Reading config...")
    config = Config()
    if config.getboolean("main", "debug") == False:
        tools.msgDebug("Disabling debug messages !", __name__)
        Globals.DEBUG = False

    # Copy files if necessary
    if Globals().versions['nextShows'] != config.get("main", "version") \
    or not "launchGUI" in os.listdir( Globals().nsCGuiBaseDir ):
        # Init dir structures and copy files
        splash.setText("Copying GUI files...")
        copyThemeFilesToConfigDir(widget)
        config.set("main", "version", Globals().versions['nextShows'])

    # Getting next cache refresh
    splash.setText("Requesting next cache refresh...")

    # Getting the show list
    splash.setText("Getting show list....")
    showList = config.getShows()
    # Extract IDs
    showIds = [ show['id'] for show in showList ]

    # Fetch data to display
    splash.setText("Filtering episodes to display...")
    data = Data()
    if config.get("display", "type") == "Fixed":
        linesMax    = config.getint("display", "lines_fixed")
    else:
        linesMin    = config.getint("display", "lines_min")
        linesMax    = config.getint("display", "lines_max")
    cacheExpiration = config.getint("misc",    "cache_expiration")
    pastDays        = config.getint("display", "past_days")
    episodeList     = data.getEpisodeList( showIds, pastDays, linesMax, cacheExpiration )

    cache = Cache( cacheExpiration )
    nextCacheRefresh = cache.getNextRefreshTS()

    applet.episodeList = episodeList
    applet.colorList = config.getColors()
    applet.episodeFormatString = config.get("display", "format")
    applet.browser = config.get("misc", "browser")
    applet.dateFormat = config.get("display", "date_format")
    applet.whenFormat = config.getint("misc", "when_format")

    # Close the splash
    splash.setText("Done!")
    splash.hide()

    # Init widget
    themeName  = config.get("display", "theme")
    numReturnedEpisode = len( episodeList )
    if config.get("display", "type") == "Fixed":
        themeLines = linesMax   # Defined above
    else:
        if numReturnedEpisode < linesMin:
            themeLines = linesMin
        elif numReturnedEpisode > linesMax:
            themeLines = linesMax
        else:
            themeLines = numReturnedEpisode
    applet.drawBackground( themeName, themeLines )
    applet.printEpisodeList()

    ###########################################################################
    ###########################################################################
    karamba.addMenuConfigOption(widget, "config_gui", "Configure...")
    karamba.setMenuConfigOption(widget, "config_gui", 0)



#this is called everytime your widget is updated
#the update inverval is specified in the .theme file
def widgetUpdated(widget):
    global nextCacheRefresh, configGuiPid, dateCheck

    # Block updates if GUI's running
    if configGuiPid:
        tools.msgDebug("Widget updates suspended, GUI's running...", __name__)
        return

    if date.today() == dateCheck:
        print "Date Check  : %s" % dateCheck
    else:
        print "Date changed => %s was %s" % (date.today(), dateCheck)
    print "Cur. time   : %s (UTC)" % datetime.fromtimestamp( int( datetime.utcnow().strftime("%s") ) )
    print "Next Refresh: %s (UTC)" % datetime.fromtimestamp( nextCacheRefresh )
    print 



#This gets called when an item is clicked in the theme CONFIGURATION menu,
#not the popup menus that you create.
#  key = the reference to the configuration key that was changed
#  value = the new value (true or false) that was selected
def menuOptionChanged(widget, key, value):
    global configGuiPid

    karamba.setMenuConfigOption(widget, "config_gui", 0)

    if key == "config_gui":
        if configGuiPid == None:
            # Launch config GUI
            gui=os.path.join( Globals().nsCGuiBaseDir, "launchGUI" )
            cmd = ["python", gui]
            configGuiPid=karamba.executeInteractive(widget, cmd)
        else:
            tools.msgDebug("GUI already running", __name__)



#This gets called when a meter (image, text, etc) is clicked.
# NOTE you must use attachClickArea() to make a meter
# clickable.  
#  widget = reference to your theme
#  meter = the meter clicked
#  button = the button clicked (see widgetClicked for button numbers)
def meterClicked(widget, meter, button):
    def storeNewWhenFormat(dummy):
        config = Config()
        config.set( "misc", "when_format", str( applet.whenFormat ) )
        config.close()

    if meter in applet.refEpisodeListWhen:
        applet.whenFormat = ( applet.whenFormat + 1 ) % 3
        applet.refreshWhenColumn()
        thread.start_new_thread( storeNewWhenFormat, ("",) )



#This gets called when a command you have executed with executeInteractive() outputs something
#to stdout.  This way you can get the output of for example kdialog without freezing up the widget
#waiting for kdialog to end.
#  widget = reference to your theme
#  pid = process number of the program outputting (use this if you execute more than out process)
#  output = the text the program outputted to stdout
def commandOutput(widget, pid, output):
    global configGuiPid

    if pid == configGuiPid:
        config = Config()
        # Check whether config was changed or not
        try:
            configChanged = config.getboolean("main", "config_changed")
            config.remove_option("main", "config_changed")
        except:
            configChanged = False

        config.close()

        if configChanged:
            karamba.reloadTheme(widget)
            return
        else:
            configGuiPid = None
