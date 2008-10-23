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
#include "misc.h"


namespace Settings
{

/*
** public:
*/
Misc::Misc(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    setWindowTitle(tr("Misc"));
    setWindowIcon(QIcon(":/images/prefs/television.png"));
} // ctor()

Misc::~Misc()
{
} // dtor()

} // namespace Settings


// EOF - vim:ts=4:sw=4:et:
