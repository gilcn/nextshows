#!/usr/bin/env python
# -*- coding: utf-8 -*-
#######################################################################
# nextShows - Cache Tool
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

from CacheToolForm_ui import Ui_CacheToolForm

from PyQt4.Qt import *

import cPickle, datetime, os, re


class CacheTool(QDialog):
    def __init__(self, parent=None):
        # Init UI
        QDialog.__init__(self, parent)
        self.ui = Ui_CacheToolForm()
        self.ui.setupUi(self)   # Setup UI
        #
        self.ui.currentDateTime.setDisplayFormat("yyyy.MM.dd - hh:mm:ss LOC")
        self.ui.showCacheDateTime.setDisplayFormat("yyyy.MM.dd - hh:mm:ss UTC")
        #
        self.ui.tableEpisodes.setColumnCount(5)
        self.ui.tableEpisodes.setHorizontalHeaderLabels( [ "S", "E", "Title", "Date", "Delta" ] )
        #vHeader = QHeaderView( Qt.Vertical, self.ui.tableEpisodes )
        self.ui.tableEpisodes.verticalHeader().hide()


        # Vars
        self.baseDir = os.path.expanduser( "~/.superkaramba/nextShows/cache" )
        self.cacheFilePattern = re.compile( r'^show_\d+$' )
        #
        self.currentDateTime = datetime.datetime.utcnow()
        #
        self.showList = self._readCachedShows()

        self.ui.listShows.clear()
        for show in self.showList:
            self.ui.listShows.addItem( show[0] )

        # Timer
        self.timer = QTimer()
        self.timer.setInterval(1000)
        self.timer.start()

        QObject.connect( self.timer, SIGNAL("timeout()"), self._timerTimeout )
        QObject.connect( self.ui.btnQuit, SIGNAL("clicked()"), self, SLOT("close()") )


    @pyqtSignature("on_listShows_currentRowChanged(int)")
    def on_listShows_currentRowChanged(self, rowNum):
        self.ui.tableEpisodes.setRowCount( 0 )

        episodes = self.showList[rowNum][3]
        pos = 0
        for episode in episodes:
            self.ui.tableEpisodes.setRowCount( self.ui.tableEpisodes.rowCount()+1 )
            itemS = QTableWidgetItem( str( episode['season']  ) )
            itemS.setFlags( Qt.ItemIsEnabled )
            itemE = QTableWidgetItem( str( episode['episode'] ) )
            itemE.setFlags( Qt.ItemIsEnabled )
            itemT = QTableWidgetItem( episode['title'] )
            itemT.setFlags( Qt.ItemIsEnabled )
            year, month, day = episode['airdate']
            date = datetime.date( year, month, day )
            itemD = QTableWidgetItem( date.strftime("%Y.%m.%d") )
            itemD.setFlags( Qt.ItemIsEnabled )
            dateToday = datetime.date.today()
            delta = date-dateToday
            itemA = QTableWidgetItem( "%d d." % delta.days )
            itemA.setFlags( Qt.ItemIsEnabled )
            self.ui.tableEpisodes.setItem( pos, 0, itemS )
            self.ui.tableEpisodes.setItem( pos, 1, itemE )
            self.ui.tableEpisodes.setItem( pos, 2, itemT )
            self.ui.tableEpisodes.setItem( pos, 3, itemD )
            self.ui.tableEpisodes.setItem( pos, 4, itemA )
            pos += 1

        for i in range(5):
            self.ui.tableEpisodes.resizeColumnToContents( i )

        qdt = QDateTime()
        qdt.setTime_t( self.showList[rowNum][1] )
        self.ui.showCacheDateTime.setDateTime( qdt )

    def _readCachedShows(self):
        showList = []
        listDir = os.listdir( self.baseDir )

        for file in listDir:
            show = ()
            match = self.cacheFilePattern.match( file )
            if match:
                fileName = os.path.join( self.baseDir, file )
                fp = open( fileName, "rb" )
                data = cPickle.load( fp )
                fp.close()

                fetchTS = data['fetch_time']
                name    = data['episode_list'][0]['show']
                show    = ( name, fetchTS, fileName, data['episode_list'] )
                showList.append( show )

        return showList

    def _timerTimeout(self):
        qdt = QDateTime()
        qdt.setTime_t( int( datetime.datetime.now().strftime("%s") ) )
        self.ui.currentDateTime.setDateTime( qdt )
