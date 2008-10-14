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
#include "mainwindow.h"

// Qt
#include <QtCore/QDate>
#include <QtCore/QDebug>
#include <QtGui/QHeaderView>


/*
** public:
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

    m_dataModel = new QStandardItemModel(this);
    m_dataModel->setColumnCount(5);
    QStringList labels;
    labels << tr("Show") << tr("Episode name")
           << tr("Season") << tr("Episode #") << tr("Date");
    m_dataModel->setHorizontalHeaderLabels(labels);
    tableView->setModel(m_dataModel);
    tableView->verticalHeader()->hide();
    tableView->horizontalHeader()->setResizeMode(QHeaderView::Interactive);
    tableView->horizontalHeader()->setStretchLastSection(true);
//    tableView->horizontalHeader()->setCascadingSectionResizes(true);
    tableView->horizontalHeader()->setHighlightSections(true);
    tableView->horizontalHeader()->setMovable(true);

    // Fill with random stuff
    for (int i=0; i<30; ++i) {
        m_dataModel->setItem(i, 0, new QStandardItem(QString("show_%1").arg(i)));
        m_dataModel->setItem(i, 1, new QStandardItem(QString("episode_%1").arg(i)));
        m_dataModel->setItem(i, 2, new QStandardItem(QString("%1").arg(rand()%10+1)));
        m_dataModel->setItem(i, 3, new QStandardItem(QString("%1").arg(rand()%24+1)));
        QDate rndDate = QDate::currentDate().addDays(i);
        m_dataModel->setItem(i, 4, new QStandardItem(rndDate.toString("yyyy/MM/dd")));
    }

    setWindowTitle("nextShows");
    statusBar()->showMessage(tr("nextShows started"), 1000*3);
} // ctor()

MainWindow::~MainWindow()
{
} // dtor()


// EOF - vim:ts=4:sw=4:et:
