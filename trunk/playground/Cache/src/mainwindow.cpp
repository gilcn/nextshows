/*
** ** Copyright (C) 2008 Emmanuel HAMELET <kh.starlifter@gmail.com>
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
#include "mainwindow.h"
// QtCore
#include <QtCore/QDebug>
#include <QtCore/QMap>
// QtGui
#include <QtGui/QPushButton>

#include "cache.h"

/*
** public:
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_cache(new Cache(this))
{
    ui.setupUi(this);
    
    //connect(ui.btnCheckCache, SIGNAL(clicked(bool)), ui.textInfo, SLOT(clear()));
    connect(ui.btnCheckCache, SIGNAL(clicked(bool)), m_cache, SLOT(testCacheState()));

    connect(m_cache, SIGNAL(stateChanged(const QString &)), ui.infoTextEdit, SLOT(append(const QString &)));
    
    connect(ui.btnListShow,SIGNAL(clicked(bool)),this,SLOT(getShowList()));
} // ctor()

MainWindow::~MainWindow()
{
} // dtor()

void MainWindow::getShowList()
{
    QMap<QString, QString> map = m_cache->getShows("");
    foreach (QString id, map.keys()) {
        ui.infoTextEdit->append(id+" : "+map.value(id));
    }
}
