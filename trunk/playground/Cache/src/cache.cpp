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
#include <QtCore/QVariant>
// QtSql
#include <QtSql/QSqlError>


/*
** public:
*/
Cache::Cache()
{
    qDebug() << Q_FUNC_INFO;

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("ns.db");
} // ctor()

Cache::~Cache()
{
    qDebug() << Q_FUNC_INFO;

    m_db.close();
} // dtor()

bool Cache::init()
{
    qDebug() << Q_FUNC_INFO;

	if (!m_db.open()) {
        qCritical() << "Error while opening DB:" << m_db.lastError();
        return false;
    }

	if (m_db.tables().count() == 0) {
		if (!createTables()) {
            qCritical() << "Could not create tables!";
			return false;
        }
    }

	return true;
} // init()


void Cache::saveUserShows(const QList<NextShows::ShowInfos_t> &shows)
{
    qDebug() << Q_FUNC_INFO;

    QList<NextShows::ShowInfos_t>::ConstIterator it;
    for (it = shows.begin(); it != shows.end(); ++it) {
        NextShows::ShowInfos_t show = *it;
        QSqlQuery query(m_db);
        query.prepare("INSERT INTO T_Shows (idT_Shows, ShowName, ShowUrl, Country, Started, Ended, EndedFlag, Timestamp) VALUES (:idt_shows, :showname, '', '', 0, 0, 0, 0)");
        query.bindValue(":idt_shows", show.showid);
        query.bindValue(":showname", show.name);
        
        query.exec();
    }
} // saveShows()

QList<NextShows::ShowInfos_t> Cache::readUserShows()
{
    qDebug() << Q_FUNC_INFO;

    QList<NextShows::ShowInfos_t> myShows;
    QSqlQuery query(m_db);
    query.exec("SELECT idT_Shows, ShowName FROM T_Shows");
    while (query.next()) {
        NextShows::ShowInfos_t show;
        show.showid = query.value(0).toInt();
        show.name = query.value(1).toString();
        myShows << show;
    }

    return myShows;
} // listShows()


/*
** private:
*/
bool Cache::createTables()
{
    qDebug() << Q_FUNC_INFO;

    bool status;
    QSqlQuery query(m_db);

    // T_Shows table
    status = query.exec("CREATE TABLE T_Shows (idT_Shows INTEGER PRIMARY KEY, ShowName VARCHAR(30), ShowUrl VARCHAR(256), Country VARCHAR(15), Started INTEGER, Ended INTEGER, EndedFlag BOOL, Timestamp INTEGER)");
    if (!status) {
        qCritical() << query.lastError();
        return false;
    }

    // T_Episodes table
    status = query.exec("CREATE TABLE T_Episodes (idT_Episodes INTEGER PRIMARY KEY, Shows_id INTEGER, EpisodeName VARCHAR(50), EpisodeNumber INTEGER, SeasonNumber INTEGER, Date DATE, IsSpecial BOOL)");
    if (!status) {
        qCritical() << query.lastError();
        return false;
    }

    return true;
} // createTables()


// EOF - vim:ts=4:sw=4:et:
