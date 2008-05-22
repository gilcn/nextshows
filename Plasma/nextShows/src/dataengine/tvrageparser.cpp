/*
** Copyright (C) 2008 Gilles CHAUVIN <gcnweb@gmail.com>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as
** published by the Free Software Foundation; either version 2,
** or (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details
**
** You should have received a copy of the GNU Library General Public
** License along with this program; if not, write to the
** Free Software Foundation, Inc.,
** 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "tvrageparser.h"

#include <QtCore/QDebug>
#include <QtCore/QStringList>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomNode>


QList<TvRageParser::showInfos> TvRageParser::parseSearchResults(const QByteArray &feed)
{
    QList<TvRageParser::showInfos> showList;

    QDomDocument doc("Search Results");
    if (!doc.setContent(feed)) {
        qCritical() << QObject::tr("Search: Error while parsing document!");
    }

    QDomElement results = doc.documentElement();

    // <Results>0</Results>
    if (results.text() == "0")
        return showList;    // Empty show list

    // Iterate over results
    QDomNode resultsDN = results.firstChild();
    while (!resultsDN.isNull())
    {
        if (resultsDN.nodeName() == "show") {
            TvRageParser::showInfos show;
            show=parseSearchResults_Show(resultsDN);
            showList << show;
        }
        resultsDN = resultsDN.nextSibling();
    }

    return showList;
} // parseSearchResults()


TvRageParser::showInfos TvRageParser::parseSearchResults_Show(const QDomNode &node)
{
    TvRageParser::showInfos showInfos;

    QDomNode child = node.firstChild();
    while (!child.isNull())
    {
        if (child.isElement()) {
            QDomElement element = child.toElement();
            QString tagName(element.tagName().toLower());
            if (tagName == "showid") {
                showInfos["showid"] = element.text().toUInt();
            } else if (tagName == "name") {
                showInfos["name"] = element.text();
            } else if (tagName == "link") {
                showInfos["link"] = element.text();
            } else if (tagName == "country") {
                showInfos["country"] = element.text();
            } else if (tagName == "started") {
                showInfos["started"] = element.text().toUInt();
            } else if (tagName == "ended") {
                showInfos["ended"] = element.text().toUInt();
            } else if (tagName == "seasons") {
                showInfos["seasons"] = element.text().toUInt();
            } else if (tagName == "classification") {
                showInfos["classification"] = element.text();
            } else if (tagName == "genres") {
                QStringList genres;
                QDomNode genre = child.firstChild();
                while (!genre.isNull())
                {
                    if (genre.isElement()) {
                        QDomElement genreElement = genre.toElement();
                        genres.append(genreElement.text());
                    }
                    genre = genre.nextSibling();
                }
                showInfos["genres"] = genres;
            }
        }
        child = child.nextSibling();
    }

    return showInfos;
} // parseSearchResults_Show()


QList<TvRageParser::episodeInfos> TvRageParser::parseEpisodeList(const QByteArray &feed)
{
    QList<TvRageParser::episodeInfos> episodeList;

    QDomDocument doc("Episode List");
    if (!doc.setContent(feed)) {
        qCritical() << QObject::tr("EpList: Error while parsing document!");
    }

    QDomElement root = doc.documentElement();
    QDomNode tag = root.firstChild();
    TvRageParser::episodeInfos ep;
    while (!tag.isNull())
    {
        QString tagName(tag.toElement().tagName().toLower());
        if (tagName == "name") {
            ep["name"] = tag.toElement().text();
        }
        else if (tagName == "totalseasons") {
            ep["totalseasons"] = tag.toElement().text();
        }
        tag = tag.nextSibling();
    }
    episodeList << ep;

    //KILLME
    /*
    QString showName(doc.documentElement().firstChild().toElement().text());
    TvRageParser::episodeInfos ep;
    ep[showName] = showName;
    episodeList << ep;
    */
    //KILLME

    return episodeList;
} // parseEpisodeList()
