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


// Own
#include "cache.h"
// QtCore
#include <QtCore/QDebug>
#include <QtCore/QFile>
// QtSql
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>


/*
** public:
*/
Cache::Cache(QObject *parent)
    : QObject(parent)
{
} // ctor()

Cache::~Cache()
{
} // dtor()

QMap<QString, QString> Cache::getShows()
{
    // set few examples
    m_shows["2456"] = "show one";
    m_shows["1235"] = "second show";
    return m_shows;
} // getShows()

void Cache::saveShows(QString)
{
} // saveShows()

void Cache::testCacheState()
{
    // First, test if db file exist
    QFile file("ns.db");
    if (!file.exists()) {
        emit stateChanged("CacheFileNotFound");
        openDb(true);
    }
    else {
        emit stateChanged("CacheFileValid");
        openDb(false);
    }
} // testCacheState()

bool Cache::openDb(bool newfile = false)
{
    QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("ns.db");
    if (m_db.open()) {
        emit stateChanged("DB Open");
    }
    else {
        emit stateChanged("DB Open error");
        return(false);
    }
    // If db file don't exist, create it!
    if (newfile==true) {
        QSqlQuery m_query;
        m_query.exec("CREATE TABLE T_Shows (idT_Shows INTEGER PRIMARY KEY, ShowName VARCHAR(30), Link VARCHAR(256), Country VARCHAR(15), Started INTEGER, Ended INTEGER, EndedFlag BOOL)");
        m_query.exec("CREATE TABLE T_Episode (Shows_id INTEGER, EpisodeName VARCHAR(50), EpisodeId INTEGER, EpisodeNumber INTEGER)");
    }
    return(true);
} // openDB()

// EOF - vim:ts=4:sw=4:et:
