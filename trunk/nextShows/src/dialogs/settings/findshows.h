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
#include "libs/animatedimage.h"
#include "libs/tvrageprovider.h"
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

private Q_SLOTS:
    void on_btnLookup_clicked();
    void on_cbHideEndedShows_stateChanged(int);
    void newImageFrame(const QPixmap &);
    void searchResultsReady(const QList<AbstractProvider::SearchResults_t> &);

private:
    void displaySearchResults();
    void updateSearchResultsWidgets();

    Ui::FindShows ui;

    AnimatedImage *m_animatedImage;
    AbstractProvider *m_tvrage;

    bool m_filterResults;
    int m_displayedShowCount;
    QList<AbstractProvider::SearchResults_t> m_searchResults;
    QList<AbstractProvider::SearchResults_t> m_trackedShows;
};

} // namespace Settings


#endif // __SETTINGS_FINDSHOWS_H__


// EOF - vim:ts=4:sw=4:et:
