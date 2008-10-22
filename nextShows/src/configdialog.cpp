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
#include "configdialog.h"

// QtCore
#include <QtCore/QDebug>


/*
** public:
*/
ConfigDialog::ConfigDialog(QWidget *parent)
    : QDialog(parent, Qt::Dialog)
{
    ui.setupUi(this);

    for (int i=0; i<ui.wPanel->count(); ++i) {
        QWidget *page = ui.wPanel->widget(i);
        ui.wCategories->addCategory(page->windowTitle(), page->windowIcon());
    }

    ui.lblCategoryName->setText(ui.wPanel->currentWidget()->windowTitle());

    connect(ui.wCategories, SIGNAL(categoryChanged(const int &)), this, SLOT(changePage(const int &)));
} // ctor()

ConfigDialog::~ConfigDialog()
{
} // dtor()


/*
** private:
*/
void ConfigDialog::changePage(const int &id)
{
    ui.wPanel->setCurrentIndex(id);
    ui.lblCategoryName->setText(ui.wPanel->currentWidget()->windowTitle());
} // changePage()


// EOF - vim:ts=4:sw=4:et:
