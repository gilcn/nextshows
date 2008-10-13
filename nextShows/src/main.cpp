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
#include "nextshowsmain.h"

// KDE
#include <KDE/KAboutData>
#include <KDE/KCmdLineArgs>
#include <KDE/KUniqueApplication>


static const char description[] = I18N_NOOP("Some description here...");
static const char version[] = "2.99.0";


int main (int argc, char **argv)
{
    KAboutData aboutData("nextShows", 0, ki18n("nextShows"), version,
                         ki18n(description), KAboutData::License_GPL_V2,
                         ki18n("(c)2006-2008, Gilles CHAUVIN"), ki18n("N/A"),
                         "http://nextshows.googlecode.com/", "http://code.google.com/p/nextshows/issues/list");
    aboutData.addAuthor(ki18n("Gilles CHAUVIN"),
                        ki18n("Author and maintainer"),
                        "gcnweb+nextshows@gmail.com");

    KCmdLineArgs::init(argc, argv, &aboutData);

    // REMOVEME
    if (!KUniqueApplication::start()) {
        fprintf(stderr, "nextShows is already running!\n");
        return 0;
    }

    //KUniqueApplication app(true, true);
    KUniqueApplication app;
    NextShowsMain *window = new NextShowsMain();
    window->show();
    return app.exec();
}
