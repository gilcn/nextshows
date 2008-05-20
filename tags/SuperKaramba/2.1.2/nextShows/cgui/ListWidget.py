#!/usr/bin/env python
# -*- coding: utf-8 -*-
#######################################################################
# nextShows - Drag n' Drop aware QListWidget
# Copyright (C) 2008 Gilles CHAUVIN <gcnweb@gmail.com>
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

from PyQt4.Qt import *


class ListWidget(QListWidget):
    def __init__(self, parent=None):
        QListWidget.__init__(self, parent)

        # Dirty but we use our own Mime-Type to prevent DnD from
        # other apps / widgets
        self.ownMimeType = "application/x-nextShows-listIdx"

        # Drag start position
        self.dragStartPosition = QPoint()
        # Should we accept Drags ?
        self.dragsAccepted = False
        # ...and Drops ?
        self.setAcceptDrops(False)


    # Do we support drags ?
    def setAcceptDrags(self, on):
        self.dragsAccepted = on


    def mousePressEvent(self, event):
        if self.dragsAccepted:
            if event.button() == Qt.LeftButton:
                self.dragStartPosition = QPoint(event.pos())
        QListWidget.mousePressEvent(self, event)


    def mouseMoveEvent(self, event):
        if self.dragsAccepted:
            if event.buttons() & Qt.LeftButton:
                distance = (event.pos() - self.dragStartPosition).manhattanLength()
                if distance >= QApplication.startDragDistance():
                    self._startDrag()
        QListWidget.mouseMoveEvent(self, event)


    def _startDrag(self):
        item = self.currentItem()
        if item:
            mimeData = QMimeData()
            data = QByteArray()
            data.append(item.data(Qt.UserRole).toString())
            mimeData.setData(self.ownMimeType, data)
            drag = QDrag(self)
            drag.setMimeData(mimeData)
            drag.exec_(Qt.CopyAction)


    def dragEnterEvent(self, event):
        if event.source() != self:
            if event.mimeData().hasFormat(self.ownMimeType):
                if event.proposedAction() == Qt.CopyAction:
                    event.accept()


    def dragMoveEvent(self, event):
        if event.source() != self:
            if event.mimeData().hasFormat(self.ownMimeType):
                if event.proposedAction() == Qt.CopyAction:
                    event.accept()


    def dropEvent(self, event):
        if event.source() != self:
            if event.mimeData().hasFormat(self.ownMimeType):
                if event.proposedAction() == Qt.CopyAction:
                    event.accept()
                    listIdx = event.mimeData().data(self.ownMimeType).toInt()[0]
                    self.emit(SIGNAL("dropReceived"), listIdx)
