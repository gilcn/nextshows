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

    if(!DbInterface::Instance().isInitialized()) {
        QMessageBox::critical(this,
                              "Database error",
                              "The database could not be opened or created!\nAborting...",
                              QMessageBox::Ok);
        abort();
    }

    connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(close()));
} // ctor()

MainWindow::~MainWindow()
{
} // dtor()


/*
** private slots:
*/
void MainWindow::on_btnSaveShow_clicked(bool /*checked*/)
{
    NextShows::ShowInfosList myShows;
    NextShows::ShowInfos_t shows;
    if (!ui.ldtShowId->text().isEmpty() && !ui.ldtShowName->text().isEmpty()) {
        shows.showid = ui.ldtShowId->text().toInt();
        shows.name = ui.ldtShowName->text();
        shows.link = QUrl(ui.ldtUrl->text());
        shows.country = ui.ldtCountry->text();
        shows.started = ui.ldtStarted->text().toInt();
        shows.ended = ui.ldtEnded->text().toInt();
        shows.endedFlag = (ui.cbxEndedFlag->checkState() == Qt::Checked) ? true : false;
        QMap<QString, QString> akasMap;
        akasMap["US"] = "inUS";
        akasMap["FR"] = "inFR";
        akasMap["RO"] = "inRO";
        akasMap["PL"] = "inPL";
        shows.akas = akasMap;
        QMap<QString, QString> networkMap;
        networkMap["US"] = "network";
        shows.network = networkMap;
        myShows << shows;
        DbInterface::Instance().saveUserShows(myShows);
    }
} // on_btnSaveShow_clicked()

void MainWindow::on_btnListShow_clicked(bool /*checked*/)
{
    // Clear
    ui.infoTextEdit->clear();

    NextShows::ShowInfosList myShows = DbInterface::Instance().readUserShows();
    NextShows::ShowInfosList::iterator i;
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
    
    QList<int> expiredshowslist = DbInterface::Instance().expiredShowIds(2880); // request shows id oldest 2880min (48hour)
    int idshow;
    int i = 1;
    foreach (idshow, expiredshowslist) {
        ui.infoTextEdit->append(QString::number(i)+". "+QString::number(idshow));
        i++;
    }
} // on_btnCheckExpiredShows_clicked()

void MainWindow::on_btnRequestDB_clicked(bool /*checked*/)
{
    QSqlTableModel *model = DbInterface::Instance().readEpisodes();
    ui.tblView->setModel(model);
    ui.tblView->show();
}

void MainWindow::on_btnUpdateShow_clicked(bool /*checked*/)
{    
    // Show data
    NextShows::ShowInfos_t show;
    show.showid = ui.ldtUpdateShowId->text().toInt();
    // fill with random data
    show.name = QString::fromUtf8("la tete à toto");
    show.link = QUrl("www.toto.com");
    show.country= "XX";
    show.started = 1111;
    show.ended = 5555;
    show.seasons = 666;
    show.status = "Random status";
    show.classification = "Random classification";
    QStringList genreList;
    genreList << "Adventure";
    genreList << "Action";
    show.genres = genreList;
    show.endedFlag = true;
    show.runtime = 60;
    show.airtime = QTime(05,50);
    show.airday = "Monday";
    show.timezone = "GMT-5 -DST";
    
    // Episodes data
    QList<NextShows::EpisodeList_t> EpisodeListList;
    int i = 1;
    for( i=1 ; i<4 ; i++) {
        NextShows::EpisodeList_t episode;
        episode.season = 1;
        episode.episodeCount = 3;
        episode.episodeNumber = i;
        episode.prodNumber = "905";
        episode.airDate = QDate(2004,9,29);
        episode.link = QUrl("www.toto.com/episodes/"+(char) i);
        episode.title = "titre "+(char) i;
        episode.isSpecial = false;
        EpisodeListList << episode;
    }
    DbInterface::Instance().saveUserEpisodes(show,EpisodeListList);
    
} // on_btnUpdateShow_clicked
