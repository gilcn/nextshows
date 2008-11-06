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
    , m_displayedShowCount(0)
{
    ui.setupUi(this);
    m_filterResults = (ui.cbHideEndedShows->checkState() == Qt::Checked) ? true : false;

    // Category title
    setWindowTitle(tr("Find Shows"));
    // Category icon
    setWindowIcon(QIcon(":/pixmaps/prefs/television.png"));

    // Adjust Layout
    QLayout *widgetLayout = layout();
    QGridLayout *gridLayout = qobject_cast<QGridLayout *>(widgetLayout);
    if (gridLayout) {
        gridLayout->setColumnStretch(0, 20); // "Search Results" column
        gridLayout->setColumnStretch(2, 10); // "Tracked shows" column
    }

    ui.leSearch->setClickMessage(tr("Enter a show name"));
    // FIXME: Postponed until Qt4.5 is out
//    ui.leSearch->setIcon(QIcon(":/pixmaps/prefs/progress_idle.png"));

    m_animatedImage = new AnimatedImage(this,
                                        ":/pixmaps/prefs/progress_working.png",
                                        ":/pixmaps/prefs/progress_idle.png");
    connect(m_animatedImage, SIGNAL(newFrame(const QPixmap &)),
            this, SLOT(newImageFrame(const QPixmap &)));

    m_tvrage = new TvRageProvider(this);
    connect(m_tvrage, SIGNAL(searchResultsReady(QList<AbstractProvider::SearchResults_t>)),
            this, SLOT(searchResultsReady(const QList<AbstractProvider::SearchResults_t> &)));
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

void FindShows::on_cbHideEndedShows_stateChanged(int state)
{
    m_filterResults = (state == Qt::Checked) ? true : false;

    m_displayedShowCount = 0;

    QTreeWidgetItem *rootItem = ui.treeSearchResults->invisibleRootItem();
    QTreeWidgetItem *childItem;
    QFont font;
    for (int i=0; i < ui.treeSearchResults->topLevelItemCount(); ++i) {
        childItem = rootItem->child(i);
        childItem->setHidden(m_filterResults && m_searchResults[i].endedFlag);
        if (!childItem->isHidden()) {
            m_displayedShowCount++;
        }
        font = childItem->font(0);
        font.setBold(!m_filterResults && !m_searchResults[i].endedFlag);
        childItem->setFont(0, font);
    }

    updateSearchResultsWidgets();
} // on_cbHideEndedShows_stateChanged()

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

    m_displayedShowCount = 0;

    foreach(AbstractProvider::SearchResults_t show, m_searchResults) {
        QTreeWidgetItem *parentItem = new QTreeWidgetItem();

        QFont font(parentItem->font(0));
        QBrush brush(parentItem->foreground(0));

        // Set the proper flag
        QString flagFile = QString(":/pixmaps/flags/%1.gif").arg(show.country.toLower());
        if (QFile::exists(flagFile)) {
            parentItem->setIcon(0, QIcon(flagFile));
        } else {
            parentItem->setIcon(0, QIcon(":/pixmaps/flags/unknown.gif"));
        }
        parentItem->setToolTip(0, QString(tr("Country: %1")).arg(show.country.toUpper()));

        if (!show.endedFlag) {
            if (!m_filterResults) {
                font.setBold(true);
            }
        } else {
            font.setItalic(true);
            brush.setColor(Qt::darkGray);
        }

        parentItem->setFont(0, font);
        parentItem->setForeground(0, brush);
        parentItem->setText(0, show.name);

        ui.treeSearchResults->addTopLevelItem(parentItem);

        // Hide item if filter's on and the show has ended
        parentItem->setHidden(m_filterResults && show.endedFlag);
        if (!parentItem->isHidden()) {
            m_displayedShowCount++;
        }

#define ADD_CHILDITEM(section, value)                                         \
        {                                                                     \
            QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);     \
            if (show.endedFlag) {                                             \
                childItem->setFont(0, font);                                  \
            }                                                                 \
            childItem->setForeground(0, brush);                               \
            childItem->setText(0, QString("%1: %2").arg(section).arg(value)); \
        }

        // Seasons
        ADD_CHILDITEM(tr("Seasons"), show.seasons)
        // Status
        ADD_CHILDITEM(tr("Status"), show.status)
        // Started
        ADD_CHILDITEM(tr("Started"), show.started)
        // Ended
        if (show.ended != 0) {
            ADD_CHILDITEM(tr("Ended"), show.ended)
        }
        // Classification
        ADD_CHILDITEM(tr("Classification"), show.classification)
        // genres
        if (!show.genres.empty()) {
            ADD_CHILDITEM(tr("Genres"), show.genres.join(", "))
        }
    } // foreach()


    updateSearchResultsWidgets();
} // displaySearchResults()

void FindShows::updateSearchResultsWidgets()
{
    QPalette palette(ui.lblDisplayed->palette());
    QFont font(ui.lblDisplayed->font());

    if (m_searchResults.count() == 0) {
        ui.treeSearchResults->setEnabled(false);
        ui.cbHideEndedShows->setEnabled(false);
        palette.setColor(QPalette::WindowText, Qt::red);
        font.setBold(true);
        ui.lblDisplayed->setText(tr("Search returned nothing!"));
    } else {
        ui.cbHideEndedShows->setEnabled(true);
        if (m_displayedShowCount == 0) {
            ui.treeSearchResults->setEnabled(false);
            palette.setColor(QPalette::WindowText, Qt::red);
            font.setBold(true);
            ui.lblDisplayed->setText(tr("All results are filtered!"));
        } else {
            ui.treeSearchResults->setEnabled(true);
            palette.setColor(QPalette::WindowText, Qt::black);
            font.setBold(false);
            ui.lblDisplayed->setText(QString(tr("Displayed: %1/%2"))
                                     .arg(m_displayedShowCount)
                                     .arg(m_searchResults.count()));
        }
    }

    ui.lblDisplayed->setPalette(palette);
    ui.lblDisplayed->setFont(font);

    ui.treeSearchResults->resizeColumnToContents(0);
} // updateSearchResultsWidgets()

} // namespace Settings


// EOF - vim:ts=4:sw=4:et:
