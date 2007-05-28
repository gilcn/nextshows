#!/usr/bin/env python
# -*- coding: utf-8 -*-
#######################################################################
# nextShows - Cache management
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
from libs.TvRage  import TvRage
import libs.tools as tools

from datetime import datetime
import cPickle, os, re


class Cache:
    def __init__(self, expiration):
        # Constants
        self.CACHEFILEOK       = 0
        self.CACHEFILEOUTDATED = 1
        self.CACHEFILENOTFOUND = 2

        # Expiration time (days converted to seconds)
        self.expiration = expiration*24*60*60


    ###############################################################################
    ## Method     : cacheEpisodeList(id)
    ## Description: Call the Parser and store results to cache
    ##
    ## Input args:
    ##   - id     : Show ID
    ##
    ## Output:
    ##   - True   : Caching OK
    ##   - False  : Ooopss
    ###############################################################################
    def cacheEpisodeList(self, id):
        # Cache filename
        cacheFileName = Globals().nsCacheFilePrefix + str( id )

        # Get the data
        parser = TvRage()
        epList = parser.getEpisodeList( id )

        if not epList:
            return False    # In case something went wrong during parsing...

        showEpList = {}
        showEpList['fetch_time']   = int( datetime.utcnow().strftime("%s") ) # Timestamp (UTC)
        showEpList['episode_list'] = epList

        # Open the file for writing
        tools.msgDebug("Writing cache file %s..." % cacheFileName, __name__)
        fp = open( cacheFileName, "wb" )
        cPickle.dump( showEpList, fp, cPickle.HIGHEST_PROTOCOL )
        fp.close()

        # At this point we suppose everything hopefully went well
        return True


    ###############################################################################
    ## Method     : getCachedEpisodeList(id)
    ## Description: return episode data from cache
    ##
    ## Input args:
    ##   - id     : Show ID
    ##
    ## Output:
    ##   - List containing episode list
    ###############################################################################
    def getCachedEpisodeList(self, id):
        # Cache filename
        cacheFileName = Globals().nsCacheFilePrefix + str( id )
        
        # Get data
        tools.msgDebug("Getting data from cache %s..." % cacheFileName, __name__)
        fp = open( cacheFileName, "rb" )
        data = cPickle.load( fp )
        fp.close()

        # Return episode list
        return data['episode_list']


    ###############################################################################
    ## Method     : checkCacheFile(id)
    ## Description: Check whether the cache for the given show is valid or not
    ##
    ## Input args:
    ##   - id         : Show ID
    ##
    ## Output:
    ##   - Cache file state (OK, OUTDATED or NOTFOUND)
    ###############################################################################
    def checkCacheFile(self, id):
        # Cache filename
        cacheFileName = Globals().nsCacheFilePrefix + str( id )

        # Check if a file exists for the given id
        if os.path.isfile( cacheFileName ):
            # Check if data are still valid
            currentTS = int( datetime.utcnow().strftime("%s") )
            # Show filename
            cacheFileName = Globals().nsCacheFilePrefix + str( id )
            # Get data fetch time
            fp = open( cacheFileName, "rb" )
            cacheData = cPickle.load( fp )
            fp.close()
            cacheFileTS = cacheData['fetch_time']

            if ( cacheFileTS + self.expiration ) < currentTS:
                return self.CACHEFILEOUTDATED
        else:
            return self.CACHEFILENOTFOUND

        return self.CACHEFILEOK


    ###############################################################################
    ## Method     : getStaledCacheFiles(idList)
    ## Description: Return the list of shows which associated cache file is not found
    ##              or outdated
    ##
    ## Input args:
    ##   - idList : Contain the IDs of the shows we need to test
    ##
    ## Output:
    ##   - List containing outdated/staled shows
    ###############################################################################
    def getStaledCacheFiles(self, idList):
        pass


    ###############################################################################
    ## Method     : deleteOldCacheFiles(idList)
    ## Description: Delete cache files belonging to shows not tracked anymore
    ##
    ## Input args:
    ##   - idList : Contain the IDs of the shows we *WANT* to *KEEP*
    ##
    ## Output:
    ##   - False  : Something odd happened
    ##   - True   : Success
    ###############################################################################
    def deleteOldCacheFiles(self, idList):
        tools.msgDebug("Purging cache dir...", __name__)
        cacheDirContents = os.listdir( Globals().nsCacheDir )
        cacheFilePrefix = os.path.basename( Globals().nsCacheFilePrefix )

        for id in idList:
            fileName = cacheFilePrefix + str( id )
            if fileName in cacheDirContents:
                index = cacheDirContents.index( fileName )
                cacheDirContents.pop( index )

        # Remove unwanted files
        exitFlag = True
        for file in cacheDirContents:
            fileName = os.path.join( Globals().nsCacheDir, file )
            try:
                os.remove( fileName )
                tools.msgDebug("Deleted %s..." % fileName, __name__)
            except:
                exitFlag = False
                tools.msgDebug("Error raised while trying to delete %s..." % fileName, __name__)

        return exitFlag


    ###############################################################################
    ## Method     : getNextRefreshTS()
    ## Description: Scans the cache files searching for the next needed refresh
    ##              !!! /!\ Takes also into account staled cache files /!\ !!!
    ##
    ## Input args:
    ##   - None
    ##
    ## Output:
    ##   - Next refresh timestamp
    ###############################################################################
    def getNextRefreshTS(self):
        cacheFilePrefix = os.path.basename( Globals().nsCacheFilePrefix )
        cacheFileNameRE = re.compile( r'^' + cacheFilePrefix + '\d+$' )

        fetchTimeList = []
        
        for file in os.listdir( Globals().nsCacheDir ):
            if cacheFileNameRE.match( file ):
                cacheFileName = os.path.join( Globals().nsCacheDir, file )
                # Get data fetch time
                fp = open( cacheFileName, "rb" )
                cacheData = cPickle.load( fp )
                fp.close()
                fetchTimeList.append( cacheData['fetch_time'] )

        # Keep smaller TS
        nextTS = -1
        for ts in fetchTimeList:
            if nextTS == -1:
                nextTS = ts
            else:
                if ts < nextTS:
                    nextTS = ts

        return ( nextTS + self.expiration )
