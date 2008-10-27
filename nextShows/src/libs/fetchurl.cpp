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
#include "fetchurl.h"
#include "version.h"
// QtCore
#include <QtCore/QDebug>
#include <QtCore/QUrl>


/*
** public:
*/
FetchUrl::FetchUrl(QObject *parent)
    : QObject(parent)
{
    m_http = new QHttp(this);
    connect(m_http, SIGNAL(requestFinished(int, bool)),
            this, SLOT(httpRequestFinished(const int &, const bool &)));
} // ctor()

FetchUrl::~FetchUrl()
{
} // dtor()

void FetchUrl::getUrl(const QUrl &url)
{
    // Custom header
    QHttpRequestHeader header("GET", url.toEncoded(QUrl::RemoveScheme | QUrl::RemoveAuthority), 1, 1);
    header.setValue("User-agent", QString("nextShows v%1 (http://nextshows.googlecode.com/)").arg(NEXTSHOWS_VERSION));
    header.setValue("Connection", "Keep-Alive");
    header.setValue("Host", url.host());

    m_http->setHost(url.host(), QHttp::ConnectionModeHttp, url.port());
    m_requestId = m_http->request(header);
} // get()


/*
** private Q_SLOTS:
*/
void FetchUrl::httpRequestFinished(const int &id, const bool &error)
{
    qDebug() << "Id:" << id;
    qDebug() << "Error:" << error;
    if (error) {
        qCritical() << "Error while processing HTTP request!";
        qCritical() << m_http->errorString();
    }

    if (id != m_requestId) {
        return;
    }

    emit(dataReady(m_http->readAll()));

    m_requestId = 0;
} // httpRequestFinished()


// EOF - vim:ts=4:sw=4:et:
