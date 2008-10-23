/*
 *   Copyright (C) 2008 Gilles CHAUVIN <gcnweb+nextshows@gmail.com>
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


// QtCore
#include <QtCore/QList>
#include <QtCore/QString>

// Forward declarations
class QByteArray;
class QDomNode;


class TvRageParser
{
public:
    struct show_t {
        uint    showid;
        QString name;
        QString link;
        QString country;
        uint    started;
        uint    ended;
        uint    seasons;
        QString classification;
        QString genres;
    };

    TvRageParser(){};
    ~TvRageParser(){};

    static QList<show_t> parseSearchResults(const QByteArray &content);

private:
    static show_t parseShow(const QDomNode &node);
};


#endif // __TVRAGEPARSER_H__


// EOF - vim:ts=4:sw=4:et:
