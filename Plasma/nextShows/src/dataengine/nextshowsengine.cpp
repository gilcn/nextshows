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
        searchUrl.setUrl("http://www.tvrage.com/feeds/search.php",
                         QUrl::StrictMode); // show=showname
//        searchUrl.setPort(80);
        epListUrl.setUrl("http://www.tvrage.com/feeds/episode_list.php",
                         QUrl::StrictMode); // sid=showid
//        epListUrl.setPort(80);
    };
    ~Private() {};

    QHttp   *http;
    int      httpGetId;
    QUrl     searchUrl;
    QUrl     epListUrl;
    QString  currentRequest;
    RequestType requestType;
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
    if (request.startsWith("search:", Qt::CaseInsensitive)) {
        d->currentRequest = request;
        QString searchKeyword(request);
        searchKeyword.remove(0, 7); // Remove "^search:"
        kDebug() << "Search show:" << searchKeyword;

        QPair<QString, QString> show("show", searchKeyword);
        QList<QPair<QString, QString> > params;
        params << show;
        d->searchUrl.setQueryItems(params);
        kDebug() << d->searchUrl.toEncoded();

        d->requestType = NextShowsEngine::Search;
        d->http->setHost(d->searchUrl.host(), QHttp::ConnectionModeHttp);
        d->httpGetId = d->http->get(d->searchUrl.toEncoded(QUrl::RemoveScheme |
                                                           QUrl::RemoveAuthority));
        kDebug() << d->httpGetId;
        setData(request, Plasma::DataEngine::Data());

    } else if (request.startsWith("eplist:", Qt::CaseInsensitive)) {
        d->currentRequest = request;
        QString showId(request);
        showId.remove(0, 7); // Remove "^eplist:"
        kDebug() << "Episode ID:" << showId;

        QPair<QString, QString> sid("sid", showId);
        QList<QPair<QString, QString> > params;
        params << sid;
        d->epListUrl.setQueryItems(params);
        kDebug() << d->epListUrl.toEncoded();

        d->requestType = NextShowsEngine::EpisodeList;
        d->http->setHost(d->epListUrl.host(), QHttp::ConnectionModeHttp);
        d->httpGetId = d->http->get(d->epListUrl.toEncoded(QUrl::RemoveScheme |
                                                          QUrl::RemoveAuthority));
        kDebug() << d->httpGetId;
        setData(request, Plasma::DataEngine::Data());
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

    switch(d->requestType)
    {
        case NextShowsEngine::Search: {
            QList<TvRageParser::showInfos> showList;
            showList = TvRageParser::parseSearchResults(d->http->readAll());

            QListIterator<TvRageParser::showInfos> it(showList);
            while (it.hasNext()) {
                TvRageParser::showInfos item(it.next());
                kDebug() << d->currentRequest << item.value("name").toString();
                setData(d->currentRequest, QString("[%1] %2").arg(item.value("showid").toString()).arg(item.value("name").toString()), QVariant(item));
            }
        }
        case NextShowsEngine::EpisodeList: {
            QList<TvRageParser::episodeInfos> episodeList;
            episodeList = TvRageParser::parseEpisodeList(d->http->readAll());
            QString key = episodeList.first().keys().at(0);
            setData(d->currentRequest, "showname", QVariant(episodeList.first()[key]));
        }
    }
}; // httpRequestFinished()


#include "nextshowsengine.moc"
