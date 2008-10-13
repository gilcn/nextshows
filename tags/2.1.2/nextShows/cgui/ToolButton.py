#!/usr/bin/env python
# -*- coding: utf-8 -*-
#######################################################################
# nextShows - Drop aware QToolButton
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


class ToolButton(QToolButton):
    def __init__(self, parent=None):
        QToolButton.__init__(self, parent)

        # own Mime-Type
        self.ownMimeType = "application/x-nextShows-listIdx"

        # Accept drops
        self.setAcceptDrops(True)


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
