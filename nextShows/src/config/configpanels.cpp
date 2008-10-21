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
#include "configpanels.h"

// QtGui
#include <QtGui/QButtonGroup>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>


/*
** public:
*/
ConfigCategories::ConfigCategories(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout();

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
    layout->addWidget(button);

    ADD_CATEGORY(findShows, tr("Find Shows"), television.png, 0);
    ADD_CATEGORY(Cat1, tr("Category 1"), television.png, 1);
    ADD_CATEGORY(Cat2, tr("Category 2"), television.png, 2);
    ADD_CATEGORY(Cat3, tr("Category 3"), television.png, 3);

    findShows->setChecked(true);
    layout->setMargin(0);
    layout->setSpacing(0);

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    setLayout(layout);
} // ctor()

ConfigCategories::~ConfigCategories()
{
} // dtor()


// EOF - vim:ts=4:sw=4:et:
