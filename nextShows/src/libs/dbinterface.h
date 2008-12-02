/*
** Copyright (C) 2008 Emmanuel Hamelet <kh.starlifter@gmail.com>
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

#ifndef __DBINTERFACE_H__
#define __DBINTERFACE_H__


// Own
#include "nextshows.h"
// QtSql
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>


class DbInterface
{
public:
    static DbInterface& Instance();
    bool isInitialized();

    void saveUserShows(const NextShows::ShowInfosList &shows);
    NextShows::ShowInfosList readUserShows();
    QList<int> expiredShowIds(const int &delta);
    void saveUserEpisodes(const NextShows::EpisodeListList &episodes);
    QSqlTableModel *readEpisodes() const;

private:
    DbInterface(); // ctor hidden
    DbInterface(const DbInterface &); // copy ctor hidden
    DbInterface& operator=(DbInterface const &); // assign op hidden
    ~DbInterface();

    // Database initialization
    bool init();

    bool createTables();
    bool saveShow(const NextShows::ShowInfos_t &show);
    bool saveEpisode(const NextShows::EpisodeList_t &episode, const int &idshow);
    bool deleteShow(const int &id);
    bool deleteEpisode(const int &idshow);

    bool m_databaseInitialized;
};


#endif // __DBINTERFACE_H__


// EOF - vim:ts=4:sw=4:et:
