/*
** Copyright (C) 2008 Emmanuel Hamelet <kh.starlifter+nextshows@gmail.com>
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

// ######################################################################
//    Coding: UTF-8, 4 spaces indent
// ######################################################################


// Own
#include "schedulewidget.h"

// QT
#include <QtGui>
#include <QDebug>


/*
** public:
*/
ScheduleWidget::ScheduleWidget(QWidget *parent)
{
    qDebug();
    setupActions();

} // ctor()

ScheduleWidget::~ScheduleWidget()
{
    qDebug();
} // dtor()


/*
** private:
*/
void ScheduleWidget::setupActions()
{
    qDebug();

    // Tune the default option of QTableWidget
    this->setShowGrid(false);
    this->setCornerButtonEnabled(false);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setAlternatingRowColors(true);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->setColumnCount(5);
    this->setHorizontalHeaderLabels(QStringList() << tr("Show") << tr("Saison") << tr("Episode") << tr("Episode name") << tr("When"));
    this->setRowCount(5);

    // Set the header label
    qDebug() << "Horizontal Header" << horizontalHeader();


} // setupActions()
