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


#include "view.h"


/*****************************************************************************
** View
*****************************************************************************/
/*
** public:
*/
View::View(QWidget *parent)
    : QGraphicsView(parent)
    , m_timer(new QTimer(this))
    , m_scene(new QGraphicsScene())
    , m_gridLayout(new QGridLayout())
{
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    ScrollWidget *widget = new ScrollWidget();
//    widget->setAttribute(Qt::WA_NoSystemBackground);
//    setAttribute(Qt::WA_NoSystemBackground);
//    qDebug() << testAttribute(Qt::WA_NoSystemBackground);
    widget->setLayout(m_gridLayout);

    m_scrollWidget = m_scene->addWidget(widget);

    setScene(m_scene);

    m_timer->setInterval(30);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(moveText()));

    connect(widget, SIGNAL(widgetEntered()), this, SLOT(pause()));
    connect(widget, SIGNAL(widgetLeaved()), this, SLOT(unpause()));
} // ctor()

View::~View()
{
} // dtor()

void View::startScrolling()
{
    qDebug() << size() << Q_FUNC_INFO;
    m_timer->start();
} // startScroll()

void View::addCreditSection(const QString &text, const int &fontSize)
{
    QLabel *label = new QLabel(text);
    QFont font(label->font());
    font.setBold(true);
    font.setPointSize(fontSize);
    label->setFont(font);
    label->setContentsMargins(0, 60, 0, 5);
    m_gridLayout->addWidget(label, m_gridLayout->rowCount(), 0, 1, 3, Qt::AlignHCenter | Qt::AlignTop);
} // addCreditSection()

void View::addCredit(const QString &country, const QByteArray &name, const QString &link, const QString &task)
{
    int nextRow = m_gridLayout->rowCount();

    // Country
    {
        QLabel *label = new QLabel(country);
        label->setContentsMargins(0, 5, 0, 5);
        m_gridLayout->addWidget(label, nextRow, 0);
    }
    // Name
    {
        QLabel *label = new QLabel();
        label->setContentsMargins(0, 5, 0, 5);
        label->setOpenExternalLinks(true);

        QFont font = label->font();
        font.setBold(true);
        label->setFont(font);

        QString text(QString::fromUtf8(name.data()));
        if (!link.isEmpty()) {
            if (link.contains(QRegExp("^http://.*"))) {
                text += QString("<br /><a href=\"%1\" style=\"text-decoration: none;\">%1</a>").arg(link);
            } else {
                // Consider link is an e-mail address
                text += QString("<br /><a href=\"mailto:%1\" style=\"text-decoration: none;\">%1</a>").arg(link);
            }
        }
        label->setText(text);

        m_gridLayout->addWidget(label, nextRow, 1);
    }
    // Task
    {
        QLabel *label = new QLabel(task);
        label->setContentsMargins(0, 5, 0, 5);
        m_gridLayout->addWidget(label, nextRow, 2);
    }
} // addCredit()


/*
** protected:
*/
void View::resizeEvent(QResizeEvent *event)
{
    m_scene->setSceneRect(0, 0, event->size().width(), event->size().height());
    setSceneRect(m_scene->sceneRect());
    qDebug();
    qDebug() << m_scene->sceneRect() << "m_scene->sceneRect()";
    qDebug() << sceneRect() << "sceneRect()";
    qDebug() << m_scrollWidget->pos() << " m_scrollWidget->pos()";
    qDebug() << size() << "size()";
    qDebug() << m_scrollWidget->size() << "m_scrollWidget->size()";

    int yPos = m_scrollWidget->pos().y();
    if (yPos > size().height()) {
        yPos = size().height();
    }
    int ww = m_scrollWidget->size().width() / 2;
    int vw = size().width() / 2;
    m_scrollWidget->setPos(vw-ww, yPos);
    setMinimumSize(m_scrollWidget->size().width(), 0);
} // resizeEvent()


/*
** private Q_SLOTS:
*/
void View::moveText()
{
    QPointF oldPos = m_scrollWidget->pos();
    QPointF newPos(oldPos.x(), oldPos.y()-1);
    m_scrollWidget->setPos(newPos);

//    qDebug() << m_scrollWidget->pos() << m_scrollWidget->size();
//    qDebug() << -m_scrollWidget->size().height();

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


// EOF - vim:ts=4:sw=4:et:
