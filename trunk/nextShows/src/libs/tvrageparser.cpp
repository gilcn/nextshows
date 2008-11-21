/*
** Copyright (C) 2008 Gilles Chauvin <gcnweb+nextshows@gmail.com>
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
#include "tvrageparser.h"
// QtCore
#include <QtCore/QDebug>
// QtXml
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomNode>


// Keywords used to detect whether a show has ended or not
const QString keywords("Canceled/Ended,Pilot Rejected"); // Separate with commas
const QStringList TvRageParser::m_endedShowStatusKeywords(keywords.split(",", QString::SkipEmptyParts));


/*
** public:
*/
NextShows::ShowInfosList TvRageParser::parseSearchResults(const QByteArray &data)
{
    NextShows::ShowInfosList showList;

    QDomDocument doc("TVRage Search Results");
    if (!doc.setContent(data)) {
        qCritical("Error while parsing search results!");
    }

    QDomElement results = doc.documentElement();

    // <Results>0</Results>
    if (results.text() == "0") {
        return showList;    // Empty show list
    }

    // Iterate over results
    QDomNode resultsDN = results.firstChild();
    while (!resultsDN.isNull())
    {
        if (resultsDN.nodeName() == "show") {
            NextShows::ShowInfos_t show = TvRageParser::parseSearchResults_Show(resultsDN);
            showList << show;
        }
        resultsDN = resultsDN.nextSibling();
    }

    return showList;
} // parseSearchResults()

NextShows::ShowInfos_t TvRageParser::parseShowInfo(const QByteArray &data)
{
    NextShows::ShowInfos_t showInfos;

    QDomDocument doc("TVRage Show Info");
    if (!doc.setContent(data)) {
        qCritical("Error while parsing show info!");
    }

    QDomElement show = doc.documentElement();

    // <Showinfo />
    if (show.text().isEmpty()) {
        return showInfos;
    }

    // Read show infos
    QDomNode showDN = show.firstChild();
    while (!showDN.isNull())
    {
        if (showDN.isElement()) {
            QDomElement element = showDN.toElement();
            QString tagName(element.tagName());
            if (tagName == "showid") {
                showInfos.showid = element.text().toInt();
            } else if (tagName == "showname") {
                showInfos.name = element.text();
            } else if (tagName == "showlink") {
                showInfos.link = QUrl(element.text());
            } else if (tagName == "started") {
                showInfos.started = element.text().toInt();
// FIXME: Missing from feed. Need to get in touch with a TVRage admin
//            } else if (tagName == "ended") {
//                showInfos.ended = element.text().toInt();
// FIXME: Missing from feed. Need to get in touch with a TVRage admin
//            } else if (tagName == "seasons") {
//                showInfos.seasons = element.text().toInt();
            } else if (tagName == "origin_country") {
                showInfos.country = element.text();
            } else if (tagName == "status") {
                showInfos.status = element.text();
                showInfos.endedFlag = TvRageParser::m_endedShowStatusKeywords.contains(showInfos.status);
            } else if (tagName == "classification") {
                showInfos.classification = element.text();
            } else if (tagName == "genres") {
                showInfos.genres = TvRageParser::parseTag_Genres(element);
            } else if (tagName == "runtime") {
                showInfos.runtime = element.text().toInt();
            } else if (tagName == "network") {
                // FIXME
                QString key(element.attribute("country"));
                if (!key.isNull()) {
                    showInfos.network[key] = element.text();
                }
            } else if (tagName == "airtime") {
                showInfos.airtime = QTime::fromString(element.text(), "hh:mm");
            } else if (tagName == "airday") {
                showInfos.airday = element.text();
            } else if (tagName == "timezone") {
                showInfos.timezone = element.text();
            } else if (tagName == "akas") {
                showInfos.akas = TvRageParser::parseTag_Akas(element);
            }
        }

        showDN = showDN.nextSibling();
    }

    return showInfos;
} // parseShowInfo()

NextShows::EpisodeListList TvRageParser::parseEpisodeList(const QByteArray &data)
{
    return NextShows::EpisodeListList();
} // parseEpisodeList()


/*
** private
*/
NextShows::ShowInfos_t TvRageParser::parseSearchResults_Show(const QDomNode &node)
{
    NextShows::ShowInfos_t showInfos;

    QDomNode child = node.firstChild();
    while (!child.isNull())
    {
        if (child.isElement()) {
            QDomElement element = child.toElement();
            QString tagName(element.tagName());
            if (tagName == "showid") {
                showInfos.showid = element.text().toInt();
            } else if (tagName == "name") {
                showInfos.name = element.text();
            } else if (tagName == "link") {
                showInfos.link = QUrl(element.text());
            } else if (tagName == "country") {
                showInfos.country = element.text();
            } else if (tagName == "started") {
                showInfos.started = element.text().toInt();
            } else if (tagName == "ended") {
                showInfos.ended = element.text().toInt();
            } else if (tagName == "seasons") {
                showInfos.seasons = element.text().toInt();
            } else if (tagName == "status") {
                showInfos.status = element.text();
                showInfos.endedFlag = TvRageParser::m_endedShowStatusKeywords.contains(showInfos.status);
            } else if (tagName == "classification") {
                showInfos.classification = element.text();
            } else if (tagName == "genres") {
                showInfos.genres = TvRageParser::parseTag_Genres(element);
            }
        }
        child = child.nextSibling();
    }

    return showInfos;
} // parseSearchResults_Show()

QStringList TvRageParser::parseTag_Genres(const QDomElement &element)
{
    QStringList genreList;

    if (element.hasChildNodes()) {
        QDomNode node = element.firstChild();
        while (!node.isNull()) {
            if (node.isElement()) {
                QDomElement genreElement = node.toElement();
                if (genreElement.tagName() == "genre") {
                    genreList << genreElement.text();
                }
            }
            node = node.nextSibling();
        }
    }

    return genreList;
} // parseTag_Genres()

QMap<QString, QString> TvRageParser::parseTag_Akas(const QDomElement &element)
{
    QMap<QString, QString> akasMap;

    if (element.hasChildNodes()) {
        QDomNode node = element.firstChild();
        while (!node.isNull()) {
            if (node.isElement()) {
                QDomElement akaElement = node.toElement();
                if (akaElement.tagName() == "aka") {
                    QString key(akaElement.attribute("country"));
                    if (!key.isNull()) {
                        akasMap[key] = akaElement.text();
                    }
                }
            }
            node = node.nextSibling();
        }
    }

    return akasMap;
} // parseTag_Akas()

// EOF - vim:ts=4:sw=4:et:
