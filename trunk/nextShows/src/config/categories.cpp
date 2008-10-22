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
#include "categories.h"

// QtGui
#include <QtGui/QToolButton>


namespace Config
{

/*
** public:
*/
Categories::Categories(QWidget *parent)
    : QWidget(parent)
    , m_layout(new QVBoxLayout)
    , m_buttonGroup(new QButtonGroup(this))
    , m_itemCount(0)
{
    m_buttonGroup->setExclusive(true);

    m_layout->setMargin(0);
    m_layout->setSpacing(0);

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setLayout(m_layout);

    connect(m_buttonGroup, SIGNAL(buttonClicked(int)), this, SIGNAL(categoryChanged(const int &)));
} // ctor()

Categories::~Categories()
{
} // dtor()

void Categories::addCategory(const QString &name, const QIcon &icon)
{
    QToolButton *button = new QToolButton(this);
    button->setIcon(icon);
    button->setIconSize(QSize(64, 64));
    button->setText(name);
    button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    button->resize(74, 74);
    button->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    button->setAutoRaise(true);
    button->setCheckable(true);
    m_buttonGroup->addButton(button, m_itemCount);
    m_layout->addWidget(button);

    // Check this button if it's the first
    if (m_itemCount == 0) {
        button->setChecked(true);
    }

    m_itemCount++;
} // addCategory()

} // namespace Config


// EOF - vim:ts=4:sw=4:et:
