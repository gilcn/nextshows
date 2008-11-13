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
#include <QtCore/QObject>
// QtNetwork
#include <QtNetwork/QNetworkAccessManager>
// Forward declarations
class QUrl;


class DataFetcher : public QObject
{
    Q_OBJECT

public:
    DataFetcher(QObject *parent = 0);
    ~DataFetcher();

    void searchShow(const QString &showName);

Q_SIGNALS:
    void searchResultsReady(QList<NextShows::ShowInfos_t>);

private Q_SLOTS:
    void requestFinished(QNetworkReply *);

private:
    enum RequestType {
        SearchShow,
        EpisodeList
    };

    void doRequest(const QUrl &url, const RequestType &requestType);

    QNetworkAccessManager *m_nam;
};


#endif // __DATAFETCHER_H__


// EOF - vim:ts=4:sw=4:et:
