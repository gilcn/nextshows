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
class QDomNode;


class TvRageParser
{
public:
    TvRageParser() {}

    static QList<NextShows::ShowInfos_t> parseSearchResults(const QByteArray &data);

private:
    static NextShows::ShowInfos_t parseSearchResults_Show(const QDomNode &node);

    static const QStringList m_endedShowStatusKeywords;
};


#endif // __TVRAGEPARSER_H__


// EOF - vim:ts=4:sw=4:et:
