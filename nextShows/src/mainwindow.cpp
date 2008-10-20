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
#include "version.h"

// QtCore
#include <QtCore/QDate>
#include <QtCore/QDebug>
// QtGui
#include <QtGui/QHeaderView>


/*
** public:
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_dialogConfig(0)
    , m_dialogAbout(0)
{
    m_dataModel = new QStandardItemModel(this);
    m_dataModel->setColumnCount(5);

    setupUi(this);

    QStringList labels;
    labels << tr("Show name") << tr("Episode name")
           << tr("Season #") << tr("Episode #") << tr("Date");
    m_dataModel->setHorizontalHeaderLabels(labels);
    showsTableView->setModel(m_dataModel);
    showsTableView->verticalHeader()->hide();
    showsTableView->horizontalHeader()->setResizeMode(QHeaderView::Interactive);
    showsTableView->horizontalHeader()->setStretchLastSection(true);
    showsTableView->horizontalHeader()->setCascadingSectionResizes(true);
    showsTableView->horizontalHeader()->setHighlightSections(true);
    showsTableView->horizontalHeader()->setMovable(true);

    // Fill with random stuff
    for (int i=0; i<30; ++i) {
        m_dataModel->setItem(i, 0, new QStandardItem(QString("show_%1").arg(i)));
        m_dataModel->setItem(i, 1, new QStandardItem(QString("episode_%1").arg(i)));
        m_dataModel->setItem(i, 2, new QStandardItem(QString("%1").arg(rand()%10+1)));
        m_dataModel->setItem(i, 3, new QStandardItem(QString("%1").arg(rand()%24+1)));
        QDate rndDate = QDate::currentDate().addDays(i);
        m_dataModel->setItem(i, 4, new QStandardItem(rndDate.toString("yyyy/MM/dd")));
    }

    setWindowTitle(QString("nextShows - v%1").arg(NEXTSHOWS_VERSION));
    statusBar()->showMessage(tr("nextShows started"), 1000*3);

    // Test alternate row colors
    QPalette pal(showsTableView->palette());
    pal.setColor(QPalette::Base, QColor("#C7FFFF"));
    pal.setColor(QPalette::AlternateBase, QColor("#E7FFFF"));
//    pal.setColor(QPalette::Highlight, QColor("#BEFFBE"));
    showsTableView->setPalette(pal);

    connect(actionConfigure, SIGNAL(triggered()), this, SLOT(showConfig()));
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
    connect(actionQuit, SIGNAL(triggered()), this, SLOT(close()));

    // SysTray
    SysTrayIcon *m_sysTrayIcon = new SysTrayIcon(this);
} // ctor()

MainWindow::~MainWindow()
{
} // dtor()


/*
** private Q_SLOTS:
*/
void MainWindow::showConfig()
{
    if (!m_dialogConfig) {
        m_dialogConfig = new ConfigDialog(this);
    }

    m_dialogConfig->show();
//    m_dialogConfig->adjustSize();
} // showConfig()

void MainWindow::showAbout()
{
    if (!m_dialogAbout) {
        m_dialogAbout = new AboutDialog(this);
    }
    m_dialogAbout->show();
} // showAbout()


// EOF - vim:ts=4:sw=4:et:
