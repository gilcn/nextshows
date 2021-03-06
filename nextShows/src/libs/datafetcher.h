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

/*
** This class is responsible for gathering data from the intarweb !
*/


#ifndef __DATAFETCHER_H__
#define __DATAFETCHER_H__


// Own
#include "nextshows.h"
// QtCore
#include <QtCore/QHash>
#include <QtCore/QObject>
#include <QtCore/QSet>
// QtNetwork
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
// Forward declarations
class QUrl;


class DataFetcher : public QObject
{
    Q_OBJECT

public:
    static DataFetcher * instance();
    void searchShow(const QString &showName);
    void getEpisodeList(const int &showId);

Q_SIGNALS:
    // SIG: searchResultsReady()
    // #1 : List of available shows
    // #2 : Was the request successful ?
    // #3 : Error Message
    void searchResultsReady(NextShows::ShowInfosList, bool, QString);
    // SIG: episodeListReady()
    // #1 : Show infos
    // #2 : List of all available episodes for show #1
    // #3 : Was the request successful ?
    // #4 : Error Message
    void episodeListReady(NextShows::ShowInfos_t, NextShows::EpisodeListList, bool, QString);

private Q_SLOTS:
    void requestFinished(QNetworkReply *);

private:
    enum RequestType {
        SearchShowRequest,
        ShowInfosRequest,
        EpisodeListRequest
    };
    enum CustomAttribute {
        RequestTypeAttribute = int(QNetworkRequest::User),
        ShowIdAttribute = int(QNetworkRequest::User+1),
        ShowNameAttribute = int(QNetworkRequest::User+2)
    };

    DataFetcher(QObject *parent = 0);
    DataFetcher(const DataFetcher &);
    DataFetcher * operator=(DataFetcher const &);
    ~DataFetcher();

    void doRequest(const QUrl &url, RequestType requestType, const int &showId, const QString &showname);

    // Test if we got all the necessary data before emitting signal
    void emissionCheck(const int &showId);

    // Convert NetworkError code to QString
    QString errorCodeToText(QNetworkReply::NetworkError errorCode);

    void clearShowData(const int &showId);


    QNetworkAccessManager *m_nam;

    QHash<int, NextShows::ShowInfos_t>      m_showInfosHash;
    QHash<int, QString>                     m_showInfosError;
    QHash<int, NextShows::EpisodeListList>  m_episodeListHash;
    QHash<int, QString>                     m_episodeListError;
};


#endif // __DATAFETCHER_H__


// EOF - vim:ts=4:sw=4:et:
