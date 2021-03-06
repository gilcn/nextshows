/*
** Copyright (C) 2008 Gilles CHAUVIN <gcnweb+kde@gmail.com>
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

#ifndef __LAYOUTTEST_APPLET_H__
#define __LAYOUTTEST_APPLET_H__


// Plasma
#include <Plasma/Applet>
#include <Plasma/Label>
#include <Plasma/LineEdit>

// KDE
#include <KDE/Solid/Networking>

// Qt
#include <QtGui/QGraphicsGridLayout>
#include <QtGui/QGraphicsLinearLayout>


class LayoutTestApplet : public Plasma::Applet
{
    Q_OBJECT

public:
    LayoutTestApplet(QObject *parent, const QVariantList &args);
    ~LayoutTestApplet();


protected:
    void init();
    void feedContent();


private:
    int m_lines;

    QGraphicsLinearLayout *m_layoutMain;
    QGraphicsGridLayout   *m_layoutControls;
    QGraphicsGridLayout   *m_layoutContent;

    Plasma::LineEdit *m_ledit;
    Plasma::Label    *m_netStatus;

    void displayNetworkStatus(const Solid::Networking::Status &status);

private Q_SLOTS:
    void refresh();

    void networkStatusChanged(const Solid::Networking::Status &status);
};


K_EXPORT_PLASMA_APPLET(layouttestapplet, LayoutTestApplet)


#endif // __LAYOUTTEST_APPLET_H__
