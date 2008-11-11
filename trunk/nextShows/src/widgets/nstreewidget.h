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

#ifndef __WIDGET_NSTREEWIDGET_H__
#define __WIDGET_NSTREEWIDGET_H__


// QtGui
#include <QtGui/QTreeWidget>


class NSTreeWidget : public QTreeWidget
{
    Q_OBJECT

public:
    NSTreeWidget(QWidget *parent = 0);
    ~NSTreeWidget();

protected:
    void contextMenuEvent(QContextMenuEvent *event);

Q_SIGNALS:
    void addShowAction();
    void openUrlAction();

private:
    QMenu   *m_menu;
    QAction *m_actionTrack;
    QAction *m_actionOpenUrl;
    QAction *m_actionExpandAll;
    QAction *m_actionCollapseAll;
};

#endif // __WIDGET_NSTREEWIDGET_H__


// EOF - vim:ts=4:sw=4:et:
