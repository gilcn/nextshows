#!/usr/bin/env python
# -*- coding: utf-8 -*-
#######################################################################
# nextShows - Tools
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
import re, sys


###############################################################################
## Method     : msgDebug(message)
## Description: Send debug messages to stderr
##
## Args:
##   - message: Message to display
##
## Return:
##   - N/A
###############################################################################
def msgDebug(message, caller=""):
    if Globals.DEBUG:
        if caller:
            text = u"[DEBUG-%s] %s\n" % ( caller, message )
        else:
            text = u"[DEBUG] %s\n" % message
        sys.stderr.write( text.encode('utf-8') )


###############################################################################
## Function   : formatEpisode(episode, formatStr)
## Description: Return the show that will be displayed in the widget
##              according to the format string given
##
## Args:
## - episode : Dict containing episode infos
##             {
##              'season'  : '',
##              'episode' : '',
##              'show'    : '',
##              'title'   : '',
##             }
## - format  : format string
##
## Return:
## - Episode formated string
###############################################################################
def formatEpisode(episode, formatStr):
    # List of vars taking [:zero_padded_length] argument
    vars1Arg  = ( "season", "episode" )
    # List of vars taking [:length[:trailing_chars]] arguments
    vars2Args = ( "show", "title" )

    # Regular Expressions
    regexp1Arg  = r'(?P<var>\$%s(?P<length>:\d+)?\$)'
    regexp2Args = r'(?P<var>\$%s((?P<length>:\d+)(?P<trail>:[^\$]+)?)?\$)'

    # Special episodes replacement char
    replChar = "?"

    # Process 1 arg vars
    for var in vars1Arg:
        regexp  = regexp1Arg % var
        pattern = re.compile(regexp, re.I)
        match   = pattern.search(formatStr)
        if match:
            # has [:zero_padded_length] ?
            if match.group('length'):
                strLen = int(match.group('length')[1:]) # remove leading ":"
                if strLen > 10:
                    msgDebug("Values greater than 10 shouldn't be necessary...", __name__)
                    strLen = 10
                if episode[var] < 0:
                    res = replChar * strLen
                else:
                    fmt = "%%0%dd" % strLen
                    res = fmt % episode[var]
                # Apply result
                formatStr = pattern.sub( res, formatStr )
            else:
                if episode[var] < 0:
                    res = replChar
                else:
                    res = str( episode[var] )
                # Apply result
                formatStr = pattern.sub( res, formatStr )

    # Process 2 args vars
    for var in vars2Args:
        regexp  = regexp2Args % var
        pattern = re.compile(regexp, re.I)
        match   = pattern.search(formatStr)
        if match:
            # has [:length] ?
            if match.group('length'):
                # Requested length
                strLen = int(match.group('length')[1:]) # remove leading ":"
                # has [:trailing_chars] ?
                if match.group('trail'):
                    appendLen = len( match.group('trail')[1:] )
                    # Append trailing chars only if longer than
                    # var_length + trailing_chars_length
                    if ( strLen+appendLen ) < len(episode[var]):
                        res = episode[var][0:strLen]+match.group('trail')[1:]
                    else:
                        res = episode[var]
                else:
                    res = episode[var][0:strLen]
                # Apply results
                formatStr = pattern.sub(res, formatStr)
            else:
                formatStr = pattern.sub(episode[var], formatStr)

    return formatStr


###############################################################################
## Function   : checkRangeOverlap(lstRanges)
## Description: Check whether or not given ranges ar overlapping
##
## Args:
##   - lstRanges: [
##                 (start, stop),
##                 (..., ...),
##                 ...
##                ]
##
## Return:
##   - True : Ranges are overlapping
##   - False: Ranges are *NOT* overlapping
###############################################################################
def checkRangeOverlap( lstRanges ):
    list = []
    for rng in lstRanges:
        start, stop = rng
        for i in range( start, stop+1 ):
            if i in list:
                return True
            else:
                list.append(i)
    return False


###############################################################################
## Function   : sortShowsByName(lstShows)
## Description: Sort given shows by name
##
## Args:
##   - lstShows: [
##                 { ...show info... }, # as returned by the parser
##                 { ... },
##                 ...
##               ]
##
## Return:
##   - Sorted lstShows
###############################################################################
def sortShowsByName(lstShows):
    showNames = [ show['name'] for show in lstShows ]
    showNames.sort()
    sortedShows = []
    for showName in showNames:
        for show in lstShows:
            if show['name'] == showName:
                sortedShows.append(show)

    return sortedShows


###############################################################################
## Function   : sortColorsByRange(lstColors)
## Description: Sort given colors by ranges
##
## Args:
##   - lstColors: [
##                 ( ...colors info... ), # as returned by Config()
##                 ( ... ),
##                 ...
##               ]
##
## Return:
##   - Sorted lstColors
###############################################################################
def sortColorsByRange(lstColors):
    tmpLstColors = []

    # Guess the min and max values
    i = 0
    for color in lstColors:
        i += 1
        if i == 1:
            minVal, maxVal = color[0], color[1]
        if color[0] < minVal: minVal = color[0]
        if color[1] > maxVal: maxVal = color[1]

    # Do the sorting
    for i in range(minVal, maxVal+1):
        for color in lstColors:
            if color[0] == i:
                tmpLstColors.append(color)

    return tmpLstColors
