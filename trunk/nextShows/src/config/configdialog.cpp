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

// QtGui
#include <QtGui/QButtonGroup>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>


/*
** public:
*/
ConfigDialog::ConfigDialog(QWidget *parent)
    : QWidget(parent)
{
    m_layoutMain = new QGridLayout(this);

    QVBoxLayout *layoutCategories = new QVBoxLayout();

    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(true);

#define ADD_CATEGORY(button, label, icon, num)                            \
    QToolButton *button = new QToolButton(this);                          \
    button->setIcon(QIcon(":/images/prefs/" #icon));                      \
    button->setIconSize(QSize(64, 64));                                   \
    button->setText(label);                                               \
    button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);              \
    button->resize(74, 74);                                               \
    button->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding); \
    button->setAutoRaise(true);                                           \
    button->setCheckable(true);                                           \
    buttonGroup->addButton(button, num);                                  \
    layoutCategories->addWidget(button);

    ADD_CATEGORY(findShows, tr("Shows"), television.png, 0);
    ADD_CATEGORY(Misc, tr("Misc"), television.png, 1);

    findShows->setChecked(true);
    layoutCategories->setMargin(0);
    layoutCategories->setSpacing(1);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_layoutMain->addLayout(layoutCategories, 0, 0);

    QWidget *panelWidget = new QWidget(this);
    m_layoutMain->addWidget(panelWidget, 0, 1);
} // ctor()

ConfigDialog::~ConfigDialog()
{
} // dtor()


// EOF - vim:ts=4:sw=4:et:
