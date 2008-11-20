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


// Own
#include "dbinterface.h"
// QtCore
#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QVariant>
// QtSql
#include <QtSql/QSqlError>
#include <QtSql/QSqlTableModel>


#define DBCONNECTION "DbInterface"


/*
** public:
*/
DbInterface::DbInterface()
{
    qDebug() << Q_FUNC_INFO;
} // ctor()

DbInterface::~DbInterface()
{
    qDebug() << Q_FUNC_INFO;

    QSqlDatabase::database(DBCONNECTION).close();
    QSqlDatabase::removeDatabase(DBCONNECTION);
} // dtor()

bool DbInterface::init()
{
    qDebug() << Q_FUNC_INFO;

    QSqlDatabase db;

    // Prevent database from being connected several times
    if (QSqlDatabase::connectionNames().contains(DBCONNECTION)) {
        qWarning() << DBCONNECTION << "already connected!";
        db = QSqlDatabase::database(DBCONNECTION);
        if (db.isOpen()) {
            return true;
        }
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE", DBCONNECTION);
        db.setDatabaseName("ns.db");
    }

    if (!db.open()) {
        qCritical() << "Error while opening DB:" << db.lastError();
        QSqlDatabase::removeDatabase(DBCONNECTION);
        return false;
    }

    if (db.tables().count() == 0) {
        if (!createTables()) {
            qCritical() << "Could not create tables!";
            db.close();
            QSqlDatabase::removeDatabase(DBCONNECTION);
            return false;
        }
    }

    return true;
} // init()


void DbInterface::saveUserShows(const NextShows::ShowInfosList &shows)
{
    qDebug() << Q_FUNC_INFO;
    
    QSqlDatabase db = QSqlDatabase::database(DBCONNECTION);
    
    // First, select all id in db
    QList<uint> dbid;
    QSqlQuery query(db);
    query.exec("SELECT idT_Shows FROM T_Shows");
    while (query.next()) {
        dbid << query.value(0).toUInt();
    }

    QList<uint> usrid;
    NextShows::ShowInfosList::ConstIterator it;
    for (it = shows.begin(); it != shows.end(); ++it) {
        NextShows::ShowInfos_t show = *it;
        usrid << show.showid;
        if(!dbid.contains(show.showid)) { // This show is a new show, Add IT !
            saveShow(show);
            qDebug() << "Add show : " << QString::number(show.showid);
        }
    }
    uint idshow;
    foreach (idshow, dbid) {
        if (!usrid.contains(idshow)) { // This show is no longer tracked, Delete IT from DB
            qDebug() << "Delete show from DB : " << QString::number(idshow);
            deleteShow(idshow);
        }
    }
} // saveUserShows()

NextShows::ShowInfosList DbInterface::readUserShows()
{
    qDebug() << Q_FUNC_INFO;
    
    QSqlDatabase db = QSqlDatabase::database(DBCONNECTION);

    NextShows::ShowInfosList myShows;
    QSqlQuery query(db);
    query.exec("SELECT idT_Shows, ShowName, ShowUrl, Country, Started, Ended, EndedFlag, Timestamp FROM T_Shows ORDER BY ShowName");
    while (query.next()) {
        NextShows::ShowInfos_t show;
        show.showid = query.value(0).toUInt();
        show.name = query.value(1).toString();
        show.link = QUrl(query.value(2).toString());
        show.country = query.value(3).toString();
        show.started = query.value(4).toUInt();
        show.ended = query.value(5).toUInt();
        show.endedFlag = query.value(6).toBool();
        myShows << show;
    }

    return myShows;
} // readUserShows()

QList<uint> DbInterface::expiredShow(const int &timestamp)
{
    qDebug() << Q_FUNC_INFO;
    
    QSqlDatabase db = QSqlDatabase::database(DBCONNECTION);
    
    QList<uint> expiredshow;
    // Calculate the max timestamp
    int maxtimestamp = QDateTime::currentDateTime().toTime_t()-timestamp;
    QSqlQuery query(db);
    query.prepare("SELECT idT_Shows, Timestamp FROM T_Shows WHERE Timestamp < :maxtimestamp");
    query.bindValue(":maxtimestamp", maxtimestamp);
    query.exec();
    while (query.next()) {
        expiredshow << query.value(0).toUInt();
    }
    return expiredshow;
} // expiredShow()

QVariant DbInterface::readEpisodes()
{
    qDebug() << Q_FUNC_INFO;
    
    QSqlDatabase db = QSqlDatabase::database(DBCONNECTION);
    
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("T_Episodes");
    /*model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    model->removeColumn(0); // don't show the ID
    model->setHeaderData(0, Qt::Horizontal, tr("Name"));
    model->setHeaderData(1, Qt::Horizontal, tr("Salary"));*/

    return true;

} // readEpisode()


/*
** private:
*/
bool DbInterface::createTables()
{
    qDebug() << Q_FUNC_INFO;

    QSqlDatabase db = QSqlDatabase::database(DBCONNECTION);
    
    bool status;
    QSqlQuery query(db);

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
    
    // T_Version table
    status = query.exec("CREATE TABLE T_Version (Version INTEGER)");
    if (!status) {
        qCritical() << query.lastError();
        return false;
    }

    return true;
} // createTables()

bool DbInterface::saveShow(const NextShows::ShowInfos_t &show)
{
    
    QSqlDatabase db = QSqlDatabase::database(DBCONNECTION);
    
    QSqlQuery query(db);
    query.prepare("INSERT INTO T_Shows (idT_Shows, ShowName, ShowUrl, Country, Started, Ended, EndedFlag, Timestamp)"
                "VALUES (:idt_shows, :showname, :showurl, :country, :started, :ended, :enderflag, 0)");

    query.bindValue(":idt_shows", show.showid);
    query.bindValue(":showname", show.name);
    query.bindValue(":showurl", show.link.toString());
    query.bindValue(":country", show.country);
    query.bindValue(":started", show.started);
    query.bindValue(":ended", show.ended);
    query.bindValue(":endedflag", show.endedFlag);
    
    bool status;
    status = query.exec();
    if (!status) {
        qCritical() << query.lastError();
        return false;
    }
    return true;
} // saveShow()

bool DbInterface::deleteShow(const uint &id)
{
    QSqlDatabase db = QSqlDatabase::database(DBCONNECTION);
    
    QSqlQuery query(db);
    query.prepare("DELETE FROM T_shows WHERE idT_Shows = :idshow");
    query.bindValue(":idshow", id);
    bool status;
    status = query.exec();
    if (!status) {
        qCritical() << query.lastError();
        return false;
    }
    return true;
} // deleteShow()


// EOF - vim:ts=4:sw=4:et:
