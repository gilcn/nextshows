/*
 *   Copyright 2008 Gilles CHAUVIN <gcnweb@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as
 *   published by the Free Software Foundation; either version 2,
 *   or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "tvragesearch.h"

#include <QtCore/QDebug>
#include <QtCore/QUrl>


// Public
TvRageSearch::TvRageSearch(QWidget *parent)
    : QDialog(parent, Qt::Window)
{
    m_http = new QHttp(this);
    connect(m_http, SIGNAL(requestFinished(int, bool)),
            this, SLOT(httpRequestFinished(int, bool)));

    m_progressAnimation = new AnimatedImage(this, ":/pics/working.png");
    connect(m_progressAnimation, SIGNAL(newFrame(const QPixmap &)),
            this, SLOT(setProgressPic(const QPixmap &)));

    ui.setupUi(this);

    // Lookup
    //connect(ui.btnLookup, SIGNAL(clicked()), this, SLOT(lookup()));
    // Quit
    //connect(ui.btnQuit, SIGNAL(clicked()), this, SLOT(close()));

//    ui.btnLookup->blockSignals(true);
}

TvRageSearch::~TvRageSearch()
{
    delete m_progressAnimation;
    delete m_http;
}


// Private slots
void TvRageSearch::on_btnLookup_clicked()
{
    if (ui.leSearch->text().isEmpty()) {
        qDebug() << tr("No show to search for...");
        return;
    }
    ui.btnLookup->setEnabled(false);
    m_progressAnimation->start();
    ui.tableResults->setRowCount(0);
    ui.tableResults->clearContents();

    // Prepare URL
    QUrl url("http://www.tvrage.com/feeds/search.php", QUrl::StrictMode);
    url.setPort(80);
    QPair<QString, QString> show("show", ui.leSearch->text());
    QList< QPair<QString, QString> > params;
    params << show;
    url.setQueryItems(params);
    qDebug() << url.toEncoded();

    // HTTP request
    m_http->setHost(url.host(), QHttp::ConnectionModeHttp, url.port());
    m_httpGetId = m_http->get(url.toEncoded(QUrl::RemoveScheme | QUrl::RemoveAuthority));
}

void TvRageSearch::setProgressPic(const QPixmap &pic) const
{
    ui.imgProgress->setPixmap(pic);
}

void TvRageSearch::httpRequestFinished(const int requestId, const bool error) const
{
    if (requestId != m_httpGetId)
        return;
    if (error)
        qDebug() << m_http->errorString();

    // Reset to initial state
    m_progressAnimation->stop();
    ui.imgProgress->setPixmap(QPixmap(":/pics/idle.png"));
    ui.btnLookup->setEnabled(true);

    QList<TvRageParser::show_t> showList;
    showList = TvRageParser::parseSearchResults(m_http->readAll());
    if (showList.isEmpty())
        qDebug() << tr("Empty! No shows found?");

    ui.tableResults->setRowCount(showList.count());
    for (int i=0; i < showList.count(); ++i) {
        QTableWidgetItem *itemShowid=new QTableWidgetItem(tr("%1").arg(showList.value(i).showid));
        ui.tableResults->setItem(i, 0, itemShowid);
        QTableWidgetItem *itemName=new QTableWidgetItem(showList.value(i).name);
        ui.tableResults->setItem(i, 1, itemName);
        QTableWidgetItem *itemLink=new QTableWidgetItem(showList.value(i).link);
        ui.tableResults->setItem(i, 2, itemLink);
        QTableWidgetItem *itemCountry=new QTableWidgetItem(showList.value(i).country);
        ui.tableResults->setItem(i, 3, itemCountry);
        QTableWidgetItem *itemStarted=new QTableWidgetItem(tr("%1").arg(showList.value(i).started));
        ui.tableResults->setItem(i, 4, itemStarted);
        QTableWidgetItem *itemEnded=new QTableWidgetItem(tr("%1").arg(showList.value(i).ended));
        ui.tableResults->setItem(i, 5, itemEnded);
        QTableWidgetItem *itemSeasons=new QTableWidgetItem(tr("%1").arg(showList.value(i).seasons));
        ui.tableResults->setItem(i, 6, itemSeasons);
        QTableWidgetItem *itemClassification=new QTableWidgetItem(showList.value(i).classification);
        ui.tableResults->setItem(i, 7, itemClassification);
        QTableWidgetItem *itemGenres=new QTableWidgetItem(showList.value(i).genres);
        ui.tableResults->setItem(i, 8, itemGenres);
    }
}

// Quit
void TvRageSearch::on_btnQuit_clicked()
{
    close();
}
