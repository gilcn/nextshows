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


// Own
#include "tvrageparser.h"
#include "nextshows.h"
// Qt
#include <QtCore>
// Sys
#include <iostream>

using namespace std;
using namespace NextShows;


int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    if (app.arguments().count() != 2) {
        cout << "Usage: " << qPrintable(app.arguments()[0]) << " file.xml" << endl;
        return EXIT_FAILURE;
    }

    QFile file(app.arguments()[1]);
    if (!file.open(QIODevice::ReadOnly)) {
        qFatal("Cannot open %s for reading!", qPrintable(app.arguments()[1]));
    }

    QByteArray data = file.readAll();
    file.close();

    EpisodeListList episodeList = TvRageParser::parseEpisodeList(data);

    qDebug() << "Episode count:" << episodeList.count();

    foreach (EpisodeList_t ep, episodeList) {
        qDebug() << "season:" << ep.season;
        qDebug() << "episodeCount:" << ep.episodeCount;
        qDebug() << "episodeNumber:" << ep.episodeNumber;
        qDebug() << "prodNumber:" << ep.prodNumber;
        qDebug() << "airDate:" << ep.airDate;
        qDebug() << "link:" << ep.link;
        qDebug() << "title:" << ep.title;
        qDebug() << "isSpecial" << ep.isSpecial;
        qDebug() << "------------------------------------------------------------------------------";
    }

    return EXIT_SUCCESS;
}
