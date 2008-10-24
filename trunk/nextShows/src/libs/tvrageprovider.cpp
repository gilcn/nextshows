/*
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
#include "tvrageprovider.h"


/*
** public:
*/
TvRageProvider::TvRageProvider(QObject *parent)
    : AbstractProvider(parent)
{
    // "Search Show" base URL
    setBaseUrl(AbstractProvider::SearchShowUrl,
               QUrl("http://www.tvrage.com/feeds/search.php?show=", QUrl::StrictMode));
    // "Episode List" base URL
    setBaseUrl(AbstractProvider::EpisodeListUrl,
               QUrl("http://www.tvrage.com/feeds/episode_list.php?sid=", QUrl::StrictMode));
} // ctor()

TvRageProvider::~TvRageProvider()
{
} // dtor()


/*
** protected:
*/
QVariant TvRageProvider::parseSearchResults(const QByteArray &/*data*/)
{
    return QVariant();
} // parseSearchResults()

QVariant TvRageProvider::parseEpisodeList(const QByteArray &/*data*/)
{
    return QVariant();
} // parseEpisodeList()


// EOF - vim:ts=4:sw=4:et:
