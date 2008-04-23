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

//#include "plasma/datacontainer.h"


NextShowsEngine::NextShowsEngine(QObject *parent, const QVariantList &args)
    : Plasma::DataEngine(parent, args)
{
    Q_UNUSED(args)
    kDebug() << "ctor() called";
}

NextShowsEngine::~NextShowsEngine()
{
    kDebug() << "dtor() called";
}

void NextShowsEngine::init()
{
    kDebug() << "init() called";
}

bool NextShowsEngine::sourceRequested(const QString &request)
{
    kDebug() << "Request:" << request;
    //setData(request, "key", QVariant("val"));
    setData(request, Data());
    return true;
}


#include "nextshowsengine.moc"
