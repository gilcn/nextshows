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

#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__


// Own
#include "ui_mainwindow.h"
#include "systrayicon.h"
#include "dialogs/about.h"
#include "dialogs/settings.h"
#include "libs/dataprovider.h"
// QtGui
#include <QtGui/QDialog>
#include <QtGui/QMainWindow>
#include <QtGui/QStandardItemModel>


class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void showSettings();
    void showAbout();
    void readConfig();
    void timerEvent(QTimerEvent *event);

private:
    QStandardItemModel          *m_dataModel;
    SysTrayIcon                 *m_sysTrayIcon;
    QBasicTimer                 *m_timer;
    DataProvider                *m_dataProvider;
    QTime                        m_lastUpdateTime;

    QPointer<Dialogs::Settings>  m_dialogSettings;
    QPointer<Dialogs::About>     m_dialogAbout;
};


#endif // __MAINWINDOW_H__


// EOF - vim:ts=4:sw=4:et:
