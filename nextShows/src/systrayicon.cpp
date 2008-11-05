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
#include "systrayicon.h"

// QtGui
#include <QtGui/QAction>
#include <QtGui/QMenu>


/*
** public:
*/
SysTrayIcon::SysTrayIcon(QObject *parent)
    : QObject(parent)
{
    m_sysTrayIcon = new QSystemTrayIcon(parent);
    m_sysTrayIcon->setIcon(QIcon(":/pixmaps/systray/systrayicon.png"));

    QAction *actionQuit = new QAction(tr("&Quit"), this);
    actionQuit->setIcon(QIcon(":/pixmaps/icons/exit.png"));
//    connect(actionQuit, SIGNAL(triggered()), this, SLOT(quit()));

    QMenu *menu = new QMenu();
    menu->addAction(actionQuit);

    m_sysTrayIcon->setContextMenu(menu);

    m_sysTrayIcon->show();
} // ctor()

SysTrayIcon::~SysTrayIcon()
{
} // dtor()


// EOF - vim:ts=4:sw=4:et: