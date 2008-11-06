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


// Own
#include "nscreditscroller.h"
// QtCore
#include <QtCore/QDebug>
#include <QtCore/QFile>
// QtGui
#include <QtGui/QLabel>


/**************************************
** ScrollWidget
**************************************/
/*
** public:
*/
ScrollWidget::ScrollWidget(QWidget *parent)
    : QWidget(parent)
{
} // ctor()


/*
** protected:
*/
void ScrollWidget::enterEvent(QEvent * /*event*/)
{
    qDebug() << Q_FUNC_INFO;
    emit(widgetEntered());
} // enterEvent()

void ScrollWidget::leaveEvent(QEvent * /*event*/)
{
    qDebug() << Q_FUNC_INFO;
    emit(widgetLeaved());
} // leaveEvent()




/**************************************
** NSCreditScroller
**************************************/
/*
** public:
*/
NSCreditScroller::NSCreditScroller(QWidget *parent)
    : QGraphicsView(parent)
    , m_timer(0)
    , m_scene(new QGraphicsScene())
    , m_gridLayout(new QGridLayout())
    , m_nextGridLayoutRow(0)
{
//    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    // Store parent widget background color
    m_parentBgColor = parent->palette().color(QPalette::Active, QPalette::Window);

    // Transparent background
    QPalette pal(palette());
    pal.setColor(QPalette::Active, backgroundRole(), m_parentBgColor);
    pal.setColor(QPalette::Inactive, backgroundRole(), m_parentBgColor);
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

NSCreditScroller::~NSCreditScroller()
{
} // dtor()

void NSCreditScroller::startScrolling(const int &interval)
{
    if (m_timer) {
        return;
    }

    m_timer = new QTimer(this);
    m_timer->setInterval(interval);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(moveText()));
    m_timer->start();
} // startScroll()

void NSCreditScroller::stopScrolling()
{
    if (m_timer) {
        m_timer->stop();
        disconnect(m_timer, 0, 0, 0);
    }
    delete m_timer;
    m_timer = 0;
} // stopScrolling

void NSCreditScroller::addCreditSection(const QString &text, const int &fontSize)
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

void NSCreditScroller::addCredit(const QString &country, const QByteArray &name, const QString &link, const QString &task)
{
    int topMargin = (!m_nextGridLayoutRow) ? 0 : 5;

    // Country flag
    {
        QString flagFile = QString(":/pixmaps/flags/%1.gif").arg(country.toLower());
        if (QFile::exists(flagFile)) {
            QLabel *label = new QLabel();
            label->setPixmap(flagFile);
            label->setContentsMargins(0, topMargin, 15, 5);
            m_gridLayout->addWidget(label, m_nextGridLayoutRow, 0);
        }
    }
    // Name
    {
        QLabel *label = new QLabel();
        label->setContentsMargins(0, topMargin, 15, 5);
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
void NSCreditScroller::resizeEvent(QResizeEvent *event)
{
    m_scene->setSceneRect(0, 0, event->size().width(), event->size().height());
    setSceneRect(m_scene->sceneRect());

    setMinimumSize(m_scrollWidget->size().width(), 0);

    positionScrollWidget();
} // resizeEvent()

void NSCreditScroller::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);

    QPainter p(viewport());

    QColor colorStart(m_parentBgColor);
    QColor colorStop(m_parentBgColor);
    colorStart.setAlphaF(1.0);
    colorStop.setAlphaF(0);

    QLinearGradient topGradient(0, 0, 0, 20);
    topGradient.setColorAt(0, colorStart);
    topGradient.setColorAt(1, colorStop);
    QLinearGradient bottomGradient(0, size().height()-20, 0, size().height());
    bottomGradient.setColorAt(1, colorStart);
    bottomGradient.setColorAt(0, colorStop);

    p.fillRect(0, 0, size().width(), 20, topGradient);
    p.fillRect(0, size().height()-20, size().width(), size().height(), bottomGradient);
} // paintEvent()


/*
** private Q_SLOTS:
*/
void NSCreditScroller::moveText()
{
    positionScrollWidget(-1);

    // Reset scroller
    if (m_scrollWidget->pos().y() < -m_scrollWidget->size().height()) {
        m_scrollWidget->setPos(m_scrollWidget->pos().x(), size().height());
    }
} // timerEvent()

void NSCreditScroller::pause()
{
    qDebug() << "Scroller paused";
    if (m_timer) {
        m_timer->stop();
    }
} // pause()

void NSCreditScroller::unpause()
{
    qDebug() << "Scroller unpaused";
    if (m_timer) {
        m_timer->start();
    }
} // unpause()


/*
** private:
*/
void NSCreditScroller::positionScrollWidget(const int &yStep)
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
