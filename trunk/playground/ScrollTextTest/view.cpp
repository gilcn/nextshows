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
#include "view.h"
// QtCore
#include <QtCore/QDebug>
// QtGui
#include <QtGui/QLabel>


/*
** public:
*/
View::View(QWidget *parent)
    : QGraphicsView(parent)
    , m_timer(0)
    , m_scene(new QGraphicsScene())
    , m_gridLayout(new QGridLayout())
    , m_nextGridLayoutRow(0)
{
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    // Transparent background
    QPalette pal(palette());
    QColor color(pal.color(QPalette::Active, backgroundRole()));
    color.setAlpha(0);
    pal.setColor(QPalette::Active, backgroundRole(), color);
    pal.setColor(QPalette::Inactive, backgroundRole(), color);
    setPalette(pal);

    ScrollWidget *widget = new ScrollWidget();
    widget->setAttribute(Qt::WA_NoSystemBackground);
    widget->setLayout(m_gridLayout);

    m_scrollWidget = m_scene->addWidget(widget);
    m_scrollWidget->setPos(999999, 999999); // Force the ScrollWidget offscreen

    setScene(m_scene);

    connect(widget, SIGNAL(widgetEntered()), this, SLOT(pause()));
    connect(widget, SIGNAL(widgetLeaved()), this, SLOT(unpause()));
} // ctor()

View::~View()
{
} // dtor()

void View::startScrolling(const int &interval)
{
    if (m_timer) {
        return;
    }

    m_timer = new QTimer(this);
    m_timer->setInterval(interval);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(moveText()));
    m_timer->start();
} // startScroll()

void View::stopScrolling()
{
    if (m_timer) {
        m_timer->stop();
        disconnect(m_timer, 0, 0, 0);
    }
    delete m_timer;
    m_timer = 0;
} // stopScrolling

void View::addCreditSection(const QString &text, const int &fontSize)
{
    int topMargin = (!m_nextGridLayoutRow) ? 0 : 60;

    QLabel *label = new QLabel(text);

    QFont font(label->font());
    font.setBold(true);
    font.setPointSize(fontSize);
    label->setFont(font);

    label->setContentsMargins(0, topMargin, 0, 5);

    m_gridLayout->addWidget(label, m_nextGridLayoutRow, 0, 1, 3, Qt::AlignHCenter | Qt::AlignTop);

    m_nextGridLayoutRow++;
} // addCreditSection()

void View::addCredit(const QString &country, const QByteArray &name, const QString &link, const QString &task)
{
    int topMargin = (!m_nextGridLayoutRow) ? 0 : 5;

    // Country
    {
        QLabel *label = new QLabel(country);
        label->setContentsMargins(0, topMargin, 0, 5);
        m_gridLayout->addWidget(label, m_nextGridLayoutRow, 0);
    }
    // Name
    {
        QLabel *label = new QLabel();
        label->setContentsMargins(0, topMargin, 0, 5);
        label->setOpenExternalLinks(true);

        QString text = QString("<b>%1</b>").arg(QString::fromUtf8(name.data()));
        if (!link.isEmpty()) {
            if (link.startsWith("http://")) {
                text += QString("<br /><a href=\"%1\" style=\"text-decoration: none;\">%1</a>").arg(link);
            } else {
                // Assume link is an e-mail address
                text += QString("<br /><a href=\"mailto:%1\" style=\"text-decoration: none;\">%1</a>").arg(link);
            }
        }
        label->setText(text);

        m_gridLayout->addWidget(label, m_nextGridLayoutRow, 1);
    }
    // Task
    {
        QLabel *label = new QLabel(task);
        label->setContentsMargins(0, topMargin, 0, 5);
        m_gridLayout->addWidget(label, m_nextGridLayoutRow, 2);
    }

    m_nextGridLayoutRow++;
} // addCredit()


/*
** protected:
*/
void View::resizeEvent(QResizeEvent *event)
{
    m_scene->setSceneRect(0, 0, event->size().width(), event->size().height());
    setSceneRect(m_scene->sceneRect());

    setMinimumSize(m_scrollWidget->size().width(), 0);

    positionScrollWidget();
} // resizeEvent()


/*
** private Q_SLOTS:
*/
void View::moveText()
{
    positionScrollWidget(-1);

    // Reset scroller
    if (m_scrollWidget->pos().y() < -m_scrollWidget->size().height()) {
        m_scrollWidget->setPos(m_scrollWidget->pos().x(), size().height());
    }
} // timerEvent()

void View::pause()
{
    qDebug() << "Scroller paused";
    if (m_timer) {
        m_timer->stop();
    }
} // pause()

void View::unpause()
{
    qDebug() << "Scroller unpaused";
    if (m_timer) {
        m_timer->start();
    }
} // unpause()


/*
** private:
*/
void View::positionScrollWidget(const int &yStep)
{
    int xPos = (size().width() / 2) - (m_scrollWidget->size().width() / 2);

    int yPos = m_scrollWidget->pos().y();
    if (yPos > size().height()) {
        yPos = size().height();
    } else {
        yPos = m_scrollWidget->pos().y() - qAbs(yStep);
    }

    m_scrollWidget->setPos(xPos, yPos);
} // positionScrollWidget();

// EOF - vim:ts=4:sw=4:et:
