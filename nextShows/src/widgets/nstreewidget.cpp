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
#include "nstreewidget.h"
// QtCode
#include <QtCore/QDebug>
// QtGui
#include <QtGui/QContextMenuEvent>
#include <QtGui/QMenu>


/*
** public:
*/
NSTreeWidget::NSTreeWidget(QWidget *parent)
    : QTreeWidget(parent)
    , m_menu(new QMenu(this))
    , m_actionTrack(new QAction(this))
    , m_actionOpenUrl(new QAction(this))
{
    m_actionTrack->setObjectName("actionTrack");
    m_actionTrack->setText(tr("Track this show"));
    m_actionTrack->setIcon(QIcon(":/pixmaps/icons/rightarrow.png"));
    m_actionOpenUrl->setObjectName("actionOpenUrl");
    m_actionOpenUrl->setText(tr("Open in web browser"));

    m_menu->addAction(m_actionTrack);
    m_menu->addAction(m_actionOpenUrl);

    connect(m_actionTrack, SIGNAL(triggered()), this, SIGNAL(addShowAction()));
    connect(m_actionOpenUrl, SIGNAL(triggered()), this, SIGNAL(openUrlAction()));
} // ctor()

NSTreeWidget::~NSTreeWidget()
{
} // dtor()


/*
** protected:
*/
void NSTreeWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QTreeWidgetItem *item = itemAt(event->pos());
    if (item)
    {
        m_menu->exec(event->globalPos());
    }
} // contextMenuEvent()


// EOF - vim:ts=4:sw=4:et:
