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
#include "abstractprovider.h"
// QtCore
#include <QtCore/QDebug>


/*
** public:
*/
AbstractProvider::AbstractProvider(QObject *parent)
    : QObject(parent)
{
    m_fetchUrl = new FetchUrl(this);
    connect(m_fetchUrl, SIGNAL(dataReady(const QByteArray &)),
            this, SLOT(dataReceived(const QByteArray &)));
} // ctor()

AbstractProvider::~AbstractProvider()
{
} // dtor()

void AbstractProvider::searchShow(const QString &showName)
{
    QUrl url(urlForRequest(SearchShowUrl, showName));

    m_fetchUrl->getUrl(url);
} // searchShow()

void AbstractProvider::getEpisodeList(const QString &showId)
{
    QUrl url(urlForRequest(EpisodeListUrl, showId));
} // getEpisodeList()


/*
** private Q_SLOTS:
*/
void AbstractProvider::dataReceived(const QByteArray &data)
{
    qDebug() << "Search Results:";
    qDebug() << "-------------------------------------------------------------------------------";
    foreach(QVariant showItem, parseSearchResults(data)) {
        QVariantMap show(showItem.toMap());
        qDebug("%s [id: %u, started: %u, ended: %u]", qPrintable(show["name"].toString()),
                              show["showid"].toUInt(),
                              show["started"].toUInt(),
                              show["ended"].toUInt());
    }
    qDebug() << "-------------------------------------------------------------------------------";
} // dataReceived()


// EOF - vim:ts=4:sw=4:et:
