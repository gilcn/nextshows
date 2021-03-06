/*
** Copyright (C) 2008 Gilles CHAUVIN <gcnweb@gmail.com>
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
#include "nextshowsapplet.h"

// Plasma
#include <Plasma/Label>

// Qt
#include <QtCore/QDir>
#include <QtGui/QGraphicsLinearLayout>


class NextShowsApplet::Private
{
public:
    Private() {}
    ~Private() {}

    QGraphicsLinearLayout *layout;
    Plasma::Label         *image;
}; // Private()


NextShowsApplet::NextShowsApplet(QObject *parent, const QVariantList &args)
    : Plasma::Applet(parent, args)
    , d(new Private)
{
} // ctor()


NextShowsApplet::~NextShowsApplet()
{
    delete d;
} // dtor()


void NextShowsApplet::init()
{
    d->layout = new QGraphicsLinearLayout(Qt::Horizontal, this);

    d->image = new Plasma::Label(this);
    d->image->setImage(QDir::currentPath()+"/nextShows_logo.png");
    d->layout->insertStretch(0);
    d->layout->insertItem(1, d->image);
    d->layout->insertStretch(2);

    setLayout(d->layout);
} // init()


void NextShowsApplet::constraintsEvent(Plasma::Constraints constraints)
{
    kDebug() << "constraintsEvent()" << constraints;
} // constraintsEvent()


#include "nextshowsapplet.moc"
