#!/usr/bin/env python
# -*- coding: utf-8 -*-
#######################################################################
# nextShows - Format Help Dialog
# Copyright (C) 2006-2007 Gilles CHAUVIN <gcnweb@gmail.com>
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

from PyQt4 import QtCore, QtGui
from FormatHelp_ui import Ui_FormatHelp


class FormatHelp(QtGui.QDialog):
    def __init__(self, parent=None):
        QtGui.QDialog.__init__(self, parent)
        self.ui = Ui_FormatHelp()
        self.ui.setupUi(self)


    # Send SIGNAL
    def sendSignal(self):
        self.emit( QtCore.SIGNAL("hideWindow()") )

    # Click on the "Close" button
    @QtCore.pyqtSignature("on_btnClose_clicked()")
    def on_btnClose_clicked(self):
        self.sendSignal()

    # React on Escape or "Q" key press
    def keyPressEvent(self, event):
        if event.key() == QtCore.Qt.Key_Escape or event.key() == QtCore.Qt.Key_Q:
            self.sendSignal()
        event.ignore()  # Ignore the event

    # React on window close
    def closeEvent(self, event):
        self.sendSignal()
        event.ignore()  # Ignore the closeEvent
