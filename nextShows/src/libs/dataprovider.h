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
#include "nextshows.h"
#include "libs/datafetcher.h"


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

    // Methods mainly used from the settings
    void searchShow(const QString &showName);
    NextShows::ShowInfosList getTrackedShows();
    void setTrackedShows(const NextShows::ShowInfosList &showList);

Q_SIGNALS:
    // Search results are ready to be served
    void searchResultsReady(NextShows::ShowInfosList, bool, QString);

private:
};


#endif // __DATAPROVIDER_H__


// EOF - vim:ts=4:sw=4:et:
