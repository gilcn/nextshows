#!/usr/bin/env python
# -*- coding: utf-8 -*-

import cPickle, os, re
from datetime import datetime

pattern=re.compile( r'^show_\d+$' )

baseDir = os.path.expanduser( "~/.superkaramba/nextShows/cache" )

dirContent = os.listdir( baseDir )

for file in dirContent:
    match = pattern.match( file )
    if match:
        fp = open( os.path.join( baseDir, file ) , "rb" )
        data = cPickle.load( fp )
        fp.close()

        showName  = data['episode_list'][0]['show']
        cacheDate = data['fetch_time']

        print "%s: %s" % ( showName, datetime.fromtimestamp( cacheDate ) )
