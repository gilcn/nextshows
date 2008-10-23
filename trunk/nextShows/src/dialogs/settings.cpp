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
#include "dialogs/settings.h"

// QtCore
#include <QtCore/QDebug>


namespace Dialogs
{

/*
** public:
*/
Settings::Settings(QWidget *parent)
    : QDialog(parent, Qt::Dialog)
    , m_wFindShows(new ::Settings::FindShows)
    , m_wMisc(new ::Settings::Misc)
{
    ui.setupUi(this);

    ui.wPanel->addWidget(m_wFindShows);
    ui.wCategories->addCategory(m_wFindShows->windowTitle(), m_wFindShows->windowIcon());
    ui.wPanel->addWidget(m_wMisc);
    ui.wCategories->addCategory(m_wMisc->windowTitle(), m_wMisc->windowIcon());

/*
    for (int i=0; i<ui.wPanel->count(); ++i) {
        QWidget *page = ui.wPanel->widget(i);
        ui.wCategories->addCategory(page->windowTitle(), page->windowIcon());
    }

    ui.lblCategoryName->setText(ui.wPanel->currentWidget()->windowTitle());
*/

    connect(ui.wCategories, SIGNAL(categoryChanged(const int &)), this, SLOT(changePage(const int &)));
} // ctor()

Settings::~Settings()
{
} // dtor()


/*
** private Q_SLOTS:
*/
void Settings::changePage(const int &id)
{
    ui.wPanel->setCurrentIndex(id);
    ui.lblCategoryName->setText(ui.wPanel->currentWidget()->windowTitle());
} // changePage()

} // namespace Dialogs


// EOF - vim:ts=4:sw=4:et:
