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

#ifndef __VERSION_H__
#define __VERSION_H__


#define _TEXT(x) #x
#define TEXT(x) _TEXT(x)

// nextShows version
#define NEXTSHOWS_RELEASE 2.99.0
#ifdef SVN_VERSION
    #define NEXTSHOWS_VERSION TEXT(SVN_VERSION) "/svn"
#else
    #define NEXTSHOWS_VERSION TEXT(NEXTSHOWS_RELEASE)
#endif

// Build date / time
#define NEXTSHOWS_BUILDDATE __DATE__ " - " __TIME__

// GCC version
#define GCC_VERSION TEXT(__GNUC__.__GNUC_MINOR__.__GNUC_PATCHLEVEL__)


#endif // __VERSION_H__


// EOF - vim:ts=4:sw=4:et:
