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

void DataFetcher::getEpisodeList(const int &showId)
{
    QUrl urlEL("http://www.tvrage.com/feeds/episode_list.php");
    urlEL.addQueryItem("sid", QString::number(showId));
    doRequest(urlEL, DataFetcher::EpisodeList, showId);

    QUrl urlSI("http://www.tvrage.com/feeds/showinfo.php");
    urlSI.addQueryItem("sid", QString::number(showId));
    doRequest(urlSI, DataFetcher::ShowInfos, showId);
} // getEpisodeList()


/*
** private Q_SLOTS:
*/
void DataFetcher::requestFinished(QNetworkReply *reply)
{
    int requestType = reply->property("RequestType").toInt();
    int showId = reply->property("ShowID").toInt();

    switch(requestType) {
    case DataFetcher::SearchShow: {
        NextShows::ShowInfosList searchResults = TvRageParser::parseSearchResults(reply->readAll());

        emit searchResultsReady(searchResults);
        break;
    }
    case DataFetcher::ShowInfos: {
        m_showInfosHash[showId] = TvRageParser::parseShowInfos(reply->readAll());
        checkEpisodeListEmission(showId);
        break;
    }
    case DataFetcher::EpisodeList: {
        m_episodeListHash[showId] = TvRageParser::parseEpisodeList(reply->readAll());
        checkEpisodeListEmission(showId);
        break;
    }
    default:
        qWarning("%s\nThis should never happen! [%d]", Q_FUNC_INFO, requestType);
    }

    reply->deleteLater();
} // requestFinished()


/*
** private:
*/
void DataFetcher::doRequest(const QUrl &url, DataFetcher::RequestType requestType, const int &showId)
{
    QNetworkRequest request;
    QString httpUA = QString("nextShows/%1 (http://nextshows.googlecode.com/)").arg(NEXTSHOWS_VERSION);
    request.setRawHeader("User-Agent", qPrintable(httpUA));
    request.setUrl(url);

    QNetworkReply *reply = m_nam->get(request);

    // "Tag" the request
    // TODO: There's probably a nicer way to do this ?
    reply->setProperty("RequestType", QVariant(requestType));
    reply->setProperty("ShowID", QVariant(showId));
} // doRequest()

void DataFetcher::checkEpisodeListEmission(const int &showId)
{
    bool check = (m_showInfosHash.contains(showId) && m_episodeListHash.contains(showId));

    if (check) {
        emit episodeListReady(m_showInfosHash[showId], m_episodeListHash[showId]);
        m_showInfosHash.remove(showId);
        m_episodeListHash.remove(showId);
    }
} // checkEpisodeListEmission()

// EOF - vim:ts=4:sw=4:et:
