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
#include "dialogs/about.h"
#include "version.h"

// QtCore
#include <QtCore/QDebug>

namespace Dialogs
{

/*
** public:
*/
About::About(QWidget *parent)
    : QDialog(parent, Qt::Dialog)
{
    // Define some default behavior
    QDialog::setModal(true);
    QWidget::setAttribute(Qt::WA_DeleteOnClose);

    ui.setupUi(this);

    connect(ui.btnBox, SIGNAL(accepted()), this, SLOT(close()));

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

    // Scrolling credits
    ui.gvCreditScroller->addCreditSection("Credits", 15);
    ui.gvCreditScroller->addCredit("FR", "Gilles Chauvin", "gcnweb@gmail.com", "Author, main developper");
    ui.gvCreditScroller->addCredit("FR", "Emmanuel Hamelet", "kh.starlifter@gmail.com", "Contributor");
    ui.gvCreditScroller->addCreditSection("Releases prior to v3.0.0<br />(SuperKaramba widget)");
    ui.gvCreditScroller->addCredit("FR", "Gilles Chauvin", "gcnweb@gmail.com","Author, main developper");
    ui.gvCreditScroller->addCredit("FR", "Emmanuel Hamelet", "kh.starlifter@gmail.com","Ideas, testing, bug-hunting");
    ui.gvCreditScroller->addCredit("ES", "Alexandre Vázquez", "", "Testing, bug-hunting");
    ui.gvCreditScroller->addCredit("SE", "ge5239", "", "Ideas, testing, bug-hunting");
    ui.gvCreditScroller->addCredit("FR", "Joachim Ionoff", "", "Ideas, testing, bug-hunting");
    ui.gvCreditScroller->addCreditSection("Special thanks to");
    ui.gvCreditScroller->addCredit("FR", "Jean-Baptiste Sannier", "http://jsannier.org/", "Qt help, tips & tricks");
    ui.gvCreditScroller->addCredit("US", "Sebrioth", "http://www.tvrage.com/", "XML feeds providing");

    ui.gvCreditScroller->startScrolling();
} // ctor()

About::~About()
{
    qDebug() << Q_FUNC_INFO;
} // dtor()

} // namespace Dialogs


// EOF - vim:ts=4:sw=4:et:
