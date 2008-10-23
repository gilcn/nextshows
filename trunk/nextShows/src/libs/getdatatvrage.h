/*
 *   Copyright 2008 Emmanuel Hamelet <kh.starlifter@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as
 *   published by the Free Software Foundation; either version 2,
 *   or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */


#ifndef __GETDATATVRAGE_H__
#define __GETDATATVRAGE_H__


// QtCore
#include <QtCore/QVariant>
#include <QtCore/QUrl>

// QtNetwork
#include <QtNetwork/QHttp>

class GetDataTvRage
{
    public:
        static QVariant searchShow(QVariant showname);

};


#endif // __GETDATATVRAGE_H__


// EOF - vim:ts=4:sw=4:et:
