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


} // namespace NextShows


#endif // __NEXTSHOWS_H__
