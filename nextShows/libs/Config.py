#!/usr/bin/env python
# -*- coding: utf-8 -*-
#######################################################################
# nextShows - Config class
# Copyright (C) 2006-2007 Gilles CHAUVIN <gcnweb@gmail.com>
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
import libs.tools as tools

from libs.demjson import JSON

from ConfigParser import SafeConfigParser
import os, random, re, time


class Config(SafeConfigParser):

    LOCK = False    # Used to prevent conflicts with simultaneous access to Config()

    def __init__(self):
        SafeConfigParser.__init__(self)

        # LOCK Config() and read configuration file
        self._acquireLock()

        # Write Flag
        # Used to prevent writing back to config file if it was just opened for reading
        self.writeFlag = False

        #### Define default config values
        ### [main]
        ## Default DEBUG Value
        self.debug = False

        ### [gui]
        ## Filter checkbox
        self.filter = True

        ### [shows]
        ## My Shows
        self.myShows = []

        ### [display]
        ## Past days to display
        self.numPastDays = 1
        ## Lines
        self.linesFixed = 10
        self.linesMin   = 1
        self.linesMax   = 10
        self.linesType  = "Fixed" # Values: Fixed / Auto
        ## Format
        self.format = "$show:12:...$-S$season:2$E$episode:2$-$title$"
        ## Theme
        self.theme  = "Original"
        ## Date
        self.dateFormat = "%%d/%%m/%%y"
        ## When format
        self.whenFormat = 0

        ### [colors]
        self.myColors = {}
        self.myColors['default'] = "#111111"
        self.myColors['ranges']  = [(-99,-1,"#771111"),(0,0,"#117711"),(1,1,"#111177")]

        ### [misc]
        self.cacheExpiration = 1
        self.browser = "firefox -remote 'openURL($url$,new-tab)'"

        #### Create necessary dir structure
        self._initConfigStorage()


    def __del__(self):
        self.close()

    def close(self):
        if Config.LOCK == True:
            self._releaseLock()     # Save file (if needed) and release LOCK


    ##############################
    ## Acquire config file LOCK ##
    ##############################
    def _acquireLock(self):
        # If a LOCK already exist, wait until it is released
        while Config.LOCK:
            tools.msgDebug("Config file LOCKed! Waiting for lock to be released...", __name__)
            randomize = float( random.randint( 0, 1000) ) / 1000
            time.sleep( randomize )
        # Acquire LOCK
        Config.LOCK = True
        tools.msgDebug("Config LOCK acquired", __name__)
        # Read config
        self.read( Globals().nsConfFile )
        tools.msgDebug("Config read", __name__)
    ######################
    ## Release the LOCK ##
    ######################
    def _releaseLock(self):
        if self.writeFlag:
            tools.msgDebug( "Saving config...", __name__ )
            # Write back to config file
            fp = open( Globals().nsConfFile, "w" )
            self.write( fp )
            fp.close()
            tools.msgDebug( "Config saved to %s" % Globals().nsConfFile, __name__ )
        # Release LOCK
        Config.LOCK = False
        tools.msgDebug( "Config LOCK released", __name__ )


    #########
    ## set ##
    #########
    def set(self, section, option, value):
        self.writeFlag = True   # Must save the config
        SafeConfigParser.set(self, section, option, value)

    ###################
    ## remove_option ##
    ###################
    def remove_option(self, section, option):
        self.writeFlag = True
        SafeConfigParser.remove_option(self, section, option)


    #########
    ## get ##
    #########
    #def get(self, section, option):
    #    return SafeConfigParser.get(self, section, option)


    ###############
    ## Set shows ##
    ###############
    def setShows(self, showList):
        self.writeFlag = True   # Must save the config

        self.remove_section( "shows" ) # clear
        self.add_section( "shows" )    # recreate

        for show in showList:
            option = "show_%d" % show['id']
            self.set( "shows", option, JSON().encode(show) )


    ###############
    ## Get shows ##
    ###############
    def getShows(self):
        pattern = re.compile( r'^show_\d+$' )

        showOpts = []
        for option in self.options( "shows" ):
            match = pattern.match( option )
            if match:
                showOpts.append( option )

        showList = []
        for option in showOpts:
            show = JSON().decode( self.get( "shows", option ) )
            showList.append( show )

        # Sort the shows
        showList = tools.sortShowsByName( showList )

        return showList


    ################
    ## Set colors ##
    ################
    def setColors(self, colDict):
        self.writeFlag = True   # Must save the config

        self.remove_section( "colors" ) # clear
        self.add_section( "colors" )    # recreate

        self.set( "colors", "default", colDict["default"] )
        for rng in colDict["ranges"]:
            start, stop, color = rng
            if start >= 0:
                startStr = "+%d" % start
            else:
                startStr = str(start)
            if stop >= 0:
                stopStr = "+%d" % stop
            else:
                stopStr = str(stop)

            self.set( "colors", "day_%s%s" % (startStr, stopStr), color )


    ################
    ## Get colors ##
    ################
    def getColors(self):
        pattern = re.compile( r'^day_([+-]\d+)([+-]\d+)$' )
        retCol = { 'default' : '',
                   'ranges'  : [] }
        for color in self.options("colors"):
            if color == "default":
                retCol['default'] = self.get("colors", "default")
            else:
                match = pattern.match(color)
                if match:
                    col = ( int( match.group(1) ), int( match.group(2) ), self.get("colors", color) )
                    retCol['ranges'].append( col )

        retCol['ranges'] = tools.sortColorsByRange( retCol['ranges'] )
        return retCol


    #############################################################
    ## Create the necessary dir structure and/or missing files ##
    #############################################################
    def _initConfigStorage(self):

        # /!\ Directory tree should be created when the widget launches

        # Create necessary directories
