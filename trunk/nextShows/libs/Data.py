#!/usr/bin/env python
# -*- coding: utf-8 -*-
#######################################################################
# nextShows - Data presentation class
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

from libs.Cache import Cache

from datetime import date

class Data:
    def __init__(self):
        pass


    ###############################################################################
    ## Method     : getEpisodeList(self, showIds, pastDays, linesMax, expiration)
    ## Description: Return a list of shows to display within the widget
    ##
    ## Input args:
    ##   - showIds   : List containing show IDs we want to extract infos from
    ##   - pastDays  : Number of past days to take into account
    ##   - linesMax  : Number of total shows to keep
    ##   - expiration: Cache expiration time (in days)
    ##
    ## Output:
    ##   - List containing show infos
    ###############################################################################
    def getEpisodeList(self, showIds, pastDays, linesMax, expiration):

        # Negate "pastDays"
        pastDays = -abs(pastDays)
        # Today's date
        todaysDate = date.today()

        # Check and refresh cache if needed
        allShows = []
        cache = Cache()
        for id in showIds:
            status = cache.checkCacheFile( id, expiration )
            ret = True
            if status == cache.CACHEFILENOTFOUND:
                ret = cache.cacheEpisodeList( id )  # Should return False if a problem occured
            if ret == True:
                allShows += cache.getCachedEpisodeList( id )

        deltas = []
        unAiredShows = []
        # Compute deltas and feed the list
        for episode in allShows:
            epAD = episode['airdate']
            episodeAirDate = date( epAD[0], epAD[1], epAD[2] )
            delta = episodeAirDate - todaysDate
            # Only append deltas and episode for un aired shows
            if delta.days >= pastDays:
                deltas.append( delta.days )
                episodeOK = episode
                episodeOK['delta'] = delta.days
                unAiredShows.append( episodeOK )

        # Sort deltas
        deltas.sort()

        # Just keep the linesMax'th first deltas
        deltas = deltas[:linesMax]

        # Final Show List
        finalShowList = []

        for delta in deltas:
            for show in unAiredShows:
                if show['delta'] == delta:
                    index=unAiredShows.index( show )
                    finalShowList.append( unAiredShows.pop( index ) )

        return finalShowList
