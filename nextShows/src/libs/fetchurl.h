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

#ifndef __FETCHURL_H__
#define __FETCHURL_H__


// QtCore
#include <QtCore/QObject>
// QtNetwork
#include <QtNetwork/QHttp>
// Forward declarations
class QUrl;


class FetchUrl : public QObject
{
    Q_OBJECT

public:
    FetchUrl(QObject *parent = 0);
    ~FetchUrl();

    void getUrl(const QUrl &);

Q_SIGNALS:
    // Emitted when data were received and ready to be served
    void dataReady(const QByteArray &);

private Q_SLOTS:
    void httpRequestFinished(const int &, const bool &);

private:
    QHttp *m_http;
    int m_requestId;
};


#endif // __FETCHURL_H__


// EOF - vim:ts=4:sw=4:et:
