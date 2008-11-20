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

#ifndef __TVRAGEPARSER_H__
#define __TVRAGEPARSER_H__


// Own
#include "nextshows.h"
// QtCore
#include <QtCore/QStringList>
// Forward declarations
class QDomElement;
class QDomNode;


class TvRageParser
{
public:
    TvRageParser() {}

    // Parser for http://www.tvrage.com/feeds/search.php?show=SHOWNAME
    static NextShows::ShowInfosList parseSearchResults(const QByteArray &data);
    // Parser for http://www.tvrage.com/feeds/showinfo.php?sid=SHOWID
    static NextShows::ShowInfos_t parseShowInfo(const QByteArray &data);
    // Parser for http://www.tvrage.com/feeds/episode_list.php?sid=SHOWID
    static NextShows::EpisodeListList parseEpisodeList(const QByteArray &data);

private:
    static NextShows::ShowInfos_t parseSearchResults_Show(const QDomNode &node);

    static QStringList parseTag_Genres(const QDomElement &element);

    static const QStringList m_endedShowStatusKeywords;
};


#endif // __TVRAGEPARSER_H__


// EOF - vim:ts=4:sw=4:et:
