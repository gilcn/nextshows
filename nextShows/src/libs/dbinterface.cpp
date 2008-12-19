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
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRelationalTableModel>


#define DBCONNECTION "DbInterface"


/*
** public:
*/
DbInterface& DbInterface::instance()
{
    qDebug() << Q_FUNC_INFO;
    static DbInterface DbInterfaceInstance;
    return DbInterfaceInstance;
} // instance()

bool DbInterface::isInitialized() const
{
    qDebug() << Q_FUNC_INFO;
    return m_databaseInitialized;
} // isInitialized()

bool DbInterface::saveUserShows(const NextShows::ShowInfosList &shows)
{
    qDebug() << Q_FUNC_INFO;
    
    QSqlDatabase db = QSqlDatabase::database(DBCONNECTION);
    QSqlQuery query(db);
    bool status = true;

    // Get all the show IDs from the DB
    QList<int> dbId;
    query.prepare("SELECT idT_Shows FROM T_Shows");
    if (!query.exec()) {
        qCritical() << query.lastQuery() << "\n" << query.lastError();
        return false; // Something went wrong...
    }
    while (query.next()) {
        dbId << query.value(0).toInt();
    }

    // Start transaction
    qDebug() << "Begin DB transaction";
    QSqlDatabase::database(DBCONNECTION).transaction();
    
    QList<int> usrId;
    foreach(NextShows::ShowInfos_t show, shows) {
        usrId << show.showid;
        if(!dbId.contains(show.showid)) { // New show, add it!
            qDebug() << "Add show:" << QString::number(show.showid);
            if (!saveShow(show)) {
                qCritical() << "Error when saving show:" << show.name;
                status = false;
                break; // Exit foreach
            }
        }
    }
    foreach (int showId, dbId) {
        if (!usrId.contains(showId)) { // Show no longer tracked, delete it!
            qDebug() << "Delete show:" << QString::number(showId);
            if (!deleteShow(showId)) {
                qCritical() << "Error when deleting show ID" << showId;
                status = false;
                break; // Exit foreach
            }
        }
    }

    bool crStatus = false;
    if (status) {
        crStatus = QSqlDatabase::database(DBCONNECTION).commit();
        qDebug() << "Commit:" << crStatus;
    } else {
        crStatus = QSqlDatabase::database(DBCONNECTION).rollback();
        qDebug() << "Rollback:" << crStatus;
    }

    return (status && crStatus);
} // saveUserShows()

NextShows::ShowInfosList DbInterface::readUserShows()
{
    qDebug() << Q_FUNC_INFO;
    
    QSqlDatabase db = QSqlDatabase::database(DBCONNECTION);

    NextShows::ShowInfosList myShows;
    QSqlQuery query(db);
    query.exec("SELECT idT_Shows, ShowName, ShowUrl, Country, Started, Ended, SeasonsNbr, Status, Classification, Genres,  EndedFlag, Runtime, Airtime, Airday, Timezone, Timestamp "
                "FROM T_Shows ORDER BY ShowName");
    while (query.next()) {
        NextShows::ShowInfos_t show;
        show.showid = query.value(0).toInt();
        show.name = query.value(1).toString();
        show.link = QUrl(query.value(2).toString());
        show.country = query.value(3).toString();
        show.started = query.value(4).toInt();
        show.ended = query.value(5).toInt();
        show.seasons = query.value(6).toInt();
        show.status = query.value(7).toString();
        show.classification = query.value(8).toString();
        if (!query.value(9).toString().isEmpty()) {
            show.genres = query.value(9).toString().split(",");
        }
        show.endedFlag = query.value(10).toBool();
        show.runtime = query.value(11).toInt();
        show.airtime = QTime::fromString(query.value(12).toString(), "hh:mm");
        show.airday = query.value(13).toString();
        show.timezone = query.value(14).toString();
        // retrieve T_Akas data for this show
        QSqlQuery queryAkas(db);
        QMap<QString, QString> akasMap;
        queryAkas.prepare("SELECT T_Akas_Shows_id, Country, Name FROM T_Akas WHERE T_Akas_Shows_id = :showid");
        queryAkas.bindValue(":showid",show.showid);
        queryAkas.exec();
        while (queryAkas.next()) {
            akasMap[queryAkas.value(1).toString()] = queryAkas.value(2).toString();
        }
        show.akas = akasMap;
        // retrieve T_Networks data for this show
        QSqlQuery queryNetwork(db);
        QMap<QString, QString> networkMap;
        queryNetwork.prepare("SELECT T_Networks_Shows_id, Country, Name FROM T_Networks WHERE T_Networks_Shows_id = :showid");
        queryNetwork.bindValue(":showid",show.showid);
        queryNetwork.exec();
        while (queryNetwork.next()) {
            networkMap[queryNetwork.value(1).toString()] = queryNetwork.value(2).toString();
        }
        show.akas = networkMap;
        
        myShows << show;
    }

    return myShows;
} // readUserShows()

QList<int> DbInterface::expiredShowIds(const int &delta)
{
    qDebug() << Q_FUNC_INFO;
    
    QSqlDatabase db = QSqlDatabase::database(DBCONNECTION);
    
    QList<int> expiredshow;
    // Calculate the max timestamp
    int maxtimestamp = QDateTime::currentDateTime().toTime_t()-delta;
    QSqlQuery query(db);
    query.prepare("SELECT idT_Shows, Timestamp FROM T_Shows WHERE Timestamp < :maxtimestamp");
    query.bindValue(":maxtimestamp", maxtimestamp);
    query.exec();
    while (query.next()) {
        expiredshow << query.value(0).toInt();
    }
    return expiredshow;
} // expiredShow()

bool DbInterface::saveUserEpisodes(const NextShows::ShowInfos_t &showInfo, const NextShows::EpisodeListList &episodes)
{
    qDebug() << Q_FUNC_INFO;
    
    QSqlDatabase db = QSqlDatabase::database(DBCONNECTION);

    bool status = true;

    // Start transaction
    qDebug() << "Begin DB transaction";
    QSqlDatabase::database(DBCONNECTION).transaction();
    
    // Delete all episodes for this show
    if(!deleteEpisodes(showInfo.showid)) {
        qCritical() << "Error while deleting episode list for show" << showInfo.name;
        status = false;
    }
    // Save episodes for this show
    for (int i = 0; i < episodes.size(); ++i) {
        if(!saveEpisode(episodes.at(i), showInfo.showid)) {
            qCritical() << "Error while saving episode for show" << showInfo.name;
            status = false;
            break; // Exit for loop
        }
    }
    // Update information of this show
    if (!updateShow(showInfo)) {
        qCritical("Error while updating show \"%s\" [%d]", qPrintable(showInfo.name), showInfo.showid);
        status = false;
    }

    bool crStatus = false;
    if (status) {
        crStatus = QSqlDatabase::database(DBCONNECTION).commit();
        qDebug() << "Commit:" << crStatus;
    } else {
        crStatus = QSqlDatabase::database(DBCONNECTION).rollback();
        qDebug() << "Rollback:" << crStatus;
    }

    return (status && crStatus);
} // saveUserEpisodes()


/*
** private:
*/
DbInterface::DbInterface()
{
    qDebug() << Q_FUNC_INFO;
    m_databaseInitialized = init();
    if (!m_databaseInitialized) {
        qCritical() << "Database was not initialized!";
    }
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
    // Check database version
    QSqlQuery query(db);
    bool status;
    status = query.exec("SELECT version FROM T_Version");
    if (!query.first()){
        qCritical() << "Database version in T_version table is missing ! ";
        return false;
    }
    if (DB_RELEASE != query.value(0)){
        qCritical() << "Database version mismatch ! actual : '" << query.value(0).toDouble() << "', needed : '" << DB_RELEASE <<"'";
        return false;
    }
    if (!status) {
        qCritical() << query.lastQuery() << "\n" << query.lastError();
        return false;
    }

    return true;
} // init()

bool DbInterface::createTables()
{
    qDebug() << Q_FUNC_INFO;

    QSqlDatabase db = QSqlDatabase::database(DBCONNECTION);
    
    QSqlQuery query(db);
    bool status = true;

    // Start transaction
    qDebug() << "Begin DB transaction";
    QSqlDatabase::database(DBCONNECTION).transaction();

    // T_Shows table
    query.prepare(
        "CREATE TABLE T_Shows ("
        "idT_Shows INTEGER PRIMARY KEY, "
        "ShowName TEXT, "
        "ShowUrl TEXT, "
        "Country TEXT, "
        "Started INTEGER, "
        "Ended INTEGER, "
        "SeasonsNbr INTEGER, "
        "Status TEXT, "
        "Classification TEXT, "
        "Genres TEXT, "
        "EndedFlag BOOL, "
        "Runtime INTEGER, "
        "Airtime TIME, "
        "Airday TEXT, "
        "Timezone TEXT, "
        "Timestamp INTEGER)"
    );
    if (!query.exec()) {
        qCritical() << query.lastQuery() << "\n" << query.lastError();
        status = false;
    }

    // T_Episodes table
    query.prepare(
        "CREATE TABLE T_Episodes ("
        "idT_Episodes INTEGER PRIMARY KEY, "
        "Shows_id INTEGER, "
        "EpisodeName TEXT, "
        "EpisodeCount INTEGER, "
        "EpisodeNumber INTEGER, "
        "ProdNumber TEXT, "
        "SeasonNumber INTEGER, "
        "EpisodeUrl TEXT, "
        "Date DATE, "
        "IsSpecial BOOL)"
    );
    if (!query.exec()) {
        qCritical() << query.lastQuery() << "\n" << query.lastError();
        status = false;
    }
    
    // T_Akas table
    query.prepare(
        "CREATE TABLE T_Akas ("
        "T_Akas_Shows_id INTEGER, "
        "Country TEXT, "
        "Name TEXT)"
    );
    if (!query.exec()) {
        qCritical() << query.lastQuery() << "\n" << query.lastError();
        status = false;
    }
    
    // T_Networks
    query.prepare(
        "CREATE TABLE T_Networks ("
        "T_Networks_Shows_id INTEGER, "
        "Country TEXT, "
        "Name TEXT)"
    );
    if (!query.exec()) {
        qCritical() << query.lastQuery() << "\n" << query.lastError();
        status = false;
    }
    
    // T_Version table
    query.prepare("CREATE TABLE T_Version (Version TEXT);");
    if (!query.exec()) {
        qCritical() << query.lastQuery() << "\n" << query.lastError();
        status = false;
    }
    query.prepare("INSERT INTO T_Version (Version) VALUES ('0.2.1')");
    if (!query.exec()) {
        qCritical() << query.lastQuery() << "\n" << query.lastError();
        status = false;
    }

    bool crStatus = false;
    if (status) {
        crStatus = QSqlDatabase::database(DBCONNECTION).commit();
        qDebug() << "Commit:" << crStatus;
    } else {
        crStatus = QSqlDatabase::database(DBCONNECTION).rollback();
        qDebug() << "Rollback:" << crStatus;
    }

    return (status && crStatus);
} // createTables()

bool DbInterface::saveShow(const NextShows::ShowInfos_t &show)
{
    qDebug() << Q_FUNC_INFO;
    
    QSqlDatabase db = QSqlDatabase::database(DBCONNECTION);
    QSqlQuery query(db);

    query.prepare("INSERT INTO T_Shows (idT_Shows, ShowName, ShowUrl, Country, Started, Ended, SeasonsNbr, Status, Classification, Genres, EndedFlag, Runtime, Airtime, Airday, Timezone, Timestamp)"
                "VALUES (:idt_shows, :showname, :showurl, :country, :started, :ended, :seasonsnbr, :status, :classification, :genres, :enderflag, :runtime, :airtime, :airday, :timezone, 0)");

    query.bindValue(":idt_shows", show.showid);
    query.bindValue(":showname", show.name);
    query.bindValue(":showurl", show.link.toString());
    query.bindValue(":country", show.country);
    query.bindValue(":started", show.started);
    query.bindValue(":ended", show.ended);
    query.bindValue(":seasonsnbr", show.seasons);
    query.bindValue(":status", show.status);
    query.bindValue(":classification", show.classification);
    query.bindValue(":genres", show.genres.join(","));
    query.bindValue(":endedflag", show.endedFlag);
    query.bindValue(":runtime", show.runtime);
    query.bindValue(":airtime", show.airtime);
    query.bindValue(":airday", show.airday);
    query.bindValue(":timezone", show.timezone);
    if (!query.exec()) {
        qCritical() << query.lastQuery() << "\n" << query.lastError();
        return false; // No need to continue if something went wrong
    }
    
    // retrieve the last ID insert
    int lastId = query.lastInsertId().toInt();
    // Insert T_Akas
    foreach(QString aka, show.akas.keys()) {
        qDebug() << aka << ": " << show.akas.value(aka);
        query.prepare("INSERT INTO T_Akas (T_Akas_Shows_id, Country, Name) "
                        "VALUES (:showid, :country, :name)");
        query.bindValue(":showid", lastId);
        query.bindValue(":country", aka);
        query.bindValue(":name", show.akas.value(aka));
        if (!query.exec()) {
            qCritical() << query.lastQuery() << "\n" << query.lastError();
            return false; // No need to continue if something went wrong
        }
    }
    // Insert T_Network
    foreach(QString network, show.network.keys()) {
        qDebug() << network << ": " << show.network.value(network);
        query.prepare("INSERT INTO T_Networks (T_Networks_Shows_id, Country, Name) "
                        "VALUES (:showid, :country, :name)");
        query.bindValue(":showid", lastId);
        query.bindValue(":country", network);
        query.bindValue(":name", show.network.value(network));
        if (!query.exec()) {
            qCritical() << query.lastQuery() << "\n" << query.lastError();
            return false; // No need to continue if something went wrong
        }
    }
    
    // If we reach this point then everything went fine
    return true;
} // saveShow()

bool DbInterface::saveEpisode(const NextShows::EpisodeList_t &episode, const int &showId)
{
    qDebug() << Q_FUNC_INFO;
    
    QSqlDatabase db = QSqlDatabase::database(DBCONNECTION);
    
    QSqlQuery query(db);
    
    query.prepare("INSERT INTO T_episodes (Shows_id, EpisodeName, EpisodeCount, EpisodeNumber, ProdNumber, SeasonNumber, EpisodeUrl, Date, IsSpecial) "
                    "VALUES (:show_id, :episodename, :episodecount, :episodenumber, :prodnumber, :seasonnumber, :episodeurl, :date, :isspecial)");
    query.bindValue(":show_id", showId);
    query.bindValue(":episodename", episode.title);
    query.bindValue(":episodecount", episode.episodeCount);
    query.bindValue(":episodenumber", episode.episodeNumber);
    query.bindValue(":prodnumber", episode.prodNumber);
    query.bindValue(":seasonnumber", episode.season);
    query.bindValue(":episodeurl", episode.link.toString());
    query.bindValue(":date", episode.airDate);
    query.bindValue(":isspecial", episode.isSpecial);
    
    bool status;
    status = query.exec();
    if (!status) {
        qCritical() << query.lastQuery() << "\n" << query.lastError();
        return false;
    }
    return true;
} // saveEpisode()

bool DbInterface::deleteShow(const int &showId)
{
    qDebug() << Q_FUNC_INFO;
    
    QSqlDatabase db = QSqlDatabase::database(DBCONNECTION);
    QSqlQuery query(db);
    bool status = true;

    // Remove Show
    query.prepare("DELETE FROM T_Shows WHERE idT_Shows = :showid");
    query.bindValue(":showid", showId);
    qDebug() << query.lastQuery();
    if (!query.exec()) {
        qCritical() << query.lastQuery() << "\n" << query.lastError();
        status = false;
    }

    // Remove AKAs
    query.prepare("DELETE FROM T_Akas WHERE T_Akas_Shows_id = :showid");
    query.bindValue(":showid", showId);
    qDebug() << query.lastQuery();
    if (!query.exec()) {
        qCritical() << query.lastQuery() << "\n" << query.lastError();
        status = false;
    }

    // Remove Networks
    query.prepare("DELETE FROM T_Networks WHERE T_Networks_Shows_id = :showid");
    query.bindValue(":showid", showId);
    qDebug() << query.lastQuery();
    if (!query.exec()) {
        qCritical() << query.lastQuery() << "\n" << query.lastError();
        status = false;
    }

    // Remove Episode List
    if (!deleteEpisodes(showId)) {
        status = false;
    }
    
    return status;
} // deleteShow()

bool DbInterface::deleteEpisodes(const int &showId)
{
    qDebug() << Q_FUNC_INFO;
    
    QSqlDatabase db = QSqlDatabase::database(DBCONNECTION);
    QSqlQuery query(db);
    bool status = true;

    query.prepare("DELETE FROM T_Episodes WHERE Shows_id = :showid");
    query.bindValue(":showid", showId);
    if (!query.exec()) {
        qCritical() << query.lastQuery() << "\n" << query.lastError();
        status = false;
    }

    return status;
} // deleteEpisodes

bool DbInterface::updateShow(const NextShows::ShowInfos_t &showInfo)
{
    //TODO merge this method with saveShow()
    qDebug() << Q_FUNC_INFO;

    QSqlDatabase db = QSqlDatabase::database(DBCONNECTION);
    QSqlQuery query(db);

    bool status = true;

    query.prepare("UPDATE T_Shows SET "
                    "ShowName = :showname, "
                    "ShowUrl = :showurl, "
                    "Country = :country, "
                    "Started = :started, "
// FIXME: Missing from feed.
//                    "Ended = :ended, "
// FIXME: Missing from feed.
//                    "SeasonsNbr = :seasonsnbr, "
                    "Status = :status, "
                    "Classification = :classification, "
                    "Genres = :genres, "
                    "EndedFlag = :endedflag, "
                    "Runtime = :runtime, "
                    "Airtime = :airtime, "
                    "Airday = :airday, "
                    "Timezone = :timezone, "
                    "Timestamp = :timestamp "
                    "WHERE idt_Shows = :show_id");
    query.bindValue(":showname", showInfo.name);
    query.bindValue(":showurl", showInfo.link.toString());
    query.bindValue(":country", showInfo.country);
    query.bindValue(":started", showInfo.started);
// FIXME: Missing from feed.
//    query.bindValue(":ended", showInfo.ended);
// FIXME: Missing from feed.
//    query.bindValue(":seasonsnbr", showInfo.seasons);
    query.bindValue(":status", showInfo.status);
    query.bindValue(":classification", showInfo.classification);
    query.bindValue(":genres", showInfo.genres.join(","));
    query.bindValue(":endedflag", showInfo.endedFlag);
    query.bindValue(":runtime", showInfo.runtime);
    query.bindValue(":airtime", showInfo.airtime);
    query.bindValue(":airday", showInfo.airday);
    query.bindValue(":timezone", showInfo.timezone);
    query.bindValue(":timestamp", QDateTime::currentDateTime().toTime_t());
    query.bindValue(":show_id", showInfo.showid);

    if (!query.exec()) {
        qCritical() << query.lastQuery() << "\n" << query.lastError();
        status = false;
    }

    return status;
} // updateShow()

// EOF - vim:ts=4:sw=4:et:
