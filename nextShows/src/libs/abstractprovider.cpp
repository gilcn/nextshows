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
#include "abstractprovider.h"
#include "version.h"
// QtCore
#include <QtCore/QDebug>
// QtNetwork
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>


/*
** public:
*/
AbstractProvider::AbstractProvider(QObject *parent)
    : QObject(parent)
{
    m_networkManager = new QNetworkAccessManager(this);
    connect(m_networkManager, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(requestFinished(QNetworkReply *)));
} // ctor()

AbstractProvider::~AbstractProvider()
{
    delete m_networkManager;
} // dtor()

void AbstractProvider::searchShow(const QString &showName)
{
    QUrl url(urlForRequest(SearchShow, showName));
    doRequest(url, AbstractProvider::SearchShow);
} // searchShow()

void AbstractProvider::getEpisodeList(const QString &showId)
{
    QUrl url(urlForRequest(EpisodeList, showId));
    doRequest(url, AbstractProvider::EpisodeList);
} // getEpisodeList()


/*
** private Q_SLOTS:
*/
void AbstractProvider::requestFinished(QNetworkReply *reply)
{
    switch(reply->property("RequestType").toInt()) {
    case AbstractProvider::SearchShow: {
        QList<NextShows::ShowInfos_t> searchResults(parseSearchResults(reply->readAll()));

        /*
        qDebug();
        qDebug("Search Results (%s):", qPrintable(reply->request().url().toString()));
        qDebug() << "-------------------------------------------------------------------------------";
        foreach(NextShows::ShowInfos_t showEntry, searchResults) {
            qDebug("%s [id: %u, started: %u, ended: %u]", qPrintable(showEntry.name),
                                  showEntry.showid, showEntry.started, showEntry.ended);
        }
        qDebug() << "-------------------------------------------------------------------------------";
        */

        emit searchResultsReady(searchResults);

        break;
    }
    case AbstractProvider::EpisodeList: {
        break;
    }
    default:
        qFatal("This should never happen!\n%s", Q_FUNC_INFO);
    }

    reply->deleteLater();
} // requestFinished()


/*
** private:
*/
void AbstractProvider::doRequest(const QUrl &url, const RequestType &urlType)
{
    QNetworkRequest request;
    QString httpUA = QString("nextShows/%1 (http://nextshows.googlecode.com/)").arg(NEXTSHOWS_VERSION);
    request.setRawHeader("User-Agent", qPrintable(httpUA));
    request.setUrl(url);

    QNetworkReply *reply = m_networkManager->get(request);
    // Mark the request type
    reply->setProperty("RequestType", QVariant(urlType));
} // doRequest()


// EOF - vim:ts=4:sw=4:et:
