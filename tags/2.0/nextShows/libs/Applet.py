#!/usr/bin/env python
# -*- coding: utf-8 -*-
#######################################################################
# nextShows - Applet class
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


import libs.tools as tools

from ConfigParser import SafeConfigParser
from datetime import date, timedelta
import os

import karamba


class Applet:

    widget     = None       # Widget reference
    widgetSize = (340, 220) # This should match default value in nextShows.theme file


    def __init__(self):
        # Refs
        self.refBgndImages  = []
        self.refHeaderTitle = 0
        self.refHeaderWhen  = 0
        self.refEpisodeList = []
        self.refEpisodeListWhen = []
        self.refEpisodeUrls = []
        # Theme infos
        self.themeName      = ""
        self.themePath      = ""
        self.themeHeaderImg = ""
        self.themeHeaderWH  = (0, 0)
        self.themeHeaderTxtTitle = ""
        self.themeHeaderTxtTitleXY = (0, 0)
        self.themeHeaderTxtTitleWH = (0, 0)
        self.themeHeaderTxtWhen = ""
        self.themeHeaderTxtWhenXY = (0, 0)
        self.themeHeaderTxtWhenWH = (0, 0)
        self.themeBodyImg   = ""
        self.themeBodyWH    = (0, 0)
        self.themeBodyTitleXY = (0, 0)
        self.themeBodyTitleWH = (0, 0)
        self.themeBodyWhenXY  = (0, 0)
        self.themeBodyWhenWG  = (0, 0)
        self.themeFooterImg = ""
        self.themeFooterWH  = (0, 0)
        self.themeLines     = 0
        # Format string
        self.episodeFormatString = ""
        # Date format
        self.dateFormat = ""
        # Colors
        self.colorList   = []
        # Episode List
        self.episodeList = []
        # browser
        self.browser     = ""
        # When format
        self.whenFormat  = 0


    ###########################################################################
    ## Draw widget background
    ###########################################################################
    def drawBackground(self):
        self._readThemeInfos(self.themeName)

        # Reset background (delete images)
        for imgRef in self.refBgndImages:
            karamba.deleteImage(Applet.widget, imgRef)
        self.refBgndImages = []
        # Header
        ref = karamba.createBackgroundImage(Applet.widget, 0, 0, self.themeHeaderImg)
        self.themeHeaderWH = karamba.getImageSize(Applet.widget, ref)
        self.refBgndImages.append(ref)
        # Header's text
        self.refHeaderTitle = karamba.createRichText(Applet.widget, self.themeHeaderTxtTitle, 0)
        karamba.moveRichText(Applet.widget, self.refHeaderTitle, self.themeHeaderTxtTitleXY[0], self.themeHeaderTxtTitleXY[1])
        karamba.setRichTextWidth(Applet.widget, self.refHeaderTitle, self.themeHeaderTxtTitleWH[0])
        self.refHeaderWhen  = karamba.createRichText(Applet.widget, self.themeHeaderTxtWhen, 0)
        karamba.moveRichText(Applet.widget, self.refHeaderWhen, self.themeHeaderTxtWhenXY[0], self.themeHeaderTxtWhenXY[1])
        karamba.setRichTextWidth(Applet.widget, self.refHeaderWhen, self.themeHeaderTxtWhenWH[0])
        #---
        # Applet must display at least 1 line
        posY = self.themeHeaderWH[1]
        ref  = karamba.createBackgroundImage(Applet.widget, 0, posY, self.themeBodyImg)
        self.themeBodyWH = karamba.getImageSize(Applet.widget, ref)
        self.refBgndImages.append(ref)
        # Display other lines...
        for i in range(1, self.themeLines):
            posY += self.themeBodyWH[1]
            ref = karamba.createBackgroundImage(Applet.widget, 0, posY, self.themeBodyImg)
            self.refBgndImages.append(ref)
        # Footer
        posY += self.themeBodyWH[1]
        ref = karamba.createBackgroundImage(Applet.widget, 0, posY, self.themeFooterImg)
        self.themeFooterWH = karamba.getImageSize(Applet.widget, ref)
        self.refBgndImages.append(ref)

        # Change widget size
        Applet.widgetSize = ( Applet.widgetSize[0], posY + self.themeFooterWH[1] )
        karamba.resizeWidget( Applet.widget, Applet.widgetSize[0], Applet.widgetSize[1] )
        karamba.redrawWidgetBackground(Applet.widget)
        karamba.redrawWidget(Applet.widget)



    ###########################################################################
    ## Displays the episode list
    ###########################################################################
    def printEpisodeList(self):

        # Reset text if necessary
        for i in range( len( self.refEpisodeList ) ):
            # Remove click areas
            karamba.removeClickArea(Applet.widget, self.refEpisodeUrls[i])
            # Remove text
            karamba.deleteText(Applet.widget, self.refEpisodeList[i])
            karamba.deleteText(Applet.widget, self.refEpisodeListWhen[i])
        self.refEpisodeUrls     = []
        self.refEpisodeList     = []
        self.refEpisodeListWhen = []

        # Write episode list
        for i in range( len( self.episodeList ) ):
            color = self._processColor( self.episodeList[i]['delta'] )

            posTitleY = self.themeHeaderWH[1] + ( self.themeBodyWH[1] * i ) + self.themeBodyTitleXY[1]
            posWhenY  = self.themeHeaderWH[1] + ( self.themeBodyWH[1] * i ) + self.themeBodyWhenXY[1]

            episodeText = tools.formatEpisode( self.episodeList[i], self.episodeFormatString )
            refT = karamba.createText(Applet.widget, self.themeBodyTitleXY[0], posTitleY, self.themeBodyTitleWH[0], self.themeBodyTitleWH[1], episodeText)
            karamba.changeTextColor(Applet.widget, refT, color[0], color[1], color[2])
            self.refEpisodeList.append( refT )

            cmd = self.browser.replace( "$url$", self.episodeList[i]['url'] )
            refUrl = karamba.createClickArea(Applet.widget, self.themeBodyTitleXY[0], posTitleY, self.themeBodyTitleWH[0], self.themeBodyTitleWH[1], cmd)
            self.refEpisodeUrls.append( refUrl )

            whenText = self._formatWhen( self.episodeList[i]['airdate'], self.episodeList[i]['delta'] )
            refW = karamba.createText(Applet.widget, self.themeBodyWhenXY[0], posWhenY, self.themeBodyWhenWH[0], self.themeBodyWhenWH[1], whenText)
            karamba.changeTextColor(Applet.widget, refW, color[0], color[1], color[2])
            karamba.setTextAlign(Applet.widget, refW, "CENTER")
            karamba.attachClickArea(Applet.widget, refW)
            self.refEpisodeListWhen.append( refW )


    ###########################################################################
    ## Refreshes the "when" column date display
    ###########################################################################
    def refreshWhenColumn(self):
        for i in range( len( self.episodeList ) ):
            whenText = self._formatWhen( self.episodeList[i]['airdate'], self.episodeList[i]['delta'] )
            karamba.changeText(Applet.widget, self.refEpisodeListWhen[i], whenText)

        karamba.redrawWidget(Applet.widget)


    ###########################################################################
    ## Return formated date suitable for display in the "when" column
    ###########################################################################
    def _formatWhen(self, airDate, delta):
        # 0 : Date Format from config => [misc], "date_format"
        # 1 : +/- Days 
        # 2 : DOTW display
        if self.whenFormat == 0:
            d = date( airDate[0], airDate[1], airDate[2] )
            ret = d.strftime(self.dateFormat)

        elif self.whenFormat == 1:
            if delta == -1 or delta == 1:
                ret = "%d day" % delta
            else:
                ret = "%d days" % delta

        elif self.whenFormat == 2:
            weekDays = ( 'Sun', 'Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat' )
            if   delta  < -1:
                ret = "%dd ago" % abs(delta)
            elif delta == -1:
                ret = "Yesterday"
            elif delta ==  0:
                ret = "Today"
            elif delta ==  1:
                ret = "Tomorrow"
            elif delta > 1 and delta < 7:
                today = date.today()
                d     = today+timedelta(days=delta)
                weekDayNum = int(d.strftime("%w"))
                ret = "Next %s." % weekDays[weekDayNum]
            elif delta >= 7:
                weeks = int(delta/7)
                ret = "%d" % weeks
                if delta%7 != 0:
                    ret += "+"
                ret += " week"
                if weeks != 1:
                    ret += "s"

        else:
            ret = "N/A"

        return ret


    ##########################################################################
    ## Read theme informations
    ##########################################################################
    def _readThemeInfos(self, theme):
        self.themeName = theme
        self.themePath = os.path.join("themes", self.themeName)
        themeInfo = os.path.join( self.themePath, "theme.info" )
        themeInfoContent = karamba.readThemeFile( Applet.widget, themeInfo )

        if themeInfoContent == "":
            tools.msgDebug("Error finding/reading %s..." % themeInfo, __name__)
            return False

        #######################################################################
        # FIXME: Unfortunately, it is not possible to directly feed ConfigParser
        # with a str()....
        # Yep! That's another ugly hack!
        #######################################################################
        tempName = os.tempnam()
        fp = open( tempName, "w" )
        fp.write( themeInfoContent )
        fp.close()
        fp = open( tempName, "r" )
        scp = SafeConfigParser()
        scp.readfp( fp )
        fp.close()
        os.unlink( tempName )
        #######################################################################

        self.themeHeaderImg = os.path.join( self.themePath, scp.get( "images", "header" ) )
        self.themeHeaderTxtTitle = scp.get( "header", "title_text" )
        X = scp.getint( "header", "title_pos_x" )
        Y = scp.getint( "header", "title_pos_y" )
        self.themeHeaderTxtTitleXY = ( X, Y )
        W = scp.getint( "header", "title_width" )
        H = 0
        self.themeHeaderTxtTitleWH = ( W, H )
        self.themeHeaderTxtWhen = scp.get( "header", "when_text" )
        X = scp.getint( "header", "when_pos_x" )
        Y = scp.getint( "header", "when_pos_y" )
        self.themeHeaderTxtWhenXY = ( X, Y )
        W = scp.getint( "header", "when_width" )
        H = 0
        self.themeHeaderTxtWhenWH = ( W, H )
        self.themeBodyImg   = os.path.join( self.themePath, scp.get( "images", "body"   ) )
        X = scp.getint( "body", "title_pos_x" )
        Y = scp.getint( "body", "title_pos_y" )
        self.themeBodyTitleXY = ( X, Y )
        W = scp.getint( "body", "title_width" )
        H = scp.getint( "body", "title_height" )
        self.themeBodyTitleWH = ( W, H )
        X = scp.getint( "body", "when_pos_x" )
        Y = scp.getint( "body", "when_pos_y" )
        self.themeBodyWhenXY = ( X, Y )
        W = scp.getint( "body", "when_width" )
        H = scp.getint( "body", "when_height" )
        self.themeBodyWhenWH = ( W, H )
        self.themeFooterImg = os.path.join( self.themePath, scp.get( "images", "footer" ) )


    ##########################################################################
    ## Read a color name, example: #112233 and return a tuple:
    ## (red, green, blue)
    ##########################################################################
    def _processColor(self, delta):
        def getRGB( colorName ):
            red   = eval( "0x%s" % colorName[1:3] )
            green = eval( "0x%s" % colorName[3:5] )
            blue  = eval( "0x%s" % colorName[5:7] )
            return (red, green, blue)

        # By default return the default color
        color = getRGB( self.colorList['default'] )

        for range in self.colorList['ranges']:
            if delta >= range[0] and delta <= range[1]:
                color = getRGB( range[2] )

        return color


    ###########################################################################
    ## Splash screen
    ###########################################################################
    class Splash:
        ## Init the splash
        def __init__(self):
            self.splashImage   = "images/nextShows_logo.png"
            self.splashImageXY = (0, 10)
            self.splashImageWH = (0,  0) # Tuple containing splashImage Width & Height
            self.splashTextXY  = (0,  0)
            self.splashTextWH  = (0,  0)
            # Refs
            self.refSplash     = None
            self.refSplashText = None

        ## Show splash
        def show(self):
            # Image
            self.refSplash     = karamba.createImage(Applet.widget, self.splashImageXY[0], self.splashImageXY[1], self.splashImage)
            self.splashImageWH = karamba.getImageSize(Applet.widget, self.refSplash)
            xPos = ( Applet.widgetSize[0] - self.splashImageWH[0] ) / 2
            self.splashImageXY = ( xPos, self.splashImageXY[1] )
            karamba.moveImage( Applet.widget, self.refSplash, self.splashImageXY[0], self.splashImageXY[1] )
            # Text
            yPos = ( self.splashImageXY[1] + self.splashImageWH[1] ) + 10
            self.splashTextXY  = ( 0, yPos )
            self.splashTextWH  = ( Applet.widgetSize[0], 14 )
            self.refSplashText = karamba.createText( Applet.widget,
                                                     self.splashTextXY[0],
                                                     self.splashTextXY[1],
                                                     self.splashTextWH[0],
                                                     self.splashTextWH[1],
                                                     "" )
            karamba.setTextAlign(Applet.widget, self.refSplashText, "CENTER")
            karamba.changeTextColor(Applet.widget, self.refSplashText, 0xFF, 0xFF, 0xFF)
            #
            for i in range(100): karamba.redrawWidget(Applet.widget)

        ## Set/change splash's text
        def setText(self, text):
            karamba.changeText(Applet.widget, self.refSplashText, text)
            for i in range(100): karamba.redrawWidget(Applet.widget)

        ## Hide splash
        def hide(self):
            karamba.deleteText(Applet.widget, self.refSplashText)
            karamba.deleteImage(Applet.widget, self.refSplash)
            for i in range(100): karamba.redrawWidget(Applet.widget)
