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


#ifndef __NEXTSHOWS_H__
#define __NEXTSHOWS_H__


/* VERSION INFOS ------------------------------------------------------------*/
#define _TEXT(x) #x
#define TEXT(x) _TEXT(x)

// nextShows version
#define NEXTSHOWS_RELEASE 2.99.0
#ifdef NS_SVNVERSION
    #define NEXTSHOWS_VERSION TEXT(NS_SVNVERSION) "-svn"
#else
    #define NEXTSHOWS_VERSION TEXT(NEXTSHOWS_RELEASE)
#endif

// nextShows database version
#define DB_RELEASE 0.2

// Build date / time
#define NEXTSHOWS_BUILDDATE __DATE__ " - " __TIME__

// GCC version
#define GCC_VERSION TEXT(__GNUC__.__GNUC_MINOR__.__GNUC_PATCHLEVEL__)
/* /VERSION INFOS -----------------------------------------------------------*/


#include <QtCore/QDate>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QUrl>

namespace NextShows
{

typedef QMap<QString, QString> StringMap;

struct ShowInfos_t {
    int         showid;         // Show unique ID [TvRage]
    QString     name;           // Show name [TvRage]
    QUrl        link;           // Show URL [TvRage]
    QString     country;        // Show country [TvRage]
    int         started;        // Show started year [TvRage]
    int         ended;          // Show ended year [TvRage]
    int         seasons;        // Total number of seasons [TvRage]
    QString     status;         // Show status [TvRage]
    QString     classification; // Show classification [TvRage]
    QStringList genres;         // Show genres [TvRage]
    bool        endedFlag;      // Show Ended flag [Internal]
    int         runtime;        // Show runtime [Tvrage]
    StringMap   network;        // Show network [TvRage]
    QTime       airtime;        // Show airtime [TvRage]
    QString     airday;         // Show airday [TvRage]
    QString     timezone;       // Show timezone [TvRage]
    StringMap   akas;           // Show also-known-as [TvRage]

    // Default values
    ShowInfos_t() {
        showid = -1;
        name = QString();
        link = QUrl();
        country = QString();
        started = -1;
        ended = -1;
        seasons = -1;
        status = QString();
        classification = QString();
        genres = QStringList();
        endedFlag = false;
        runtime = -1;
        network = StringMap();
        airtime = QTime();
        airday = QString();
        timezone = QString();
        akas = StringMap();
    };
};
typedef QList<ShowInfos_t> ShowInfosList;

struct EpisodeList_t {
    int         season;         // Season
    int         episodeCount;   // Episode number since the show has started
    int         episodeNumber;  // Episode number within the season
    QString     prodNumber;     // Production "number" (can contain letters)
    QDate       airDate;        // Episode airdate
    QUrl        link;           // Episode URL
    QString     title;          // Episode title
    bool        isSpecial;      // Flag for special (off-season) episodes

    // Default values
    EpisodeList_t() {
        season = -1;
        episodeCount = -1;
        episodeNumber = -1;
        prodNumber = QString();
        airDate = QDate();
        link = QUrl();
        title = QString();
        isSpecial = false;
    };
};
typedef QList<EpisodeList_t> EpisodeListList;

}; // namespace NextShows


#endif // __NEXTSHOWS_H__
