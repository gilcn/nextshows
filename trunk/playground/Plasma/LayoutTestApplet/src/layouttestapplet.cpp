/*
** Copyright (C) 2008 Gilles CHAUVIN <gcnweb+kde@gmail.com>
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
#include "layouttestapplet.h"

// Plasma
#include <Plasma/Label>
#include <Plasma/PushButton>

// KDE
#include <KDE/KLineEdit>

// Qt
#include <QtGui/QLabel>
#include <QtGui/QIntValidator>


/*
** Public
*/
LayoutTestApplet::LayoutTestApplet(QObject *parent, const QVariantList &args)
    : Plasma::Applet(parent, args)
    , m_layoutMain(0), m_layoutContent(0)
{
    kDebug();

    Plasma::Applet::setAspectRatioMode(Plasma::IgnoreAspectRatio);

//    resize(290, 360);
} // ctor()

LayoutTestApplet::~LayoutTestApplet()
{
    kDebug();
} // dtor()


/*
** Protected
*/
void LayoutTestApplet::init()
{
    kDebug();

    m_layoutMain     = new QGraphicsLinearLayout(Qt::Vertical);
    m_layoutControls = new QGraphicsGridLayout();
    m_layoutContent  = new QGraphicsGridLayout();

    Plasma::Label *label = new Plasma::Label();
    label->setText(i18n("Lines:"));
    m_layoutControls->addItem(label, 0, 0);

    m_ledit = new Plasma::LineEdit();
    m_ledit->setText("10");
    KLineEdit *nledit = m_ledit->nativeWidget();
    nledit->setValidator(new QIntValidator(0, 30, this));
    m_layoutControls->addItem(m_ledit, 0, 1);

    Plasma::PushButton *button = new Plasma::PushButton();
    button->setText(i18n("Refresh..."));
    connect(button, SIGNAL(clicked()), this, SLOT(refresh()));
    m_layoutControls->addItem(button, 1, 0, 1, 2);

    m_layoutMain->addItem(m_layoutControls);
    m_layoutMain->addItem(m_layoutContent);

    Plasma::Applet::setLayout(m_layoutMain);

    feedContent();
} // init()

void LayoutTestApplet::feedContent()
{
    kDebug();

    // Do some cleanup
    for (int i=m_layoutContent->count()-1; i>=0; --i) {
        QGraphicsLayoutItem *item = m_layoutContent->itemAt(i);
        m_layoutContent->removeAt(i);
        delete item;
    }

    // Display some content
    for (int col=0; col<2; ++col) {
        for (int row=0; row<m_ledit->text().toInt(); ++row) {
            Plasma::Label *label = new Plasma::Label();
            label->setText(QString("Label_%1%2")
                           .arg(QLatin1Char(0x41+col))
                           .arg(row));
            QLabel *nlabel = label->nativeWidget();
            switch(col) {
            case 0:
                nlabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
                break;
            case 1:
                nlabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
                break;
            }
            m_layoutContent->addItem(label, row, col);
        }
    }
} // feedContent()


/*
** Private Q_SLOTS
*/
void LayoutTestApplet::refresh()
{
    kDebug();

    feedContent();
} // refresh()


#include "layouttestapplet.moc"
