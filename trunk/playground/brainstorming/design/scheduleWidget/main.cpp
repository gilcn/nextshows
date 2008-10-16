/*
** Copyright (C) 2008 Emmanuel Hamelet <kh.starlifter@gmail.com>
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
#include "schedulewidget.h"

// QT
#include <QApplication>
#include <QtGui/QStandardItemModel>
#include <QtGui/QHeaderView>

#include <QtCore/QDate>

int main (int argc, char *argv[])
{
    // Create a datamodel to fill ScheduleWidget
    QStandardItemModel *m_dataModel = new QStandardItemModel();
    m_dataModel->setColumnCount(5);
    QStringList labels;
    labels << "Show" << "Episode name"
            << "Season" << "Episode #" << "Date";
    m_dataModel->setHorizontalHeaderLabels(labels);
    // Fill with random stuff
    for (int i=0; i<30; ++i) {
        m_dataModel->setItem(i, 0, new QStandardItem(QString("show_%1").arg(i)));
        m_dataModel->setItem(i, 1, new QStandardItem(QString("episode_%1").arg(i)));
        m_dataModel->setItem(i, 2, new QStandardItem(QString("%1").arg(rand()%10+1)));
        m_dataModel->setItem(i, 3, new QStandardItem(QString("%1").arg(rand()%24+1)));
        QDate rndDate = QDate::currentDate().addDays(i);
        m_dataModel->setItem(i, 4, new QStandardItem(rndDate.toString("yyyy/MM/dd")));
    }

    QApplication app(argc, argv);
    ScheduleWidget *window = new ScheduleWidget();
    window->setModel(m_dataModel);
    window->show();
    return app.exec();
}