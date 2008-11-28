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


// Own
#include "config.h"
// QtCore
#include <QtCore/QSettings>


// Default values
#define BROWSER_KEY       "browser"
#define BROWSER_VAL       "firefox -remote 'openURL($url$,new-tab)'"
#define CACHEDURATION_KEY "cache_duration"
#define CACHEDURATION_VAL 1


/*
** public:
*/
QVariant Config::getValue(Config::Keys key)
{
    QSettings settings;
    QVariant value;

    switch (key) {
    case Config::Browser:
        value=settings.value(BROWSER_KEY, BROWSER_VAL);
        break;
    case Config::CacheDuration:
        value=settings.value(CACHEDURATION_KEY, CACHEDURATION_VAL);
        break;
    default:
        qWarning("%s\nThis should never happen !!!", Q_FUNC_INFO);
    }

    return value;
} // getValue()

void Config::setValue(Config::Keys key, const QVariant &value)
{
    QSettings settings;

    switch (key) {
    case Config::Browser:
        settings.setValue(BROWSER_KEY, value);
        break;
    case Config::CacheDuration:
        settings.setValue(CACHEDURATION_KEY, value);
        break;
    default:
        qWarning("%s\nThis should never happen !!!", Q_FUNC_INFO);
    }
} // setValue()


// EOF - vim:ts=4:sw=4:et:
