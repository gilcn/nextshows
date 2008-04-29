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


#include "nextshowsengine.h"
#include "tvrageparser.h"

#include <QtCore/QUrl>
#include <QtNetwork/QHttp>


class NextShowsEngine::Private
{
public:
    Private()
    {
        http      = new QHttp();
        httpGetId = 0;
        searchUrl.setUrl("http://www.tvrage.com/feeds/search.php", QUrl::StrictMode);
        searchUrl.setPort(80);
    };
    ~Private() {};

    QHttp   *http;
    int      httpGetId;
    QUrl     searchUrl;
    QString  currentRequest;
}; // Private()


NextShowsEngine::NextShowsEngine(QObject *parent, const QVariantList &args)
    : Plasma::DataEngine(parent, args)
    , d(new Private())
{
    Q_UNUSED(args);

    connect(d->http, SIGNAL(requestFinished(int, bool)),
            this, SLOT(httpRequestFinished(int, bool)));
}; // ctor()


NextShowsEngine::~NextShowsEngine()
{
    delete d;
}; // dtor()


bool NextShowsEngine::sourceRequestEvent(const QString &request)
{
    if ( request.startsWith("search:", Qt::CaseInsensitive) ) {
        d->currentRequest = request;
        QString searchKeyword(request);
        searchKeyword.remove(0, 7); // Remove "^search:"
        kDebug() << "Search show:" << searchKeyword;

        QPair<QString, QString> show("show", searchKeyword);
        QList<QPair<QString, QString> > params;
        params << show;
        d->searchUrl.setQueryItems(params);
        kDebug() << d->searchUrl.toEncoded();

        d->http->setHost(d->searchUrl.host(),
                         QHttp::ConnectionModeHttp,
                         d->searchUrl.port());
        d->httpGetId = d->http->get(d->searchUrl.toEncoded(QUrl::RemoveScheme |
                                                           QUrl::RemoveAuthority));
        kDebug() << d->httpGetId;
        setData(request, Plasma::DataEngine::Data());

    } else if ( request.startsWith("eplist:", Qt::CaseInsensitive) ) {
        kDebug() << "Episode List";
        setData(request, "EpList", "Not implemented yet!");
    } else {
        // Quick usage help
        setData(request,
                "Usage",
                QVariant("search:showname -> search for a show\neplist:showid -> get episode list for the given show ID"));
        return false;
    }

    return true;
}; // sourceRequestEvent()


void NextShowsEngine::httpRequestFinished(const int reqId, const bool error)
{
    if (reqId != d->httpGetId) {
        return;
    }
    if (error) {
        kDebug() << d->http->errorString();
    }

    QList<TvRageParser::showInfos> showList;
    showList = TvRageParser::parseSearchResults(d->http->readAll());

    QListIterator<TvRageParser::showInfos> it(showList);
    int i=0;
    while (it.hasNext()) {
        kDebug() << d->currentRequest << it.next().value("name").toString();
        //setData(d->currentRequest, it.next().value("name").toString(), QVariant(QString()));
        //setData(d->currentRequest, it.next().value("showid").toString(), "value");
        QString str;
        str.setNum(i, 10);
        setData(d->currentRequest, it.next().value("showid").toString(), QVariant(str));
        ++i;
    }
}; // httpRequestFinished();


#include "nextshowsengine.moc"
