#!/usr/bin/env python
# -*- coding: utf-8 -*-
#######################################################################

from Form_ui           import Ui_Form
from ColorViewerWidget import ColorViewerWidget

from PyQt4.Qt import *

class Form(QDialog):
    def __init__(self, parent=None):
        QDialog.__init__(self, parent)
        self.ui = Ui_Form()
        self.ui.setupUi(self)
