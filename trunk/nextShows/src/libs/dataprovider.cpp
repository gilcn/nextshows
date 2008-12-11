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
#include "libs/dataprovider.h"
#include "libs/dbinterface.h"
// QtCore
#include <QtCore/QDebug>


/*
** public:
*/
DataProvider::DataProvider(QObject *parent)
    : QObject(parent)
{
    qDebug() << Q_FUNC_INFO;
    // Search results, simply reroute SIGNAL()
    connect(DataFetcher::instance(), SIGNAL(searchResultsReady(NextShows::ShowInfosList, bool, QString)),
            this, SIGNAL(searchResultsReady(NextShows::ShowInfosList, bool, QString)));

    // Show & Episode list update
    connect(DataFetcher::instance(), SIGNAL(episodeListReady(NextShows::ShowInfos_t, NextShows::EpisodeListList, bool, QString)),
            this, SLOT(episodeListReady(NextShows::ShowInfos_t, NextShows::EpisodeListList, bool, QString)));
} // ctor()

DataProvider::~DataProvider()
{
    qDebug() << Q_FUNC_INFO;
} // dtor()

void DataProvider::searchShow(const QString &showName)
{
    qDebug() << Q_FUNC_INFO;
    DataFetcher::instance()->searchShow(showName);
} // searchShow()

NextShows::ShowInfosList DataProvider::getTrackedShows()
{
    qDebug() << Q_FUNC_INFO;
    return DbInterface::instance().readUserShows();
} // getTrackedShows()

void DataProvider::setTrackedShows(const NextShows::ShowInfosList &showList)
{
    qDebug() << Q_FUNC_INFO;
    DbInterface::instance().saveUserShows(showList);
} // setTrackedShows()

void DataProvider::updateOutdatedShows(const int &delta)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << DbInterface::instance().expiredShowIds(0);
    qDebug() << delta;
    qDebug() << DbInterface::instance().expiredShowIds(delta);

    foreach(int id, DbInterface::instance().expiredShowIds(delta)) {
        qDebug() << id;
        if (!m_pendingUpdates.contains(id)) {
            DataFetcher::instance()->getEpisodeList(id);
            m_pendingUpdates.append(id);
        }
    }
} // updateOutdatedShows()


/*
** private Q_SLOTS
*/
void DataProvider::episodeListReady(NextShows::ShowInfos_t showInfos, NextShows::EpisodeListList episodeList, bool success, QString errorMessage)
{
    qDebug() << Q_FUNC_INFO;
    // FIXME: If showInfos couldn't be retrieved the following line will
    //        behave unexpectedly !!!
    m_pendingUpdates.removeAll(showInfos.showid);

    if (!success) {
        qWarning() << errorMessage;
        return;
    }

    qDebug() << "Received data for:" << showInfos.name;
    qDebug() << "Show ID          :" << showInfos.showid;
    DbInterface::instance().saveUserEpisodes(showInfos, episodeList);
} // episodeListReady()


// EOF - vim:ts=4:sw=4:et:
