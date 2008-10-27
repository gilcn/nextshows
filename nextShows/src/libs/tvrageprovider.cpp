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
QUrl TvRageProvider::urlForRequest(const AbstractProvider::UrlType &urlType, const QString &request)
{
    QUrl url;

    switch(urlType) {
    case AbstractProvider::SearchShowUrl:
        url="http://www.tvrage.com:80/feeds/search.php";
        url.addQueryItem("show", request);
        break;
    case AbstractProvider::EpisodeListUrl:
        url="http://www.tvrage.com:80/feeds/episode_list.php";
        url.addQueryItem("sid", request);
        break;
    }

    qDebug() << "urlForRequest:" << url;
    return url;
} // urlForRequest()


QVariantList TvRageProvider::parseSearchResults(const QByteArray &data)
{
    QVariantList showList;

    QDomDocument doc("TvRage Search Results");
    if (!doc.setContent(data))
        qCritical() << QObject::tr("Error while parsing document!");

    QDomElement results = doc.documentElement();

    // <Results>0</Results>
    if (results.text() == "0")
        return showList;    // Empty show list

    // Iterate over results
    QDomNode resultsDN = results.firstChild();
    while (!resultsDN.isNull())
    {
        if (resultsDN.nodeName() == "show") {
            QVariantMap show(parseSearchResultsTag_Show(resultsDN));
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
QVariantMap TvRageProvider::parseSearchResultsTag_Show(const QDomNode &node)
{
    QVariantMap showInfos;

    QDomNode child = node.firstChild();
    while (!child.isNull())
    {
        if (child.isElement()) {
            QDomElement element = child.toElement();
            QString tagName(element.tagName().toLower());
            if (tagName == "showid") {
                showInfos[tagName] = element.text().toUInt();
            } else if (tagName == "name") {
                showInfos[tagName] = element.text();
            } else if (tagName == "link") {
                showInfos[tagName] = element.text();
            } else if (tagName == "country") {
                showInfos[tagName] = element.text();
            } else if (tagName == "started") {
                showInfos[tagName] = element.text().toUInt();
            } else if (tagName == "ended") {
                showInfos[tagName] = element.text().toUInt();
            } else if (tagName == "seasons") {
                showInfos[tagName] = element.text().toUInt();
            } else if (tagName == "classification") {
                showInfos[tagName] = element.text();
            } else if (tagName == "genres") {
                showInfos[tagName] = element.text();
            }
        }
        child = child.nextSibling();
    }

    return showInfos;
} // parseSearchResultsTag_Show()


// EOF - vim:ts=4:sw=4:et:
