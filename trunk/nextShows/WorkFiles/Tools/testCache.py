#!/usr/bin/env python
# -*- coding: utf-8 -*-

import cPickle, os, re
from datetime import datetime

pattern    = re.compile( r'^show_\d+$' )
baseDir    = os.path.expanduser( "~/.superkaramba/nextShows/cache" )
dirContent = os.listdir( baseDir )
maxLen     = 0
epList     = []

print "Now: %s UTC\n" % datetime.utcnow()

for file in dirContent:
    match = pattern.match( file )
    if match:
        fp = open( os.path.join( baseDir, file ) , "rb" )
        data = cPickle.load( fp )
        fp.close()

        showName  = data['episode_list'][0]['show']
        cacheDate = data['fetch_time']

        if len( showName ) > maxLen:
            maxLen = len( showName )

        ep = ( showName, datetime.fromtimestamp( cacheDate ) )
        epList.append( ep )

for episode in epList:
    disp  = episode[0]
    disp += " " * ( maxLen - len( episode[0] ) )
    print "%s: %s UTC" % ( disp, episode[1] )
