#!/usr/bin/env python
# -*- coding: utf-8 -*-
#######################################################################
# nextShows - Parser for tvrage.com webpages
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


from   libs.Http          import Http
import libs.tools         as     tools

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
        self.urlEpisodeList  = u"http://www.tvrage.com/feeds/episode_list.php?sid=%d"

        #### RegExps
        #self.reSeasonNumber   = re.compile(r"^Season(\d+)$")
        self.reEpisodeAirDate = re.compile(r"^(\d{4})-(\d{2})-(\d{2})$")

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
            tools.msgDebug("Parsing feed content...", __name__)
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
    ##   - id : Show id (int)
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
        # ...and parse the results
        try:
            tools.msgDebug("Parsing feed content...", __name__)
            doc = ETree.fromstring(content)
        except:
            tools.msgDebug("Unexpected error while parsing the XML feed...", __name__)
            return False

        showName = u''+doc.find('name').text

        # No Episode List ?
        if not doc.find('Episodelist'):
            return self.episodeList

        # Get Episode list...
        for season in doc.find('Episodelist').getchildren():
            if season.tag == "Season":
                for ep in season.findall('episode'):
                    episode = {}
                    episode['show']    = showName
                    episode['season']  = int( season.attrib["no"] )
                    episode['episode'] = 0
                    episode['title']   = ""
                    episode['url']     = ""
                    episode['airdate'] = ( 0, 0, 0 )
                    for child in ep.getchildren():
                        if   child.tag == "seasonnum":
                            episode['episode'] = int( child.text )
                        elif child.tag == "title":
                            episode['title'] = u''+child.text
                        elif child.tag == "link":
                            episode['url'] = u''+child.text
                        elif child.tag == "airdate":
                            matchEAD = self.reEpisodeAirDate.match( child.text )
                            if matchEAD:
                                year, month, day = matchEAD.group(1), matchEAD.group(2), matchEAD.group(3)
                                episode['airdate'] = ( int(year), int(month), int(day) )

                    # Only append episode if we got all the data we need
                    if   not episode['show']:
                        continue
                    elif episode['season'] <= 0:
                        continue
                    elif episode['episode'] <= 0:
                        continue
                    elif not episode['title']:
                        continue
                    elif not episode['url']:
                        continue
                    #elif episode['airdate'][0] <= 0:
                    #    continue
                    #elif episode['airdate'][1] < 1 or episode['airdate'][1] > 12:
                    #    continue
                    #elif episode['airdate'][2] < 1 or episode['airdate'][2] > 31:
                    #    continue

                    tools.msgDebug( "Found: %s-S%02dE%02d-%s (%04d-%02d-%02d)" %
                        ( episode['show'], episode['season'], episode['episode'], episode['title'],
                        episode['airdate'][0], episode['airdate'][1], episode['airdate'][2] ),
                        __name__ )
                    self.episodeList.append( episode )

        return self.episodeList
