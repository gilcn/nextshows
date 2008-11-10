/*
** Copyright (C) 2008 Gilles Chauvin <gcnweb+nextshows@gmail.com>
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
#include "nslistwidget.h"
// QtCode
#include <QtCore/QDebug>
// QtGui
#include <QtGui/QContextMenuEvent>
#include <QtGui/QMenu>


/*
** public:
*/
NSListWidget::NSListWidget(QWidget *parent)
    : QListWidget(parent)
    , m_menu(new QMenu(this))
    , m_actionRemove(new QAction(this))
    , m_actionOpenUrl(new QAction(this))
{
    m_actionRemove->setObjectName("actionRemove");
    m_actionRemove->setIcon(QIcon(":/pixmaps/icons/trash.png"));
    m_actionRemove->setText(tr("Remove this show"));
    m_actionOpenUrl->setObjectName("actionOpenUrl");
    m_actionOpenUrl->setIcon(QIcon(":/pixmaps/icons/browser.png"));
    m_actionOpenUrl->setText(tr("Open in web browser"));

    m_menu->addAction(m_actionRemove);
    m_menu->addAction(m_actionOpenUrl);

    connect(m_actionRemove, SIGNAL(triggered()), this, SIGNAL(removeShowAction()));
    connect(m_actionOpenUrl, SIGNAL(triggered()), this, SIGNAL(openUrlAction()));
} // ctor()

NSListWidget::~NSListWidget()
{
} // dtor()


/*
** protected:
*/
void NSListWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QListWidgetItem *item = itemAt(event->pos());
    if (item) {
        m_menu->exec(event->globalPos());
    }
} // contextMenuEvent()


// EOF - vim:ts=4:sw=4:et:
