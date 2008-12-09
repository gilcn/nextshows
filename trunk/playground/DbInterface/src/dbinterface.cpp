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
DbInterface& DbInterface::instance()
{
    static DbInterface DbInterfaceInstance;
    return DbInterfaceInstance;
} // instance()

bool DbInterface::isInitialized()
{
    return m_databaseInitialized;
} // isInitialized()

void DbInterface::saveUserShows(const NextShows::ShowInfosList &shows)
{
    qDebug() << Q_FUNC_INFO;
    
    QSqlDatabase db = QSqlDatabase::database(DBCONNECTION);
    
    // First, select all id in db
    QList<int> dbid;
    QSqlQuery query(db);
    query.exec("SELECT idT_Shows FROM T_Shows");
    while (query.next()) {
        dbid << query.value(0).toInt();
    }

    QList<int> usrid;
    NextShows::ShowInfosList::ConstIterator it;
    for (it = shows.begin(); it != shows.end(); ++it) {
        NextShows::ShowInfos_t show = *it;
        usrid << show.showid;
        if(!dbid.contains(show.showid)) { // This show is a new show, Add IT !
            saveShow(show);
            qDebug() << "Add show : " << QString::number(show.showid);
        }
    }
    int idshow;
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
        show.genres = query.value(9).toString().split(",");
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

void DbInterface::saveUserEpisodes(const NextShows::ShowInfos_t &showInfo, const NextShows::EpisodeListList &episodes)
{
    qDebug() << Q_FUNC_INFO;
    
    QSqlDatabase db = QSqlDatabase::database(DBCONNECTION);
    
    // Delete all episodes for this show
    deleteEpisode(showInfo.showid);
    // Save episodes for this show
    for (int i = 0; i < episodes.size(); ++i) {
        saveEpisode(episodes.at(i),showInfo.showid);
    }
    // Update information of this show
    updateShow(showInfo);
    
    
} // saveUserEpisodes()

QSqlTableModel* DbInterface::readEpisodes() const
{
    qDebug() << Q_FUNC_INFO;
    
    QSqlDatabase db = QSqlDatabase::database(DBCONNECTION);
    
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("T_Shows");
    //model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    if (!model->select())
    	qDebug() << "Error setTable !!";
    model->removeColumn(0); // don't show the ID
    /*model->setHeaderData(0, Qt::Horizontal, tr("Name"));
    model->setHeaderData(1, Qt::Horizontal, tr("Salary"));
    */
    return model;

} // readEpisode()


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
    // Verifie Database version
    QSqlQuery query(db);
    bool status;
    status = query.exec("SELECT version FROM T_Version");
    if (!query.first()){
        qCritical() << "Database version in T_version table is missing ! ";
        return false;
    }
    if (DB_RELEASE != query.value(0).toDouble()){
        qCritical() << "Database version mismatch ! actual : '" << query.value(0).toDouble() << "', needed : '" << DB_RELEASE <<"'";
        return false;
    }
    if (!status) {
        qCritical() << query.lastError();
        return false;
    }

    return true;
} // init()

bool DbInterface::createTables()
{
    qDebug() << Q_FUNC_INFO;

    QSqlDatabase db = QSqlDatabase::database(DBCONNECTION);
    
    bool status;
    QSqlQuery query(db);

    // T_Shows table
    status = query.exec("CREATE TABLE T_Shows ("
            "idT_Shows INTEGER PRIMARY KEY, "
            "ShowName VARCHAR(30), "
            "ShowUrl VARCHAR(256), "
            "Country VARCHAR(15), "
            "Started INTEGER, "
            "Ended INTEGER, "
            "SeasonsNbr INTEGER, "
            "Status VARCHAR(30), "
            "Classification VARCHAR(30), "
            "Genres VARCHAR(256), "
            "EndedFlag BOOL, "
            "Runtime INTEGER, "
            "Airtime TIME, "
            "Airday VARCHAR(9), "
            "Timezone VARCHAR(15), "
            "Timestamp INTEGER)");
    if (!status) {
        qCritical() << query.lastError();
        return false;
    }

    // T_Episodes table
    status = query.exec("CREATE TABLE T_Episodes ("
            "idT_Episodes INTEGER PRIMARY KEY, "
            "Shows_id INTEGER, "
            "EpisodeName VARCHAR(50), "
            "EpisodeCount INTEGER, "
            "EpisodeNumber INTEGER, "
            "ProdNumber VARCHAR(10), "
            "SeasonNumber INTEGER, "
            "EpisodeUrl VARCHAR(256), "
            "Date DATE, "
            "IsSpecial BOOL)");
    if (!status) {
        qCritical() << query.lastError();
        return false;
    }
    
    // T_Akas table
    status = query.exec("CREATE TABLE T_Akas ("
            "T_Akas_Shows_id INTEGER, "
            "Country VARCHAR(3), "
            "Name VARCHAR(30))");
    if (!status) {
        qCritical() << query.lastError();
        return false;
    }
    
    // T_Networks
    status = query.exec("CREATE TABLE T_Networks ("
            "T_Networks_Shows_id INTEGER, "
            "Country VARCHAR(3), "
            "Name VARCHAR(30))");
    if (!status) {
        qCritical() << query.lastError();
        return false;
    }
    
    // T_Version table
    status = query.exec("CREATE TABLE T_Version (Version VARCHAR(5))");
    if (!status) {
        qCritical() << query.lastError();
        return false;
    }
    status = query.exec("INSERT INTO T_Version (Version) VALUES ('0.2')");


    return true;
} // createTables()

bool DbInterface::saveShow(const NextShows::ShowInfos_t &show)
{
    qDebug() << Q_FUNC_INFO;
    
    QSqlDatabase db = QSqlDatabase::database(DBCONNECTION);
    bool status;
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
    status = query.exec();
    
    // retrieve the last ID insert
    int lastid = query.lastInsertId().toInt();
    // Insert T_Akas
    QMapIterator<QString, QString> i(show.akas);
    while (i.hasNext()) {
        i.next();
        qDebug() << i.key() << ": " << i.value();
        query.prepare("INSERT INTO T_Akas (T_Akas_Shows_id, Country, Name) "
                        "VALUES (:showid, :country, :name)");
        query.bindValue(":showid", lastid);
        query.bindValue(":country", i.key());
        query.bindValue(":name", i.value());
        status = query.exec();
    }
    // Insert T_Network
    QMapIterator<QString, QString> y(show.network);
    while (y.hasNext()) {
        y.next();
        qDebug() << y.key() << ": " << y.value();
        query.prepare("INSERT INTO T_Networks (T_Networks_Shows_id, Country, Name) "
                        "VALUES (:showid, :country, :name)");
        query.bindValue(":showid", lastid);
        query.bindValue(":country", y.key());
        query.bindValue(":name", y.value());
        status = query.exec();
    }
    
    // If a SQL request doesn't work return FALSE
    if (!status) {
        qCritical() << query.lastError();
        return false;
    }
    // If all SQL request as ok return TRUE
    return true;
} // saveShow()

bool DbInterface::saveEpisode(const NextShows::EpisodeList_t &episode, const int &idshow)
{
    qDebug() << Q_FUNC_INFO;
    
    QSqlDatabase db = QSqlDatabase::database(DBCONNECTION);
    
    QSqlQuery query(db);
    
    query.prepare("INSERT INTO T_episodes (Shows_id, EpisodeName, EpisodeCount, EpisodeNumber, ProdNumber, SeasonNumber, EpisodeUrl, Date, IsSpecial) "
                    "VALUES (:show_id, :episodename, :episodecount, :episodenumber, :prodnumber, :seasonnumber, :episodeurl, :date, :isspecial)");
    query.bindValue(":show_id",idshow);
    query.bindValue(":episodename",episode.title);
    query.bindValue(":episodecount",episode.episodeCount);
    query.bindValue(":episodenumber",episode.episodeNumber);
    query.bindValue(":prodnumber",episode.prodNumber);
    query.bindValue(":seasonnumber",episode.season);
    query.bindValue(":episodeurl",episode.link);
    query.bindValue(":date",episode.airDate);
    query.bindValue(":isspecial",episode.isSpecial);
    
    bool status;
    status = query.exec();
    if (!status) {
        qCritical() << query.lastError();
        return false;
    }
    return true;
} // saveEpisode()

bool DbInterface::deleteShow(const int &id)
{
    qDebug() << Q_FUNC_INFO;
    
    QSqlDatabase db = QSqlDatabase::database(DBCONNECTION);
    bool status;
    QSqlQuery query(db);
    query.prepare("DELETE FROM T_Shows WHERE idT_Shows = :idshow");
    query.bindValue(":idshow", id);
    status = query.exec();

    query.prepare("DELETE FROM T_Akas WHERE T_Akas_Shows_id = :idshow");
    query.bindValue(":idshow", id);
    status = query.exec();

    query.prepare("DELETE FROM T_Networks WHERE T_Networks_Shows_id = :idshow");
    query.bindValue(":idshow", id);
    status = query.exec();
    
    if (!status) {
        qCritical() << query.lastError();
        return false;
    }
    return true;
} // deleteShow()

bool DbInterface::deleteEpisode(const int &idshow)
{
    qDebug() << Q_FUNC_INFO;
    
    QSqlDatabase db = QSqlDatabase::database(DBCONNECTION);
    
    QSqlQuery query(db);
    query.prepare("DELETE FROM T_episodes WHERE Shows_id = :idshow");
    query.bindValue(":idshow", idshow);
    bool status;
    status = query.exec();
    if (!status) {
        qCritical() << query.lastError();
        return false;
    }
    return true;
} // deleteEpisode

bool DbInterface::updateShow(const NextShows::ShowInfos_t &showInfo)
{
    //TODO merge this method with saveShow()
    qDebug() << Q_FUNC_INFO;
    
    QSqlDatabase db = QSqlDatabase::database(DBCONNECTION);
    
    QSqlQuery query(db);
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
    query.bindValue(":genres", showInfo.genres.join(", "));
    query.bindValue(":endedflag", showInfo.endedFlag);
    query.bindValue(":runtime", showInfo.runtime);
    query.bindValue(":airtime", showInfo.airtime);
    query.bindValue(":airday", showInfo.airday);
    query.bindValue(":timezone", showInfo.timezone);
    query.bindValue(":timestamp", QDateTime::currentDateTime().toTime_t());
    query.bindValue(":show_id", showInfo.showid);
    qDebug() << showInfo.link;
    bool status;
    status = query.exec();
    qDebug() << query.executedQuery();
    if (!status) {
        qCritical() << query.lastError();
        return false;
    }
    return true;
}

// EOF - vim:ts=4:sw=4:et:
