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

// Qt
#include <QtGui/QLabel>


/*
** Public
*/
LayoutTestApplet::LayoutTestApplet(QObject *parent, const QVariantList &args)
    : Plasma::Applet(parent, args)
    , m_mainLayout(0), m_btnsLayout(0), m_cellLayout(0)
{
    kDebug();

    m_maxCols  = 4;
    m_maxLines = 10;

    Plasma::Applet::setAspectRatioMode(Plasma::IgnoreAspectRatio);

    resize(290, 360);
} // ctor()

LayoutTestApplet::~LayoutTestApplet()
{
    kDebug();
} // dtor()

void LayoutTestApplet::init()
{
    kDebug();

    // Buttons
    m_btnsLayout = new QGraphicsGridLayout();

    Plasma::PushButton *btnAddLine = new Plasma::PushButton();
    btnAddLine->setText(i18n("Add line"));
    connect(btnAddLine, SIGNAL(clicked()), this, SLOT(addLine()));
    m_btnsLayout->addItem(btnAddLine, 0, 0);

    Plasma::PushButton *btnRemoveRandomLine = new Plasma::PushButton();
    btnRemoveRandomLine->setText(i18n("Remove random line"));
    connect(btnRemoveRandomLine, SIGNAL(clicked()), this, SLOT(removeRandomLine()));
    m_btnsLayout->addItem(btnRemoveRandomLine, 1, 0);

    Plasma::PushButton *btnRemoveRandomCell = new Plasma::PushButton();
    btnRemoveRandomCell->setText(i18n("Remove random cell"));
    connect(btnRemoveRandomCell, SIGNAL(clicked()), this, SLOT(removeRandomCell()));
    m_btnsLayout->addItem(btnRemoveRandomCell, 2, 0);


    // Cells
    m_cellLayout = new QGraphicsGridLayout();

    // Display content
    for (int i=0; i<m_maxCols; ++i) {
        for (int j=0; j<m_maxLines; ++j) {
            Plasma::Label *label = new Plasma::Label();
            label->setText(QString("Cell_%1%2").arg(QLatin1Char(0x41+i)).arg(j));
            // Text alignment
            QLabel *lbl = label->nativeWidget();
            if (i == 0) {
                lbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            }
            else if (i == m_maxCols-1) {
                lbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
            }
            else {
                lbl->setAlignment(Qt::AlignCenter);
            }
            m_cellLayout->addItem(label, j, i);
        }
    }


    // Main
    m_mainLayout = new QGraphicsLinearLayout(Qt::Vertical);
    Plasma::Applet::setLayout(m_mainLayout);

    m_mainLayout->addItem(m_btnsLayout);
    m_mainLayout->addItem(m_cellLayout);
} // init()


/*
** Private Q_SLOTS
*/
void LayoutTestApplet::addLine()
{
    kDebug();
} // addLine();

void LayoutTestApplet::removeRandomCell()
{
    kDebug();
} // removeRandomCell()

void LayoutTestApplet::removeRandomLine()
{
    kDebug();
} // removeRandomLine()


#include "layouttestapplet.moc"
