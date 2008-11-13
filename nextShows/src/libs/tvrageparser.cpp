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
QList<NextShows::ShowInfos_t> TvRageParser::parseSearchResults(const QByteArray &data)
{
    QList<NextShows::ShowInfos_t> showList;

    QDomDocument doc("TvRage Search Results");
    if (!doc.setContent(data)) {
        qCritical("Error while parsing document!");
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
            NextShows::ShowInfos_t show = TvRageParser::parseSearchResults_Show(resultsDN);
            showList << show;
        }
        resultsDN = resultsDN.nextSibling();
    }

    return showList;
} // parseSearchResults()


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
                showInfos.endedFlag = TvRageParser::m_endedShowStatusKeywords.contains(showInfos.status);
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
} // parseSearchResults_Show()


// EOF - vim:ts=4:sw=4:et:
