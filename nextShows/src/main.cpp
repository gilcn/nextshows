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
#include "mainwindow.h"
#include "nextshows.h"
// QtGui
#include <QtGui/QApplication>
#include <QtGui/QMessageBox>
// Sys
#include <stdio.h>
#include <stdlib.h>


void msgHandler(QtMsgType type, const char *msg)
{
    switch(type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s\n", msg);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s\n", msg);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s\n", msg);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s\n", msg);
        abort();
    }
}

int main(int argc, char **argv)
{
    QT_REQUIRE_VERSION(argc, argv, "4.4.0")

    qInstallMsgHandler(msgHandler);

    QApplication app(argc, argv);
    app.setApplicationName("nextShows");
    app.setApplicationVersion(NEXTSHOWS_VERSION);
    app.setOrganizationName("nextShows");
    app.setOrganizationDomain("nextshows.googlecode.com");

    MainWindow window;
    window.show();
    return app.exec();
} // main()


// EOF - vim:ts=4:sw=4:et:
