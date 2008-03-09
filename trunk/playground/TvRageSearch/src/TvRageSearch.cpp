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

#include "TvRageSearch.h"

#include <QtCore/QDebug>
#include <QtCore/QList>
#include <QtCore/QPair>
#include <QtCore/QUrl>


TvRageSearch::TvRageSearch(QWidget *parent)
    : QDialog(parent, Qt::Window)
    , m_http(new QHttp())
{
    ui.setupUi(this);
    connect(ui.btnQuit, SIGNAL(clicked()), this, SLOT(close()));

    m_ai = new AnimImage(this);
    connect(m_ai, SIGNAL(nextFrame(const QPixmap &)),
            this, SLOT(progressPic(const QPixmap &)));
    m_ai->setPicture(":/pics/working.png");

    connect(ui.btnLookup, SIGNAL(clicked()), this, SLOT(testAnim()));

}

TvRageSearch::~TvRageSearch()
{
    delete m_ai;
}

void TvRageSearch::progressPic(const QPixmap &pic)
{
    ui.imgProgress->setPixmap(pic);
}

void TvRageSearch::testAnim()
{
    if (m_ai->active()) {
        m_ai->stop();
        ui.imgProgress->setPixmap(QPixmap(":/pics/idle.png"));
    } else {
        m_ai->start();
    }

    QUrl url("http://www.tvrage.com/feeds/search.php");
    QPair<QString, QString> param("show", ui.leSearch->text());
    QList< QPair<QString,QString> > list;
    list << param;
    url.setQueryItems(list);
    qDebug() << url.toEncoded();
}
