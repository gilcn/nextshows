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

// Build date / time
#define NEXTSHOWS_BUILDDATE __DATE__ " - " __TIME__

// GCC version
#define GCC_VERSION TEXT(__GNUC__.__GNUC_MINOR__.__GNUC_PATCHLEVEL__)
/* /VERSION INFOS -----------------------------------------------------------*/


#include <QtCore/QDate>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QUrl>

namespace NextShows
{

struct ShowInfos_t {
    uint        showid;         // Show unique ID [TvRage]
    QString     name;           // Show name [TvRage]
    QUrl        link;           // Show URL [TvRage]
    QString     country;        // Show country [TvRage]
    uint        started;        // Show started year [TvRage]
    uint        ended;          // Show ended year [TvRage]
    uint        seasons;        // Total number of seasons [TvRage]
    QString     status;         // Show status [TvRage]
    QString     classification; // Show classification [TvRage]
    QStringList genres;         // Show genres [TvRage]
    bool        endedFlag;      // Show Ended flag [Internal]
};
typedef QList<ShowInfos_t> ShowInfosList;

struct EpisodeList_t {
    uint        season;         // Season
    uint        episodeCount;   // Episode number since the show has started
    uint        episodeNumber;  // Episode number within the season
    QString     prodNumber;     // Production "number" (can contain letters)
    QDate       airDate;        // Episode airdate
    QUrl        link;           // Episode URL
    QString     title;          // Episode title
    bool        isSpecial;      // Flag for special (off-season) episodes
};
typedef QList<EpisodeList_t> EpisodeListList;

} // namespace NextShows


#endif // __NEXTSHOWS_H__
