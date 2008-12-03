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


/*
** public:
*/
DataProvider::DataProvider(QObject *parent)
    : QObject(parent)
    , m_dataFetcher(new DataFetcher(this))
{
    // Search results, simply reroute SIGNAL()
    connect(m_dataFetcher, SIGNAL(searchResultsReady(NextShows::ShowInfosList)),
            this, SIGNAL(searchResultsReady(NextShows::ShowInfosList)));
    // Search results error
    connect(m_dataFetcher, SIGNAL(dataRetrievalError(DataFetcher::GatheringError, const QString &, const int &)),
            this, SIGNAL(dataRetrievalError(DataFetcher::GatheringError, const QString &, const int &)));
} // ctor()

DataProvider::~DataProvider()
{
    delete m_dataFetcher;
} // dtor()

void DataProvider::searchShow(const QString &showName)
{
    m_dataFetcher->searchShow(showName);
} // searchShow()

NextShows::ShowInfosList DataProvider::getTrackedShows()
{
    return DbInterface::Instance().readUserShows();
} // getTrackedShows()

void DataProvider::setTrackedShows(const NextShows::ShowInfosList &showList)
{
    DbInterface::Instance().saveUserShows(showList);
} // setTrackedShows()


// EOF - vim:ts=4:sw=4:et:
