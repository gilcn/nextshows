/*
 *   Copyright (C) 2008 Gilles CHAUVIN <gcnweb@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License either version 2, or
 *   (at your option) any later version as published by the Free Software
 *   Foundation.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef __EETEST_DATAENGINE_H__
#define __EETEST_DATAENGINE_H__


#include "plasma/dataengine.h"


class EETestEngine : public Plasma::DataEngine
{
    Q_OBJECT;

public:
    struct MyUserType {
        int     a;
        QString b;
    };

    EETestEngine(QObject *parent, const QVariantList &args);
    ~EETestEngine();

protected:
    void init();
    bool sourceRequestEvent(const QString &source);
};


K_EXPORT_PLASMA_DATAENGINE(eetest, EETestEngine)


#endif // __EETEST_DATAENGINE_H__
