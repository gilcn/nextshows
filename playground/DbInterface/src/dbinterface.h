/*
** Copyright (C) 2008 Emmanuel HAMELET <kh.starlifter@gmail.com>
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

#ifndef __DBINTERFACE_H__
#define __DBINTERFACE_H__


// Own
#include "nextshows.h"
// QtSql
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>


class DbInterface
{
public:
    DbInterface();
    ~DbInterface();

    // Init the database
    bool init();

    void saveUserShows(const QList<NextShows::ShowInfos_t> &shows);
    QList<NextShows::ShowInfos_t> readUserShows();
    QList<uint> expiredShow(const int &timestamp);

//signals:
//    void stateChanged(const QString &text);

private:
    QSqlDatabase m_db;
    QSqlQuery m_query;
    enum RecordType {
            Insert,
            Update
        };

    bool createTables();
    bool saveShow(const NextShows::ShowInfos_t &show, const RecordType &rtype);
    bool deleteShow(const uint &id);
};


#endif // __DBINTERFACE_H__


// EOF - vim:ts=4:sw=4:et:
