#!/usr/bin/env python
# -*- coding: utf-8 -*-
#######################################################################
# nextShows - Global (const) variables
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

import os

class Globals():

    # Set DEBUG ?
    DEBUG = True

    def __init__(self):
        # Version
        self.VERSION           = "2.1.1" # Don't forget to update "maindata.xml"

        #### Working Directories & Files
        self.superKarambaDir   = os.path.expanduser("~/.superkaramba")
        #self.nsConfDir         = os.path.join(self.superKarambaDir, "DEVnextShows")
        self.nsConfDir         = os.path.join(self.superKarambaDir, "nextShows")
        self.nsCGuiBaseDir     = os.path.join(self.nsConfDir, "config")
        self.nsCGuiDirs        = ( 'cgui', 'libs' )
        self.nsCGuiFiles       = ( 'launchGUI',
                                   'maindata.xml',
                                   'cgui/__init__.py',
                                   'cgui/FormatHelp.py',
                                   'cgui/FormatHelp_ui.py',
                                   'cgui/ListWidget.py',
                                   'cgui/NextShowsConfig.py',
                                   'cgui/NextShowsConfig_ui.py',
                                   'cgui/NextShowsConfig_rc.py',
                                   'libs/__init__.py',
                                   'libs/Config.py',
                                   'libs/Globals.py',
                                   'libs/Http.py',
                                   'libs/TvRage.py',
                                   'libs/demjson.py',
                                   'libs/tools.py' )
        self.nsConfFile        = os.path.join(self.nsConfDir, "nextShows.conf")
        self.nsCacheDir        = os.path.join(self.nsConfDir, "cache")
        self.nsDirMode         = 0755
        self.nsCacheFilePrefix = os.path.join(self.nsCacheDir, "show_")

        # Hardcoding the theme names is not very efficient but it is the simpliest
        # way since SuperKaramba lacks some functions we'd need otherwise.
        self.availableThemes = [ "Default", "ClapperBoard" ]
        # Default theme name
        self.defaultThemeName  = "Default"

        # Sample episode (used for testing in the GUI)
        self.sampleEpisode     = { 'show'    : 'Battlestar Galactica (2003)',
                                   'title'   : 'Taking a Break from All Your Worries',
                                   'season'  : 3,
                                   'episode' : 13 }

        self.versions      = self.getVersions()


    ###############################################################################
    ## NOTE: Moved from libs/Globals.py to avoid SK crashes when importing PyQt4
    ##
    ## Function   : getLibsVersions()
    ## Description: Return version number for the main libs used by the widget
    ##
    ## Input args:
    ##   - None
    ##
    ## Output:
    ##   - dict {
    ##           'nextShows'     : u'',
    ##           'KDE'           : u'',
    ##           'Qt'            : u'',
    ##           'PyQt'          : u'',
    ##     }
    ###############################################################################
    def getVersions(self):
        versDict = {}

        # nextShows release
        #import xml.dom.minidom
        #maindata = xml.dom.minidom.parse('maindata.xml')
        #versDict['nextShows'] = maindata.getElementsByTagName('version')[0].firstChild.nodeValue
        versDict['nextShows'] = self.VERSION

        # KDE version
        import os, re
        pattern=re.compile(r'^KDE: (.*)$')
        for line in os.popen('kde-config --version').readlines():
            match = pattern.match(line)
            if match:
                versDict['KDE'] = match.group(1).decode('utf-8')

        ######################################################################
        ## FIXME: Commented. Code copied to NextShowsConfig.py due to SK
        ##        crashing when importing PyQt4 !
        ######################################################################
        # Qt/PyQt version
        #from PyQt4 import QtCore
        #versDict['Qt']   = QtCore.QT_VERSION_STR.decode('utf-8')
        #versDict['PyQt'] = QtCore.PYQT_VERSION_STR.decode('utf-8')

        # Return result
        return versDict

