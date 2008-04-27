/*
 *   Copyright (C) 2008 Gilles CHAUVIN <gcnweb@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License either version 2, or
 *   (at your option) any later version as published by the Free Software
 *   Foundation.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */


#include "nextshowsengine.h"

#include <QtNetwork/QHttp>


class NextShowsEngine::Private
{
public:
    Private()
    {
        http = new QHttp();
    };
    ~Private() {};

    QHttp *http;
}; // Private()


NextShowsEngine::NextShowsEngine(QObject *parent, const QVariantList &args)
    : Plasma::DataEngine(parent, args)
    , d(new Private())
{
    Q_UNUSED(args);
}; // ctor()


NextShowsEngine::~NextShowsEngine()
{
    delete d;
}; // dtor()


bool NextShowsEngine::sourceRequestEvent(const QString &request)
{
    if ( request.toLower().startsWith("search:") ) {
        kDebug() << "Search";
//        setData(request, Plasma::DataEngine::Data());
        setData(request, "key1", QVariant("value"));
        setData(request, "key2", QVariant("value"));
        setData(request, "key3", QVariant("value"));
    } else if ( request.toLower().startsWith("eplist:") ) {
        kDebug() << "Episode List";
        setData(request, Plasma::DataEngine::Data());
    } else {
        // Quick usage help
        setData(request,
                "Usage",
                QVariant("search:showname -> search for a show\neplist:showid -> get episode list for the given show ID"));
        return false;
    }

    return true;
}; // sourceRequestEvent()


#include "nextshowsengine.moc"
