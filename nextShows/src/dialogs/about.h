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

#ifndef __DIALOG_ABOUT_H__
#define __DIALOG_ABOUT_H__


// Own
#include "ui_aboutdialog.h"

// Qt
#include <QtGui/QDialog>

namespace Dialogs
{

class About : public QDialog
{
    Q_OBJECT

public:
    About(QWidget *parent = 0);
    ~About();

private:
    Ui::AboutDialog ui;
};

} // namespace Dialogs

#endif // __ABOUTDIALOG_H__


// EOF - vim:ts=4:sw=4:et:
