/*
** Copyright (C) 2008 Emmanuel HAMELET <kh.starlifter@gmail.com>
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

#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__


// Own
#include "ui_mainwindow.h"
#include "dbinterface.h"
// QtGui
#include <QtGui/QDialog>


class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnSaveShow_clicked(bool checked);
    void on_btnListShow_clicked(bool checked);
    void on_btnCheckExpiredShows_clicked(bool checked);
    void on_btnRequestDB_clicked(bool checked);

private:
    Ui::MainWindow ui;
    DbInterface *m_dbinterface;
    QMap<QString, QString> *map;
};


#endif // __MAINWINDOW_H__
