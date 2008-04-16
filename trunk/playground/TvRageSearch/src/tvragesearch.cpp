/*
 *   Copyright 2008 Gilles CHAUVIN <gcnweb@gmail.com>
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

#include "tvragesearch.h"

#include <QtCore/QDebug>
#include <QtCore/QUrl>


// Public
TvRageSearch::TvRageSearch(QWidget *parent)
    : QDialog(parent, Qt::Window)
{
    m_http = new QHttp(this);
    connect(m_http, SIGNAL(requestFinished(int, bool)),
            this, SLOT(httpRequestFinished(int, bool)));

    m_progressAnimation = new AnimatedImage(this, ":/pics/working.png");
    connect(m_progressAnimation, SIGNAL(newFrame(const QPixmap &)),
            this, SLOT(setProgressPic(const QPixmap &)));

    ui.setupUi(this);
}

TvRageSearch::~TvRageSearch()
{
    delete m_progressAnimation;
    delete m_http;
}


// Private slots
void TvRageSearch::on_btnLookup_clicked()
{
    if (ui.leSearch->text().isEmpty()) {
        qDebug() << tr("No show to search for...");
        return;
    }
    ui.btnLookup->setEnabled(false);
    m_progressAnimation->start();

    // Prepare URL
    QUrl url("http://www.tvrage.com/feeds/search.php", QUrl::StrictMode);
    url.setPort(80);
    QPair<QString, QString> show("show", ui.leSearch->text());
    QList< QPair<QString, QString> > params;
    params << show;
    url.setQueryItems(params);
    qDebug() << url.toEncoded();

    // HTTP request
    m_http->setHost(url.host(), QHttp::ConnectionModeHttp, url.port());
    m_httpGetId = m_http->get(url.toEncoded(QUrl::RemoveScheme | QUrl::RemoveAuthority));
}

void TvRageSearch::setProgressPic(const QPixmap &pic) const
{
    ui.imgProgress->setPixmap(pic);
}

void TvRageSearch::httpRequestFinished(const int requestId, const bool error) const
{
    if (requestId != m_httpGetId)
        return;
    if (error)
        qDebug() << m_http->errorString();

    // Reset to initial state
    m_progressAnimation->stop();
    ui.imgProgress->setPixmap(QPixmap(":/pics/idle.png"));
    ui.btnLookup->setEnabled(true);
    ui.treeResults->clear();

    QList<TvRageParser::show_t> showList;
    showList = TvRageParser::parseSearchResults(m_http->readAll());
    if (showList.isEmpty()) {
        qDebug() << tr("Empty! No shows found?");
        ui.btnExpand->setEnabled(false);
        ui.btnCollapse->setEnabled(false);
        return;
    } else {
        ui.btnExpand->setEnabled(true);
        ui.btnCollapse->setEnabled(true);
    }

    QList<QTreeWidgetItem *> items;
    QList<QTreeWidgetItem *> childItems;
    for (int i=0; i < showList.count(); ++i) {
        items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(showList.value(i).name)));
        {
            childItems.append(new QTreeWidgetItem(items.last(),
                              QStringList(QString("showid: %1").arg(showList.value(i).showid))));
            childItems.append(new QTreeWidgetItem(items.last(),
                              QStringList(QString("link: %1").arg(showList.value(i).link))));
            childItems.append(new QTreeWidgetItem(items.last(),
                              QStringList(QString("country: %1").arg(showList.value(i).country))));
            childItems.append(new QTreeWidgetItem(items.last(),
                              QStringList(QString("started: %1").arg(showList.value(i).started))));
            childItems.append(new QTreeWidgetItem(items.last(),
                              QStringList(QString("ended: %1").arg(showList.value(i).ended))));
            childItems.append(new QTreeWidgetItem(items.last(),
                              QStringList(QString("seasons: %1").arg(showList.value(i).seasons))));
            childItems.append(new QTreeWidgetItem(items.last(),
                              QStringList(QString("classification: %1").arg(showList.value(i).classification))));
            childItems.append(new QTreeWidgetItem(items.last(),
                              QStringList(QString("genres: %1").arg(showList.value(i).genres))));
        }
        QColor color = ( !showList.value(i).ended ) ? "#000000" : "#555555";
        QFont   font = items.last()->font(0);
        ( !showList.value(i).ended ) ? font.setWeight(QFont::Bold) : font.setWeight(QFont::Normal);
        items.last()->setForeground(0, QBrush(color));
        items.last()->setFont(0, font);
    }
    ui.treeResults->insertTopLevelItems(0, items);
}

// Expand
void TvRageSearch::on_btnExpand_clicked()
{
    for (int i=0; i < ui.treeResults->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = ui.treeResults->topLevelItem(i);
        ui.treeResults->expandItem(item);
    }
}

// Collapse
void TvRageSearch::on_btnCollapse_clicked()
{
    for (int i=0; i < ui.treeResults->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = ui.treeResults->topLevelItem(i);
        ui.treeResults->collapseItem(item);
    }
}

// Quit
void TvRageSearch::on_btnQuit_clicked()
{
    close();
}
