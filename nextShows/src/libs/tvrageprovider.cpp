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
#include "tvrageprovider.h"
// QtCore
#include <QtCore/QDebug>
// QtXml
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomNode>


/*
** public:
*/
TvRageProvider::TvRageProvider(QObject *parent)
    : AbstractProvider(parent)
{
} // ctor()

TvRageProvider::~TvRageProvider()
{
} // dtor()


/*
** protected:
*/
QUrl TvRageProvider::urlForRequest(const AbstractProvider::RequestType &urlType, const QString &request)
{
    QUrl url;

    switch(urlType) {
    case AbstractProvider::SearchShow:
        url="http://www.tvrage.com:80/feeds/search.php";
        url.addQueryItem("results", "-1"); // Request all available results
        url.addQueryItem("show", request);
        break;
    case AbstractProvider::EpisodeList:
        url="http://www.tvrage.com:80/feeds/episode_list.php";
        url.addQueryItem("sid", request);
        break;
    default:
        qFatal("This should never happen!\n%s", Q_FUNC_INFO);
    }

    return url;
} // urlForRequest()


QList<AbstractProvider::SearchResults_t> TvRageProvider::parseSearchResults(const QByteArray &data)
{
    QList<AbstractProvider::SearchResults_t> showList;

    QDomDocument doc("TvRage Search Results");
    if (!doc.setContent(data))
        qCritical() << tr("Error while parsing document!");

    QDomElement results = doc.documentElement();

    // <Results>0</Results>
    if (results.text() == "0")
        return showList;    // Empty show list

    // Iterate over results
    QDomNode resultsDN = results.firstChild();
    while (!resultsDN.isNull())
    {
        if (resultsDN.nodeName() == "show") {
            AbstractProvider::SearchResults_t show(parseSearchResultsTag_Show(resultsDN));
            showList << show;
        }
        resultsDN = resultsDN.nextSibling();
    }

    return showList;
} // parseSearchResults()

QVariant TvRageProvider::parseEpisodeList(const QByteArray &/*data*/)
{
    return QVariant();
} // parseEpisodeList()


/*
** private:
*/
AbstractProvider::SearchResults_t TvRageProvider::parseSearchResultsTag_Show(const QDomNode &node)
{
    AbstractProvider::SearchResults_t showInfos;

    QDomNode child = node.firstChild();
    while (!child.isNull())
    {
        if (child.isElement()) {
            QDomElement element = child.toElement();
            QString tagName(element.tagName().toLower());
            if (tagName == "showid") {
                showInfos.showid = element.text().toUInt();
            } else if (tagName == "name") {
                showInfos.name = element.text();
            } else if (tagName == "link") {
                showInfos.link = element.text();
            } else if (tagName == "country") {
                showInfos.country = element.text();
            } else if (tagName == "started") {
                showInfos.started = element.text().toUInt();
            } else if (tagName == "ended") {
                showInfos.ended = element.text().toUInt();
            } else if (tagName == "seasons") {
                showInfos.seasons = element.text().toUInt();
            } else if (tagName == "status") {
                showInfos.status = element.text();
                showInfos.endedFlag = (showInfos.status == "Canceled/Ended") ? true : false; 
            } else if (tagName == "classification") {
                showInfos.classification = element.text();
            } else if (tagName == "genres") {
                if (element.hasChildNodes()) {
                    QDomNode genreNode = element.firstChild();
                    while (!genreNode.isNull()) {
                        QDomElement genreElement = genreNode.toElement();
                        showInfos.genres << genreElement.text();
                        genreNode = genreNode.nextSibling();
                    }
                }
            }
        }
        child = child.nextSibling();
    }

    return showInfos;
} // parseSearchResultsTag_Show()


// EOF - vim:ts=4:sw=4:et:
