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
// QtGui
#include <QtGui/QFont>
#include <QtGui/QPainter>
#include <QtGui/QPalette>
#include <QtGui/QStyleOptionFrame>

/*
** public:
*/
NSLineEdit::NSLineEdit(QWidget *parent, const QString &clickMessage)
    : QLineEdit(parent)
{
    setClickMessage(clickMessage);
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

/*
** protected:
*/
void NSLineEdit::paintEvent(QPaintEvent *event)
{
    QLineEdit::paintEvent(event);

    if (hasFocus() || !text().isEmpty() || m_clickMessage.isEmpty()) {
        return;
    }

    QPainter p(this);

    // Font
    QFont f(font());
    f.setItalic(true);
    p.setFont(f);

    // Pen
    p.setPen(palette().color(QPalette::Disabled, QPalette::Text));

    // Position
    QStyleOptionFrame opt;
    initStyleOption(&opt);
    QRect cr = style()->subElementRect(QStyle::SE_LineEditContents, &opt, this);
    cr.setLeft(cr.left() + 2);
    cr.setRight(cr.right() - 2);

    // Draw
    p.drawText(cr, Qt::AlignLeft|Qt::AlignVCenter, m_clickMessage);
} // paintEvent()


// EOF - vim:ts=4:sw=4:et:
