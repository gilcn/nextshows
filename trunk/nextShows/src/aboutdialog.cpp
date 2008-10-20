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
#include "aboutdialog.h"
#include "version.h"

// QtCore
#include <QtCore/QDebug>


/*
** public:
*/
AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent, Qt::Dialog)
{
    // Define some default behavior
    QDialog::setModal(true);

    ui.setupUi(this);

    connect(ui.btnClose, SIGNAL(clicked()), this, SLOT(close()));

    // Fill labels with their relevant values
    QString version(ui.lblNextShowsVersion->text());
    version = version.replace("%NSVER%", QLatin1String(NEXTSHOWS_VERSION));
    ui.lblNextShowsVersion->setText(version);

    QString buildInfos(ui.lblBuildInfos->text());
    buildInfos = buildInfos.replace("%BUILD%", QLatin1String(NEXTSHOWS_BUILDDATE));
    buildInfos = buildInfos.replace("%GCCVER%", QLatin1String(GCC_VERSION));
    QString versionCompiled(QT_VERSION_STR);
    QString versionRunning(qVersion());
    if (versionCompiled != versionRunning) {
        buildInfos = buildInfos.replace("%QTVER%", versionCompiled+" / "+versionRunning);
    } else {
        buildInfos = buildInfos.replace("%QTVER%", QLatin1String(QT_VERSION_STR));
    }
    ui.lblBuildInfos->setText(buildInfos);
} // ctor()

AboutDialog::~AboutDialog()
{
} // dtor()


// EOF - vim:ts=4:sw=4:et:
