#!/usr/bin/env python
# -*- coding: utf-8 -*-
#######################################################################
# nextShows - Parser for tvrage.com webpages
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


from   libs.Http          import Http
import libs.tools         as     tools

from   libs.BeautifulSoup import BeautifulSoup

import re, urllib
import xml.etree.cElementTree as ETree


class TvRage(Http):
    def __init__(self):
        #### Init
        Http.__init__(self)

        #### Used to convert Months
        self.monthsList = { 'Jan' :  1, 'Feb' :  2, 'Mar' :  3, 'Apr' :  4, 'May' :  5, 'Jun' :  6,
                            'Jul' :  7, 'Aug' :  8, 'Sep' :  9, 'Oct' : 10, 'Nov' : 11, 'Dec' : 12 }

        #### URL Templates for tvrage.com
        self.urlBase         = u"http://www.tvrage.com/"
        self.urlSearch       = u"http://www.tvrage.com/feeds/search.php?show=%s"
        self.urlShowTemplate = u"http://www.tvrage.com/shows/id-%d"
        self.urlEpisodeList  = u"http://www.tvrage.com/shows/id-%d/episode_list/all"

        #### RegExps
        self.reSeasonEpisode = re.compile(r"^(\d+)x(\d+)$")

        #### Parsed search results
        self.searchResults  = []
        #### Parsed episode list
        self.episodeList    = []


    ###############################################################################
    ## Method     : search(keywords)
    ## Description: Return the parsed content of a tvrage's search result
    ##
    ## Input args:
    ##   - keywords : show title to search for
    ##
    ## Output:
    ##   - [
    ##         { 'name'       : u'',
    ##           'year_begin' : u'',
    ##           'year_end'   : u'',
    ##           'id'         : int,
    ##           'url'        : u'',
    ##           'flag'       : u''
    ##         },
    ##         { ... },
    ##         ...
    ##     ]
    ###############################################################################
    def search(self, keywords):
        # Clear Search Results
        self.searchResults = []

        # Sanitize keywords and build the URL
        url = self.urlSearch % urllib.quote_plus(keywords)
        tools.msgDebug("Requesting %s" % url, __name__)
        # do the request
        content = self.request(url)     # request() from Http()
        if not content:
            return False    # In case something went wrong during fetching
        # ...and parse the results
        try:
            tools.msgDebug("Parsing page content...", __name__)
            doc = ETree.fromstring(content)
        except:
            tools.msgDebug("Unexpected error while parsing the XML feed...", __name__)
            return False

        # If the search returns nothing...
        if doc.text == "0":
            tools.msgDebug("Search returned 0 results", __name__)
            return self.searchResults

        # Extract infos from the returned results
        for show in doc.getiterator('show'):
            showInfos = {}
            for child in show.getchildren():
                if   child.tag == "showid":
                    showInfos["id"]   = int( child.text )
                    showInfos["url"]  = self.urlShowTemplate % showInfos["id"]
                elif child.tag == "name":
                    showInfos["name"] = u''+child.text
                elif child.tag == "started":
                    showInfos["year_begin"] = child.text
                elif child.tag == "ended":
                    # This hack is necessary to retain compatibility with
                    # previous versions' config. files
                    if child.text == "0":
                        showInfos["year_end"] = "????"
                    else:
                        showInfos["year_end"] = child.text
                elif child.tag == "country":
                    showInfos["flag"] = child.text.lower()

            tools.msgDebug("ShowName: %s, Flag: %s, Years: %s-%s, id: %d, url: %s" % ( showInfos["name"], showInfos["flag"], showInfos["year_begin"], showInfos["year_end"], showInfos["id"], showInfos["url"] ), __name__ )

            self.searchResults.append(showInfos)

        return self.searchResults


    ###############################################################################
    ## Method     : getEpisodeList(id)
    ## Description: Return the parsed content of Episode List page
    ##
    ## Input args:
    ##   - id : Show id
    ##
    ## Output:
    ##       [
    ##          {
    ##             'season'  : int,     # Episode season number
    ##             'episode' : int,     # Episode number
    ##             'title'   : u'',     # Episode title
    ##             'url'     : u'',     # Episode URL
    ##             'airdate' : (year, month, day),
    ##          }, ...
    ##       ], ...
    ##
    ## Note:
    ## "Special" episodes are returned with 'season' and 'episode' set to a negative
    ## value (ie. -1).
    ###############################################################################
    def getEpisodeList(self, id):
        # Clear episodeList
        self.episodeList = []

        # Sanitize keywords and build the URL
        url = self.urlEpisodeList % id
        tools.msgDebug("Requesting %s" % url, __name__)
        # do the request...
        content = self.request(url)     # request() from Http()
        if not content:
            return False    # In case something went wrong during fetching
        # ...and feed BeautifulSoup
        page = BeautifulSoup(content)

        showName = u''+page('h3')[0].contents[0]

        tools.msgDebug("Parsing content...", __name__)
        # Read each line and extract infos
        for line in page.findAll("tr", id="brow"):
            episode = {}
            episode['show'] = showName
            try:
                firstCellWidth = int( line('td')[0]['width'] )
                # Each "normal" episode 1st <td /> have width=30
                if firstCellWidth == 30:
                    # Get Season and Episode #
                    match = self.reSeasonEpisode.match( str( line('td')[1]('a')[0].contents[0] ) )
                    episode['season']  = int( match.group(1) )
                    episode['episode'] = int( match.group(2) )
                    # Episode title
                    episode['title']   = u''+line('td')[8]('a')[0].contents[0]
                    # Url
                    episode['url']     = self.urlBase + line('td')[8].a['href'][1:]   # Remove leading "/"
                    # Airdate
                    day   = int( line('td')[3].contents[0] )
                    m     = str( line('td')[5].contents[0] )
                    month = self.monthsList[ m ]
                    year  = int( line('td')[7].contents[0] )
                    episode['airdate'] = ( year, month, day )

                    tools.msgDebug( "Found: %s-S%02dE%02d-%s" % ( episode['show'], episode['season'], episode['episode'], episode['title'] ), __name__ )
                    self.episodeList.append( episode )

                # Each "special" episode 1st <td /> have width=70
                elif firstCellWidth == 70:
                    # Set Season and Episode numbers to a negative value
                    episode['season']  = -1
                    episode['episode'] = -1
                    # Episode title
                    episode['title']   = u''+line('td')[7]('a')[0].contents[0]
                    # Episode URL
                    episode['url']     = self.urlBase + str( line('td')[7].a['href'][1:] )
                    # Airdate
                    day   = int( line('td')[2].contents[0] )
                    m     = str( line('td')[4].contents[0] )
                    month = self.monthsList[ m ]
                    year  = int( line('td')[6].contents[0] )
                    episode['airdate'] = ( year, month, day )

                    tools.msgDebug( "Found: %s-S%02dE%02d-%s" % ( episode['show'], episode['season'], episode['episode'], episode['title'] ), __name__ )
                    self.episodeList.append( episode )
            except:
                tools.msgDebug("WARNING: Invalid line found! Skipping...", __name__)
                continue

        return self.episodeList
