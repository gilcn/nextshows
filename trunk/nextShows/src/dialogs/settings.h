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

#ifndef __DIALOG_SETTINGS_H__
#define __DIALOG_SETTINGS_H__


// Own
#include "ui_settingsdialog.h"
#include "dialogs/settings/findshows.h"
#include "dialogs/settings/options.h"
#include "libs/dataprovider.h"
// QtGui
#include <QtGui/QCloseEvent>
#include <QtGui/QDialog>


namespace Dialogs
{

class Settings : public QDialog
{
    Q_OBJECT

public:
    Settings(QWidget *parent = 0);
    ~Settings();

Q_SIGNALS:
    void settingsChanged();

private Q_SLOTS:
    void changePage(const int &);
    void acceptDialog();

private:
    void setCategoryTitle(const QString &);
    void readSettings();
    void saveSettings();

    Ui::SettingsDialog ui;

    ::Settings::FindShows *m_wFindShows;
    ::Settings::Options   *m_wOptions;

    DataProvider *m_data;
};

} // namespace Dialogs

#endif // __DIALOG_SETTINGS_H__


// EOF - vim:ts=4:sw=4:et:
