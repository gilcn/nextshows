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

#ifndef __SETTINGS_FINDSHOWS_H__
#define __SETTINGS_FINDSHOWS_H__


// Own
#include "ui_findshows.h"
#include "nextshows.h"
#include "libs/animatedimage.h"
#include "libs/dataprovider.h"
// QtGui
#include <QtGui/QWidget>


namespace Settings
{

class FindShows : public QWidget
{
    Q_OBJECT

public:
    FindShows(QWidget *parent = 0);
    ~FindShows();

    NextShows::ShowInfosList getTrackedShows() const;
    void setTrackedShows(const NextShows::ShowInfosList &shows);

private Q_SLOTS:
    void on_btnLookup_clicked();
    void on_leSearch_textChanged(const QString &);
    void on_treeSearchResults_itemClicked(QTreeWidgetItem *, int);
    void on_treeSearchResults_itemSelectionChanged();
    void on_cbHideEndedShows_stateChanged(int);
    void on_btnAddShow_clicked();
    void on_lstTrackedShows_itemSelectionChanged();
    void on_btnRemoveShow_clicked();
    void newImageFrame(const QPixmap &);
    void searchResultsReady(NextShows::ShowInfosList, bool, QString);
    void on_treeSearchResults_addShowAction();
    void on_treeSearchResults_openUrlAction();

    void on_lstTrackedShows_removeShowAction();
    void on_lstTrackedShows_openUrlAction();

private:
    void displaySearchResults();
    // pos = selected item
    void displayTrackedShows(const int &pos = -1);
    void updateSearchResultsWidgets();
    // Insert user selected show into tracked shows list
    // Returns the show position within the list
    int insertIntoTrackedShowList(const NextShows::ShowInfos_t &);

    void addShowToTrackedList();
    void removeShowFromTrackedList();

    Ui::FindShows ui;

    AnimatedImage *m_animatedImage;
    DataProvider *m_data;

    bool m_filterResults;
    int m_displayedShowCount;
    NextShows::ShowInfosList m_searchResults;
    NextShows::ShowInfosList m_trackedShows;
};

} // namespace Settings


#endif // __SETTINGS_FINDSHOWS_H__


// EOF - vim:ts=4:sw=4:et:
