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

/*
** Some parts were borrowed from KDE's KLineEdit widget available here:
** http://websvn.kde.org/trunk/KDE/kdelibs/kdeui/widgets/
*/

#ifndef __WIDGET_NSLINEEDIT_H__
#define __WIDGET_NSLINEEDIT_H__


// QtGui
#include <QtGui/QIcon>
#include <QtGui/QLineEdit>


class NSLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    NSLineEdit(QWidget *parent = 0);
    NSLineEdit(const QString &contents, QWidget *parent = 0);
    ~NSLineEdit();

    void setClickMessage(const QString &clickMessage);
    QString clickMessage() const;

    void setIcon(const QIcon &icon); // FIXME (Need Qt4.5)!!!
    QIcon icon() const;


protected:
    void paintEvent(QPaintEvent *event);


private:
    QString  m_clickMessage;
    QIcon    m_icon;
};

#endif // __WIDGET_NSLINEEDIT_H__


// EOF - vim:ts=4:sw=4:et:
