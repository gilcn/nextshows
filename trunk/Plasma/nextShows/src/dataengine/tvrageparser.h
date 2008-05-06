/*
 *   Copyright 2008 Gilles CHAUVIN <gcnweb@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as
 *   published by the Free Software Foundation; either version 2,
 *   or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */


#ifndef __TVRAGEPARSER_H__
#define __TVRAGEPARSER_H__

#include <QtCore/QList>
#include <QtCore/QHash>
#include <QtCore/QString>
#include <QtCore/QVariant>

class QByteArray;
class QDomNode;


class TvRageParser
{
public:
    typedef QMap<QString, QVariant> showInfos;
    typedef QMap<QString, QVariant> episodeInfos;

    TvRageParser(){};
    ~TvRageParser(){};

    static QList<showInfos> parseSearchResults(const QByteArray &feed);
    static QList<episodeInfos> parseEpisodeList(const QByteArray &feed);

private:
    static showInfos parseSearchResults_Show(const QDomNode &node);
};


#endif // __TVRAGEPARSER_H__
