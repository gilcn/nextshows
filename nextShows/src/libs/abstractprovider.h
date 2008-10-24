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

#ifndef __ABSTRACTPROVIDER_H__
#define __ABSTRACTPROVIDER_H__


// QtCore
#include <QtCore/QUrl>
#include <QtCore/QVariant>


class AbstractProvider : public QObject
{
    Q_OBJECT

public:
    AbstractProvider(QObject *parent = 0);
    ~AbstractProvider();

    QVariant searchShow(const QString &);
    QVariant getEpisodeList(const QString &);

protected:
    enum UrlTypes {
        SearchShowUrl,
        EpisodeListUrl
    };

    virtual QVariant parseSearchResults(const QByteArray &) = 0;
    virtual QVariant parseEpisodeList(const QByteArray &) = 0;

    void setBaseUrl(const UrlTypes &, const QUrl &);

private:
    QMap<UrlTypes, QUrl> m_urls;
};


#endif // __ABSTRACTPROVIDER_H__


// EOF - vim:ts=4:sw=4:et:
