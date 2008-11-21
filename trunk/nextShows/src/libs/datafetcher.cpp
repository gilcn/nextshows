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
#include "datafetcher.h"
#include "nextshows.h"
#include "libs/tvrageparser.h"
// QtCore
#include <QtCore/QUrl>
// QtNetwork
#include <QtNetwork/QNetworkReply>


/*
** public:
*/
DataFetcher::DataFetcher(QObject *parent)
    : QObject(parent)
    , m_nam(new QNetworkAccessManager(this))
{
    connect(m_nam, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(requestFinished(QNetworkReply *)));
} // ctor()

DataFetcher::~DataFetcher()
{
    delete m_nam;
} // dtor()

void DataFetcher::searchShow(const QString &showName)
{
    QUrl url("http://www.tvrage.com:80/feeds/search.php");
    url.addQueryItem("results", "-1"); // Request all available results
    url.addQueryItem("show", showName);

    doRequest(url, DataFetcher::SearchShow);
} // searchShow()


/*
** private Q_SLOTS:
*/
void DataFetcher::requestFinished(QNetworkReply *reply)
{
    switch(reply->property("RequestType").toInt()) {
    case DataFetcher::SearchShow: {
        NextShows::ShowInfosList searchResults = TvRageParser::parseSearchResults(reply->readAll());

        emit searchResultsReady(searchResults);
        break;
    }
    case DataFetcher::EpisodeList: {
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
void DataFetcher::doRequest(const QUrl &url, const DataFetcher::RequestType &requestType)
{
    QNetworkRequest request;
    QString httpUA = QString("nextShows/%1 (http://nextshows.googlecode.com/)").arg(NEXTSHOWS_VERSION);
    request.setRawHeader("User-Agent", qPrintable(httpUA));
    request.setUrl(url);

    QNetworkReply *reply = m_nam->get(request);
    // Mark the request type
    reply->setProperty("RequestType", QVariant(requestType));
} // doRequest()
// EOF - vim:ts=4:sw=4:et:
