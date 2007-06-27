#!/usr/bin/env python
# -*- coding: utf-8 -*-
#######################################################################
# Coding: UTF-8, 4 spaces indent, LF line terminator
#######################################################################

from PyQt4.Qt import *


class ColorViewerWidget(QWidget):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)

        self.setMouseTracking( True )
        self.setCursor( QCursor( Qt.CrossCursor ) )

        self.mousePosX = -100
        self.mousePosY = -100


    def mouseMoveEvent( self, event ):
        self.mousePosX = event.pos().x()
        self.mousePosY = event.pos().y()
        self.update()


    def paintEvent(self, event):
        self.drawWidget()


    def drawWidget(self):
        painter = QPainter()
        painter.begin( self )


        # Coordinates conversion/transformation
        pTL = QPoint( -100, -10 )
        pBR = QPoint( 100, 10 )
        painter.setWindow( QRect( pTL, pBR ) )
#        pTL = QPoint( 0, self.height()/2-100 )
#        pBR = QPoint( self.width(), self.height()/2+100 )
#        painter.setViewport( QRect( pTL, pBR ) )
        
        
        ########################################################################
        color = QColor( "#CC0000" )
        brush = QBrush( Qt.SolidPattern )
        brush.setColor( color )
        painter.setBrush( brush )
        painter.setPen( QPen( color ) )
        painter.drawRect( QRectF( QPointF( -99.5, -3 ), QPointF( -0.5, 3 ) ) )
        ########################################################################
        color = QColor( "#00CC00" )
        brush = QBrush( Qt.SolidPattern )
        brush.setColor( color )
        painter.setBrush( brush )
        painter.setPen( QPen( color ) )
        painter.drawRect( QRectF( QPointF( -0.5, -3 ), QPointF( 0.5, 3 ) ) )
        ########################################################################
        color = QColor( "#0000CC" )
        brush = QBrush( Qt.SolidPattern )
        brush.setColor( color )
        painter.setBrush( brush )
        painter.setPen( QPen( color ) )
        painter.drawRect( QRectF( QPointF( 9.5, -3 ), QPointF( 70.5, 3 ) ) )
        ########################################################################
        color = QColor( "#CACACA" )
        brush = QBrush( Qt.SolidPattern )
        brush.setColor( color )
        painter.setBrush( brush )
        painter.setPen( QPen( color ) )
        painter.drawRect( QRectF( QPointF( 4.5, -3 ), QPointF( 5.5, 3 ) ) )
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

        painter.resetMatrix()
        painter.setPen( QPen( QColor( "#000000" ) ) )
        #pH1 = QPoint( self.mousePosX-10, self.mousePosY )
        #pH2 = QPoint( self.mousePosX+10, self.mousePosY )
        #pV1 = QPoint( self.mousePosX, self.mousePosY-10 )
        #pV2 = QPoint( self.mousePosX, self.mousePosY+10 )
        #painter.drawLine( pH1, pH2 )
        #painter.drawLine( pV1, pV2 )
        painter.drawText( QPoint(10,20), "%03dx%03d"%(self.mousePosX,self.mousePosY) )

        painter.end()
