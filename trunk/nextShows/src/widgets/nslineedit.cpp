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
#include "nslineedit.h"
// QtCore
#include <QtCore/QDebug>
// QtGui
#include <QtGui/QFont>
#include <QtGui/QPainter>
#include <QtGui/QPalette>
#include <QtGui/QStyleOptionFrameV2>


/*
** public:
*/
NSLineEdit::NSLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
} // ctor()

NSLineEdit::NSLineEdit(const QString &contents, QWidget *parent)
    : QLineEdit(contents, parent)
{
} // ctor()

NSLineEdit::~NSLineEdit()
{
} // dtor()

void NSLineEdit::setClickMessage(const QString &clickMessage)
{
    m_clickMessage = clickMessage;
} // setClickMessage()

QString NSLineEdit::clickMessage() const
{
    return m_clickMessage;
} // clickMessage()

void NSLineEdit::setIcon(const QIcon &icon)
{
    m_icon = icon;
    update(); // Repaint
} // setIcon()

QIcon NSLineEdit::icon() const
{
    return m_icon;
} // icon()


/*
** protected:
*/
void NSLineEdit::paintEvent(QPaintEvent *event)
{
    QLineEdit::paintEvent(event);

    // Content rect
    QStyleOptionFrameV2 opt;
    initStyleOption(&opt);
    QRect cr = style()->subElementRect(QStyle::SE_LineEditContents, &opt, this);

    QPainter p(this);

    // Do we need to display an icon ?
    if (!m_icon.isNull()) {
        m_icon.paint(&p, cr, Qt::AlignLeft | Qt::AlignVCenter);
    }

    if (hasFocus() || !text().isEmpty() || m_clickMessage.isEmpty()) {
        return;
    }

    // Font
    QFont f(font());
    f.setItalic(true);
    p.setFont(f);

    // Pen
    p.setPen(palette().color(QPalette::Disabled, QPalette::Text));

    // Text Position
    cr.setLeft(cr.left() + 3);
    cr.setRight(cr.right() - 3);

    // Draw
    p.drawText(cr, Qt::AlignLeft|Qt::AlignVCenter, m_clickMessage);
} // paintEvent()


// EOF - vim:ts=4:sw=4:et:
