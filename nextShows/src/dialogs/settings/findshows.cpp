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
#include "findshows.h"
// QtCore
#include <QtCore/QDebug>
#include <QtCore/QFile>


namespace Settings
{

/*
** public:
*/
FindShows::FindShows(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    // Adjust Layout
    QLayout *widgetLayout = layout();
    QGridLayout *gridLayout = qobject_cast<QGridLayout *>(widgetLayout);
    if (gridLayout) {
        gridLayout->setColumnStretch(0, 20); // "Search Results" column
        gridLayout->setColumnStretch(2, 10); // "Tracked shows" column
    }

    // Category title
    setWindowTitle(tr("Find Shows"));
    // Category icon
    setWindowIcon(QIcon(":/pixmaps/prefs/television.png"));


    ui.leSearch->setClickMessage(tr("Enter a show name"));
    // FIXME: Qt4.5
//    ui.leSearch->setIcon(QIcon(":/pixmaps/prefs/progress_idle.png"));


    m_animatedImage = new AnimatedImage(this,
                                        ":/pixmaps/prefs/progress_working.png",
                                        ":/pixmaps/prefs/progress_idle.png");
    connect(m_animatedImage, SIGNAL(newFrame(const QPixmap &)),
            this, SLOT(newImageFrame(const QPixmap &)));

    m_tvrage = new TvRageProvider(this);
    connect(m_tvrage, SIGNAL(searchResultsReady(QList<AbstractProvider::SearchResults_t>)),
            this, SLOT(searchResultsReady(const QList<AbstractProvider::SearchResults_t> &)));

    m_filterResults = (ui.cbFilterResults->checkState() == Qt::Checked) ? true : false;
} // ctor()

FindShows::~FindShows()
{
    delete m_tvrage;
    delete m_animatedImage;
} // dtor()


/*
** private Q_SLOTS:
*/
void FindShows::on_btnLookup_clicked()
{
    if (ui.leSearch->text().isEmpty()) {
        return;
    }

    ui.leSearch->setEnabled(false);
    ui.btnLookup->setEnabled(false);

    m_animatedImage->start();
    m_tvrage->searchShow(ui.leSearch->text());
} // on_btnLookup_clicked()

void FindShows::on_cbFilterResults_stateChanged(int state)
{
    m_filterResults = (state == Qt::Checked) ? true : false;
    displaySearchResults(); // Refresh list
} // on_cbFilterResults_stateChanged()

void FindShows::newImageFrame(const QPixmap &pixmap)
{
//    ui.btnLookup->setIcon(pixmap);
    ui.imgProgress->setPixmap(pixmap);
} // newImageFrame()

void FindShows::searchResultsReady(const QList<AbstractProvider::SearchResults_t> &showList)
{
    m_searchResults = showList;

    m_animatedImage->stop();

    ui.leSearch->setEnabled(true);
    ui.btnLookup->setEnabled(true);

    displaySearchResults(); // Refresh list
} // searchResultsReady()


/*
** private:
*/
void FindShows::displaySearchResults()
{
    ui.treeSearchResults->clear();

    int displayedShowCounter = 0;

    foreach(AbstractProvider::SearchResults_t show, m_searchResults) {
        if (m_filterResults && show.endedFlag) {
            continue; // Skip to the next result when user wants to filter
        }

        QTreeWidgetItem *parentItem = new QTreeWidgetItem();
        QFont font(parentItem->font(0));
        QBrush brush(parentItem->foreground(0));
        QString flagFile = QString(":/pixmaps/flags/%1.gif").arg(show.country.toLower());

        if (QFile::exists(flagFile)) {
            parentItem->setIcon(0, QIcon(flagFile));
        } else {
            parentItem->setIcon(0, QIcon(":/pixmaps/flags/unknown.gif"));
        }

        parentItem->setText(0, show.name);

        if (!show.endedFlag) {
            if (!m_filterResults) {
                font.setBold(true);
                parentItem->setFont(0, font);
            }
        } else {
            brush.setColor(Qt::gray);
            parentItem->setForeground(0, brush);
        }

        ui.treeSearchResults->addTopLevelItem(parentItem);

        // Seasons
        {
            QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);
            childItem->setForeground(0, brush);
            childItem->setText(0, QString("Seasons: %1").arg(show.seasons));
        }
        // Status
        {
            QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);
            childItem->setForeground(0, brush);
            childItem->setText(0, QString("Status: %1").arg(show.status));
        }
        // Started
        {
            QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);
            childItem->setForeground(0, brush);
            childItem->setText(0, QString("Started: %1").arg(show.started));
        }
        // Ended
        if (show.ended != 0) {
            QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);
            childItem->setForeground(0, brush);
            childItem->setText(0, QString("Ended: %1").arg(show.ended));
        }
        // Classification
        {
            QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);
            childItem->setForeground(0, brush);
            childItem->setText(0, QString("Classification: %1").arg(show.classification));
        }
        // Genres
        if (!show.genres.empty()) {
            QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);
            childItem->setForeground(0, brush);
            childItem->setText(0, QString("Genres: %1").arg(show.genres.join(", ")));
        }

        displayedShowCounter++;
    } // foreach()

    if (m_searchResults.count() != 0) {
        ui.cbFilterResults->setEnabled(true);
        ui.lblDisplayed->setEnabled(true);
        if (displayedShowCounter != 0) {
            ui.treeSearchResults->setEnabled(true);
            ui.treeSearchResults->setRootIsDecorated(true);
        } else {
            ui.treeSearchResults->setEnabled(false);
            QTreeWidgetItem *item = new QTreeWidgetItem();
            item->setText(0, tr("Only ended shows were found!"));
            ui.treeSearchResults->addTopLevelItem(item);
            ui.treeSearchResults->setRootIsDecorated(false);
        }
    } else {
        ui.treeSearchResults->setEnabled(false);
        ui.cbFilterResults->setEnabled(false);
        ui.lblDisplayed->setEnabled(false);

        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, tr("No results found!"));
        ui.treeSearchResults->addTopLevelItem(item);
        ui.treeSearchResults->setRootIsDecorated(false);
    }

    ui.treeSearchResults->resizeColumnToContents(0);

    ui.lblDisplayed->setText(QString("Displayed: %1/%2")
                             .arg(displayedShowCounter)
                             .arg(m_searchResults.count()));
} // displaySearchResults()


} // namespace Settings


// EOF - vim:ts=4:sw=4:et:
