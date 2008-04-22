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

#include "plasma/datacontainer.h"

#include <QtCore/QDebug>


NextShowsEngine::NextShowsEngine(QObject *parent, const QVariantList &args)
    : Plasma::DataEngine(parent, args)
{
    Q_UNUSED(parent)
    Q_UNUSED(args)
    qDebug() << args;
}

NextShowsEngine::~NextShowsEngine()
{
}

QStringList NextShowsEngine::sources() const
{
   QStringList list;

   list << QLatin1String("Test1");
   list << QLatin1String("Test2");
   list << QLatin1String("Test3");

   return list;
}

bool NextShowsEngine::sourceRequested(const QString &name)
{
    kDebug() << name;

    return true;
}

bool NextShowsEngine::updateSource(const QString &source)
{
    kDebug() << source;

    return true;
}

#include "nextshowsengine.moc"
