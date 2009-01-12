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
    , m_actionExpandAll(new QAction(this))
    , m_actionCollapseAll(new QAction(this))
{
    m_actionTrack->setObjectName("actionTrack");
    m_actionTrack->setIcon(QIcon(":/pixmaps/icons/rightarrow.png"));
    m_actionTrack->setText(tr("Track this show"));
    m_actionOpenUrl->setObjectName("actionOpenUrl");
    m_actionOpenUrl->setIcon(QIcon(":/pixmaps/icons/browser.png"));
    m_actionOpenUrl->setText(tr("Open in web browser"));
    m_actionExpandAll->setObjectName("actionExpandAll");
    m_actionExpandAll->setIcon(QIcon(":/pixmaps/icons/expand.png"));
    m_actionExpandAll->setText(tr("Expand all"));
    m_actionCollapseAll->setObjectName("actionCollapseAll");
    m_actionCollapseAll->setIcon(QIcon(":/pixmaps/icons/collapse.png"));
    m_actionCollapseAll->setText(tr("Collapse all"));

    m_menu->addAction(m_actionTrack);
    m_menu->addAction(m_actionOpenUrl);
    m_menu->addSeparator();
    m_menu->addAction(m_actionExpandAll);
    m_menu->addAction(m_actionCollapseAll);

    connect(m_actionTrack, SIGNAL(triggered()), this, SIGNAL(addShowAction()));
    connect(m_actionOpenUrl, SIGNAL(triggered()), this, SIGNAL(openUrlAction()));
    connect(m_actionExpandAll, SIGNAL(triggered()), this, SLOT(expandAll()));
    connect(m_actionCollapseAll, SIGNAL(triggered()), this, SLOT(collapseAll()));
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
    if (item) {
        bool state = (item->flags() & Qt::ItemIsEnabled);
        m_actionTrack->setEnabled(state);
        m_actionOpenUrl->setEnabled(state);

        m_menu->exec(event->globalPos());
    }
} // contextMenuEvent()


// EOF - vim:ts=4:sw=4:et:
