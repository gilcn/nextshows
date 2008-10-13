#!/usr/bin/env python
# -*- coding: utf-8 -*-
#######################################################################
# nextShows - Http Requests
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

import os, socket, urllib2


class Http:
    def __init__(self):
        #### User-Agent we use while doing HTTP requests
        version  = Globals().versions
        kernName = os.popen('uname -s').read()[:-1]
        kernRel  = os.popen('uname -r').read()[:-1]
        #return "Mozilla/5.0 (compatible; Konqueror/3.5; Linux) KHTML/3.5.6 (like Gecko)"
        self.userAgent = u"Mozilla/5.0 (compatible; nextShows/%s; %s-%s)" % ( version['nextShows'], kernName, kernRel )

        #### Set default timeout
        socket.setdefaulttimeout(10) # 10s


    ###############################################################################
    ## Method     : request(url)
    ## Description: Send a HTTP request using custom headers
    ##
    ## Input args:
    ##   - url   : URL we want to retrieve
    ##
    ## Output:
    ##   - Webpage content
    ###############################################################################
    def request(self, url):

        header  = urllib2.Request(url, None, { 'User-agent' : self.userAgent })
        try:
            request = urllib2.urlopen(header)
        except:
            return False
        content = request.readlines()
        request.close()

        return ''.join(content)
