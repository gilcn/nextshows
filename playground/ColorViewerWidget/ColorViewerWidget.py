#!/usr/bin/env python
# -*- coding: utf-8 -*-
#######################################################################
# Coding: UTF-8, 4 spaces indent, LF line terminator
#######################################################################

from PyQt4.Qt import *


class ColorViewerWidget(QWidget):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)

    def paintEvent(self, event):
        print self.width()
        painter = QPainter()
        painter.begin( self )


        # Coordinates conversion/transformation
        pTL = QPoint( -100, -50 )
        pBR = QPoint( 100, 50 )
        painter.setWindow( QRect( pTL, pBR ) )
#        pTL = QPoint( 0, self.height()/2-60 )
#        pBR = QPoint( self.width(), self.height()/2+60 )
#        painter.setViewport( QRect( pTL, pBR ) )
        
        
        ########################################################################
        color = QColor( "#CC0000" )
        brush = QBrush( Qt.SolidPattern )
        brush.setColor( color )
        painter.setBrush( brush )
        painter.setPen( QPen( color ) )
        painter.drawRect( QRect( QPoint( -99, -3 ), QPoint( -1, 3 ) ) )
        ########################################################################
        color = QColor( "#00CC00" )
        brush = QBrush( Qt.SolidPattern )
        brush.setColor( color )
        painter.setBrush( brush )
        painter.setPen( QPen( color ) )
        painter.drawRect( QRect( QPoint( 0, -3 ), QPoint( 5, 3 ) ) )
        ########################################################################
        color = QColor( "#0000CC" )
        brush = QBrush( Qt.SolidPattern )
        brush.setColor( color )
        painter.setBrush( brush )
        painter.setPen( QPen( color ) )
        painter.drawRect( QRect( QPoint( 10, -3 ), QPoint( 70, 3 ) ) )
        ########################################################################


        # Draw scale
        painter.setPen( QPen( QColor( "#666666" ) ) )
        painter.drawLine( -100, 0, 100, 0 )
        for i in range(-100, 100+1):
            if i==-100 or i==0 or i==100:
                length=10
            else:
                length=5
            if i%10==0:
                painter.drawLine( i, -length, i, length)

        painter.end()
