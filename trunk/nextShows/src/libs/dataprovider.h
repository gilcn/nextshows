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


#ifndef __DATAPROVIDER_H__
#define __DATAPROVIDER_H__


// Own
#include "datafetcher.h"
#include "nextshows.h"


class DataProvider : public QObject
{
    Q_OBJECT

public:
    // Cache
    enum CacheState {
        // File found and not expired
        CacheValid    = 0x00,
        // File not found
        CacheNotFound = 0x01,
        // File found but content expired
        CacheExpired  = 0x02,
        CacheDirty    = CacheNotFound | CacheExpired
    };

    DataProvider(QObject *parent = 0);
    ~DataProvider();

    void searchShow(const QString &showName);

Q_SIGNALS:
    // Search results are ready to be served
    void searchResultsReady(NextShows::ShowInfosList);

private:
    DataFetcher *m_dataFetcher;
};


#endif // __DATAPROVIDER_H__


// EOF - vim:ts=4:sw=4:et:
