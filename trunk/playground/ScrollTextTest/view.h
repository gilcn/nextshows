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

#ifndef __VIEW_H__
#define __VIEW_H__


#include <QtGui>


class ScrollWidget : public QWidget
{
    Q_OBJECT

public:
    ScrollWidget(QWidget *parent = 0)
        : QWidget(parent) {}

Q_SIGNALS:
    void widgetEntered();
    void widgetLeaved();

protected:
    void enterEvent(QEvent *)
    {
        emit(widgetEntered());
    }
    void leaveEvent(QEvent *)
    {
        emit(widgetLeaved());
    }
};




class View : public QGraphicsView
{
    Q_OBJECT

public:
    View(QWidget *parent = 0);
    ~View();

    void addCreditSection(const QString &text,
                          const int &fontSize = 12);
    void addCredit(const QString &country,
                   const QByteArray &name,
                   const QString &link,
                   const QString &task);
    void startScrolling(const int &interval = 30);
    void stopScrolling();

protected:
    void resizeEvent(QResizeEvent *event);

private Q_SLOTS:
    void moveText();
    void pause();
    void unpause();

private:
    void positionScrollWidget();

    QTimer               *m_timer;
    QGraphicsScene       *m_scene;
    QGridLayout          *m_gridLayout;
    QGraphicsProxyWidget *m_scrollWidget;
};

#endif // __VIEW_H__


// EOF - vim:ts=4:sw=4:et:
