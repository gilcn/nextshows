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

#ifndef __WIDGET_NSCREDITSCROLLER_H__
#define __WIDGET_NSCREDITSCROLLER_H__


// QtCore
#include <QtCore/QDebug>
#include <QtCore/QTimer>
// QtGui
#include <QtGui/QGraphicsProxyWidget>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QWidget>


/**************************************
** ScrollWidget
**************************************/
class ScrollWidget : public QWidget
{
    Q_OBJECT

public:
    ScrollWidget(QWidget *parent = 0);

Q_SIGNALS:
    void widgetEntered();
    void widgetLeaved();

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
};




/**************************************
** NSCreditScroller
**************************************/
class NSCreditScroller : public QGraphicsView
{
    Q_OBJECT

public:
    NSCreditScroller(QWidget *parent = 0);
    ~NSCreditScroller();

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
    void paintEvent(QPaintEvent *event);

private Q_SLOTS:
    void moveText();
    void pause();
    void unpause();

private:
    void positionScrollWidget(const int &yStep = 0);

    QTimer               *m_timer;
    QGraphicsScene       *m_scene;
    QGridLayout          *m_gridLayout;
    QGraphicsProxyWidget *m_scrollWidget;

    QColor                m_parentBgColor;
    int                   m_nextGridLayoutRow;
};

#endif // __WIDGET_NSCREDITSCROLLER_H__


// EOF - vim:ts=4:sw=4:et:
