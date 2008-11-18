/*
** Copyright (C) 2008 Emmanuel HAMELET <kh.starlifter@gmail.com>
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
#include "dbinterface.h"
// QtCore
#include <QtCore/QDebug>
#include <QtCore/QUrl>
// QtGui
#include <QtGui/QKeyEvent>
#include <QtGui/QMessageBox>


/*
** public:
*/
MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);

    m_dbinterface = new DbInterface();
    if(!m_dbinterface->init()) {
        QMessageBox::critical(this,
                              "Database error",
                              "The database could not be opened or created!\nAborting...",
                              QMessageBox::Ok);
        abort();
    }

//    connect(m_dbinterface, SIGNAL(stateChanged(const QString &)), ui.infoTextEdit, SLOT(append(const QString &)));

    connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(close()));
} // ctor()

MainWindow::~MainWindow()
{
    delete m_dbinterface;
} // dtor()


/*
** private slots:
*/
void MainWindow::on_btnSaveShow_clicked(bool /*checked*/)
{
    QList<NextShows::ShowInfos_t> myShows;
    NextShows::ShowInfos_t shows;
    if (!ui.ldtShowId->text().isEmpty() && !ui.ldtShowName->text().isEmpty()) {
        shows.showid = ui.ldtShowId->text().toUInt();
        shows.name = ui.ldtShowName->text();
        shows.link = QUrl(ui.ldtUrl->text());
        shows.country = ui.ldtCountry->text();
        shows.started = ui.ldtStarted->text().toUInt();
        shows.ended = ui.ldtEnded->text().toUInt();
        shows.endedFlag = (ui.cbxEndedFlag->checkState() == Qt::Checked) ? true : false;
        myShows << shows;
        m_dbinterface->saveUserShows(myShows);
    }
} // on_btnSaveShow_clicked()

void MainWindow::on_btnListShow_clicked(bool /*checked*/)
{
    // Clear
    ui.infoTextEdit->clear();

    QList<NextShows::ShowInfos_t> myShows = m_dbinterface->readUserShows();
    QList<NextShows::ShowInfos_t>::iterator i;
    for (i = myShows.begin(); i != myShows.end(); ++i) {
        NextShows::ShowInfos_t show = *i;
        ui.infoTextEdit->append(QString::number(show.showid)+" "+show.name);
        ui.infoTextEdit->append("  URL : "+show.link.toString());
        ui.infoTextEdit->append("  COU : "+show.country);
        ui.infoTextEdit->append("  STA : "+(QString::number(show.started)));
        ui.infoTextEdit->append("  END : "+(QString::number(show.ended)));
        QString endedFlag = (show.endedFlag) ? "True" : "False";
        ui.infoTextEdit->append("  FLA : "+endedFlag);
    }
} // on_btnListShow_clicked()

void MainWindow::on_btnCheckExpiredShows_clicked(bool /*checked*/)
{
    // Clear
    ui.infoTextEdit->clear();
    
    QList<uint> expiredshowslist = m_dbinterface->expiredShow(2880); // request shows id oldest 2880min (48hour)
    uint idshow;
    int i = 1;
    foreach (idshow, expiredshowslist) {
        ui.infoTextEdit->append(QString::number(i)+". "+QString::number(idshow));
        i++;
    }
} // on_btnCheckExpiredShows_clicked()
