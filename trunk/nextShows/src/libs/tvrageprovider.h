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

#ifndef __TVRAGEPROVIDER_H__
#define __TVRAGEPROVIDER_H__


// Own
#include "abstractprovider.h"
// Forward declarations
class QDomNode;


class TvRageProvider : public AbstractProvider
{
    Q_OBJECT

public:
    TvRageProvider(QObject *parent = 0);
    ~TvRageProvider();

protected:
    QUrl urlForRequest(const AbstractProvider::RequestType &, const QString &);
    QList<AbstractProvider::SearchResults_t> parseSearchResults(const QByteArray &);
    QVariant parseEpisodeList(const QByteArray &);

private:
    AbstractProvider::SearchResults_t parseSearchResultsTag_Show(const QDomNode &);
};


#endif // __TVRAGEPROVIDER_H__


// EOF - vim:ts=4:sw=4:et:
