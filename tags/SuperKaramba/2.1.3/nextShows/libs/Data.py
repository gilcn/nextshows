#!/usr/bin/env python
# -*- coding: utf-8 -*-
#######################################################################
# nextShows - Data presentation class
# Copyright (C) 2006-2008 Gilles CHAUVIN <gcnweb@gmail.com>
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

from libs.Cache import Cache

from datetime import date

class Data():
    def __init__(self):
        pass


    ###############################################################################
    ## Method     : getEpisodeList(self, showIds, pastDays, linesMax)
    ## Description: Return a list of shows to display within the widget
    ##
    ## Input args:
    ##   - showIds   : List containing show IDs we want to extract infos from
    ##   - pastDays  : Number of past days to take into account
    ##   - linesMax  : Number of total shows to keep
    ##
    ## Output:
    ##   - List containing show infos
    ###############################################################################
    def getEpisodeList(self, showIds, pastDays, linesMax):
        # Negate "pastDays"
        pastDays = -abs(pastDays)
        # Today's date
        todaysDate = date.today()

        # Check and refresh cache if needed
        allEpisodes = []
        cache = Cache()
        for id in showIds:
            status = cache.checkCacheFile( id )
            ret = True
            if status == cache.CACHEFILENOTFOUND:
#                ret = cache.cacheEpisodeList( id )  # Should return False if a problem occured
                ret = False     # Don't include files not found
            if ret == True:
                allEpisodes += cache.getCachedEpisodeList( id )

        deltas = []
        unairedEpisodes = []
        # Compute deltas and feed the list
        for episode in allEpisodes:
            epAD = episode['airdate']
            try:
                episodeAirDate = date( epAD[0], epAD[1], epAD[2] )
                delta = episodeAirDate - todaysDate
                # Only append deltas and episode for unaired shows
                if delta.days >= pastDays:
                    deltas.append( delta.days )
                    episodeOK = episode
                    episodeOK['delta'] = delta.days
                    unairedEpisodes.append( episodeOK )
            except:
                # Air date for this episode is unknown.
                # We suppose it is unaired yet!
                episode['delta'] = 999999
                deltas.append( episode['delta'] )
                unairedEpisodes.append( episode )

        # Sort deltas
        deltas.sort()

        # Just keep the linesMax'th first deltas
        deltas = deltas[:linesMax]

        # Final Show List
        finalShowList = []

        for delta in deltas:
            for show in unairedEpisodes:
                if show['delta'] == delta:
                    if not len( finalShowList ) >= linesMax:
                        index=unairedEpisodes.index( show )
                        finalShowList.append( unairedEpisodes.pop( index ) )

        return finalShowList
