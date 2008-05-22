/*
** Copyright (C) 2008 Gilles CHAUVIN <gcnweb@gmail.com>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as
** published by the Free Software Foundation; either version 2,
** or (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details
**
** You should have received a copy of the GNU Library General Public
** License along with this program; if not, write to the
** Free Software Foundation, Inc.,
** 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef __NEXTSHOWS_DATAENGINE_H__
#define __NEXTSHOWS_DATAENGINE_H__

#include "plasma/dataengine.h"


class NextShowsEngine : public Plasma::DataEngine
{
    Q_OBJECT

public:
    enum RequestType {
        Search      = 0x0,
        EpisodeList = 0x1
    };

    NextShowsEngine(QObject *parent, const QVariantList &args);
    ~NextShowsEngine();

protected:
    bool sourceRequestEvent(const QString &request);

private Q_SLOTS:
    void httpRequestFinished(const int reqId, const bool error);

private:
    class Private;
    Private * const d;
};


K_EXPORT_PLASMA_DATAENGINE(nextshows, NextShowsEngine)


#endif // __NEXTSHOWS_DATAENGINE_H__