#        mode = Globals().nsDirMode
#        dirs = [ Globals().superKarambaDir, Globals().nsConfDir ]

#        for dir in dirs:
#            try:
#                os.mkdir( dir, mode )
#            except OSError:
#                pass

        # If no config file is found, create a default one
        if not os.path.isfile( Globals().nsConfFile ):
            self._createDefaultConfFile()


    ##########################################################
    ## Create a new configuration file with defaults values ##
    ##########################################################
    def _createDefaultConfFile(self):
        self.writeFlag = True   # Must save the config

        tools.msgDebug("Creating default config file %s" % Globals().nsConfFile, __name__)

        #----------------------------------------------------------------------
        # Create necessary sections
        #sections = ( 'main', 'gui', 'display', 'colors', 'shows', 'misc' )
        sections = ( 'main', 'display', 'colors', 'shows', 'misc' )
        for section in sections:
            self.add_section( section )
        # Main
        self.set( "main",    "version",     "0"                   )
        self.set( "main",    "debug",       str(self.debug)       )
        # Gui
        #self.set( "gui",     "filter",      str(self.filter)      )
        # Display
        self.set( "display", "past_days",   str(self.numPastDays) )
        self.set( "display", "lines_fixed", str(self.linesFixed)  )
        self.set( "display", "lines_min",   str(self.linesMin)    )
        self.set( "display", "lines_max",   str(self.linesMax)    )
        self.set( "display", "type",        str(self.linesType)   )
        self.set( "display", "format",      str(self.format)      )
        self.set( "display", "theme",       str(self.theme)       )
        self.set( "display", "date_format", str(self.dateFormat)  )
        # Misc
        self.set( "misc",    "cache_expiration", str(self.cacheExpiration ) )
        self.set( "misc",    "browser",     str(self.browser)     )
        self.set( "misc",    "when_format", str(self.whenFormat)  )
        #----------------------------------------------------------------------

        # Set shows
        self.setShows ( self.myShows )
        # Set color
        self.setColors ( self.myColors )
