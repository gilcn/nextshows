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
#include <QtCore/QVariant>
// QtSql
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>


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

void Cache::saveShows(QMap<QString, QString> shows)
{
    foreach (QString id, shows.keys()) {
        QSqlQuery query;
        query.prepare("INSERT INTO T_Shows (idT_Shows, ShowName, ShowUrl, Country, Started, Ended, EndedFlag, Timestamp) VALUES (:idt_shows, :showname, '', '', 0, 0, 0, 0)");
        query.bindValue(":idt_shows", id);
        query.bindValue(":showname", shows.value(id));
        query.exec();
        if (query.lastError().isValid())
            qDebug() << query.lastError();
        
    }
} // saveShows()

QMap<QString, QString> Cache::getShows(QString search)
{
    // set few examples
    //m_shows["2456"] = "show one";
    //m_shows["1235"] = "second show";
    QSqlQuery query("SELECT idT_Shows, ShowName FROM T_Shows",m_db);
    //m_query.exec("SELECT idT_Shows, ShowName FROM T_Shows");
    while (query.next()) {
        QString id_show = query.value(0).toString();
        qDebug() << id_show;
        QString show_name = query.value(1).toString();
        m_shows[id_show] = show_name;
    }
    /*for (int i = 0; i < 4; ++i) {
        QStandardItem *item = new QStandardItem(QString("item %0").arg(i));
        m_modelShow->appendRow(item);
        //parentItem = item;
    }*/
    return m_shows;
} // listShows()

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
        //QSqlQuery m_query;
        QSqlQuery query1("CREATE TABLE T_Shows (idT_Shows INTEGER PRIMARY KEY, ShowName VARCHAR(30), ShowUrl VARCHAR(256), Country VARCHAR(15), Started INTEGER, Ended INTEGER, EndedFlag BOOL, Timestamp INTEGER)",m_db);
        QSqlQuery query2("CREATE TABLE T_Episodes (idT_Episodes INTEGER PRIMARY KEY, Shows_id INTEGER, EpisodeName VARCHAR(50), EpisodeNumber INTEGER, SeasonNumber INTEGER, Date DATE, IsSpecial BOOL)",m_db);
    }
    return(true);
} // openDB()

// EOF - vim:ts=4:sw=4:et:
