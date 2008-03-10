/*
 *   Copyright 2008 Gilles CHAUVIN <gcnweb@gmail.com>
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

#ifndef __TVRAGESEARCH_H__
#define __TVRAGESEARCH_H__

#include "libs/animatedimage.h"

#include "ui_tvragesearch.h"

#include <QtGui/QDialog>
#include <QtNetwork/QHttp>


class TvRageSearch : public QDialog
{
    Q_OBJECT

public:
    TvRageSearch(QWidget *parent=0);
    ~TvRageSearch();

private:
    Ui::TvRageSearch ui;

    AnimatedImage *m_ai;
    QHttp         *m_http;

private slots:
    void progressPic(const QPixmap &pic);
    void testAnim();
};

#endif // __TVRAGESEARCH_H__
