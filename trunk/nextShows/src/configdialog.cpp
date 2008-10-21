/*
** Copyright (C) 2008 Gilles CHAUVIN <gcnweb+nextshows@gmail.com>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2  of  the  License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be  useful, but
** WITHOUT  ANY  WARRANTY;  without  even  the   implied   warranty  of
** MERCHANTABILITY or FITNESS FOR A  PARTICULAR  PURPOSE. See  the  GNU
** General Public License for more details.
**
** You should have received a copy of the GNU  General  Public  License
** along with  this  program;  if  not,  write  to  the  Free  Software
** Foundation, Inc.,
** 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


// Own
#include "configdialog.h"
#include "config/configpanels.h"
#include "config/findshows.h"

// QtCore
#include <QtCore/QDebug>


/*
** public:
*/
ConfigDialog::ConfigDialog(QWidget *parent)
    : QDialog(parent, Qt::Dialog)
{
    ui.setupUi(this);

    m_layoutCats = new QHBoxLayout();
    ui.wCategories->setLayout(m_layoutCats);
    ConfigCategories *panelCats = new ConfigCategories();
    m_layoutCats->addWidget(panelCats);


    m_layoutPanel = new QHBoxLayout();
    ui.wPanel->setLayout(m_layoutPanel);
    FindShows *panel = new FindShows();
    m_layoutPanel->addWidget(panel);
} // ctor()

ConfigDialog::~ConfigDialog()
{
} // dtor()


// EOF - vim:ts=4:sw=4:et:
