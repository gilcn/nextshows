/*
 *   Copyright 2008 Gilles CHAUVIN <gcnweb+nextshows@gmail.com>
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


// Own
#include "tvrageparser.h"

// QtCore
#include <QtCore/QDebug>
// QtXml
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomNode>


/*
** public:
*/
QList<TvRageParser::show_t> TvRageParser::parseSearchResults(const QByteArray &content)
{
    QList<TvRageParser::show_t> showList;

    QDomDocument doc("Search Results");
    if (!doc.setContent(content))
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
            TvRageParser::show_t show;
            show=parseShow(resultsDN);
            showList << show;
        }
        resultsDN = resultsDN.nextSibling();
    }

    return showList;
} // parseSearchResults()


/*
** private:
*/
TvRageParser::show_t TvRageParser::parseShow(const QDomNode &node)
{
    TvRageParser::show_t showInfos;

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
            } else if (tagName == "classification") {
                showInfos.classification = element.text();
            } else if (tagName == "genres") {
                showInfos.genres = element.text();
            }
        }
        child = child.nextSibling();
    }

    return showInfos;
} // parseShow()


// EOF - vim:ts=4:sw=4:et:
