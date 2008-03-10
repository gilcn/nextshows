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

#include "tvragesearch.h"

#include <QtCore/QDebug>
#include <QtCore/QUrl>


// Public
TvRageSearch::TvRageSearch(QWidget *parent)
    : QDialog(parent, Qt::Window)
{
    m_http = new QHttp(this);
    connect(m_http, SIGNAL(requestFinished(int, bool)),
            this, SLOT(httpRequestFinished(int, bool)));

    m_progressAnimation = new AnimatedImage(this, ":/pics/working.png");
    connect(m_progressAnimation, SIGNAL(newFrame(const QPixmap &)),
            this, SLOT(setProgressPic(const QPixmap &)));

    ui.setupUi(this);

    // Lookup
    connect(ui.btnLookup, SIGNAL(clicked()), this, SLOT(lookup()));
    // Quit
    connect(ui.btnQuit, SIGNAL(clicked()), this, SLOT(close()));
}

TvRageSearch::~TvRageSearch()
{
    delete m_progressAnimation;
    delete m_http;
}


// Private slots
void TvRageSearch::lookup()
{
    if (ui.leSearch->text().isEmpty()) {
        qDebug() << "No show to search for...";
        return;
    }
    ui.btnLookup->setEnabled(false);
    m_progressAnimation->start();
    ui.teResults->clear();

    // Prepare URL
    QUrl url("http://www.tvrage.com/feeds/search.php", QUrl::StrictMode);
    url.setPort(80);
    QPair<QString, QString> show("show", ui.leSearch->text());
    QList< QPair<QString, QString> > params;
    params << show;
    url.setQueryItems(params);
    qDebug() << url.toEncoded(QUrl::RemoveScheme | QUrl::RemoveAuthority);

    // HTTP request
    m_http->setHost(url.host(), QHttp::ConnectionModeHttp, url.port());
    m_httpGetId = m_http->get(url.toEncoded(QUrl::RemoveScheme | QUrl::RemoveAuthority));
}

void TvRageSearch::setProgressPic(const QPixmap &pic)
{
    ui.imgProgress->setPixmap(pic);
}

void TvRageSearch::httpRequestFinished(const int requestId, const bool error)
{
    if (requestId != m_httpGetId)
        return;
    if (error)
        qDebug() << m_http->errorString();

    m_progressAnimation->stop();
    ui.imgProgress->setPixmap(QPixmap(":/pics/idle.png"));
    ui.btnLookup->setEnabled(true);

    QByteArray results(m_http->readAll());
    ui.teResults->setPlainText(results);
    m_showList = TvRageParser::parseSearchResults(results);
    if (m_showList.isEmpty())
        qDebug() << "Empty!";

    qDebug() << m_showList.value(1).link;
}
