/*
 *   Copyright (C) 2008 Gilles CHAUVIN <gcnweb+nextshows@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as
 *   published by the Free Software Foundation; either version 2,
 *   or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */


// Own
#include "animatedimage.h"
// QtCore
#include <QtCore/QDebug>
#include <QtCore/QFile>
// QtGui
#include <QtGui/QPainter>


// Default timer interval
#define TIMER_INTERVAL 50


/*
** public:
*/
AnimatedImage::AnimatedImage(QObject *parent, const QString &fileName)
    : QObject(parent)
    , m_timerId(0)
{
    if (!fileName.isEmpty()) {
        setPicture(fileName);
    }
} // ctor()

AnimatedImage::~AnimatedImage()
{
} // dtor()

bool AnimatedImage::setPicture(const QString &fileName)
{
    if (!QFile::exists(fileName)) {
        if (fileName.isEmpty()) {
            qCritical() << "No filename given!";
        } else {
            qCritical() << "File" << qPrintable(fileName) << "not found!";
        }
        return false;
    }

    if (!m_picList.isEmpty()) {
        m_picList.clear();
    }

    QPixmap animatedPic(fileName);
    int picSize        = qMin(animatedPic.width(), animatedPic.height());
    int numberOfFrames = animatedPic.height() / picSize;

    // Alpha Channel (weird results without this)
    QPixmap alphaChan(picSize, picSize);
    QPainter p(&alphaChan);
    p.fillRect(0,0,picSize,picSize,QBrush(QColor(Qt::black)));
    // Cut up image
    for (int i=0; i < numberOfFrames; ++i) {
        QPixmap pic(picSize, picSize);
        pic.setAlphaChannel(alphaChan);
        QPainter p(&pic);
        p.drawPixmap(QPoint(0, 0),
                     animatedPic,
                     QRect(0, i * picSize, picSize, picSize));
        m_picList.append(pic);
    }

    return true;
} // setPicture()

void AnimatedImage::start()
{
    // We just need 1 timer running
    if (isActive()) {
        qWarning() << "A timer is already active!";
        return;
    }
    if (m_picList.isEmpty()) {
        qWarning() << "Picture list is empty!";
        return;
    }

    sendPixmap();
    m_timerId = QObject::startTimer(TIMER_INTERVAL);
} // start()

void AnimatedImage::stop()
{
    QObject::killTimer(m_timerId);
    m_timerId = 0;
    m_currentFrame=0;
    emit newFrame(QPixmap());
} // stop()

bool AnimatedImage::isActive() const
{
    return m_timerId != 0;
} // isActive()


/*
** protected:
*/
void AnimatedImage::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    sendPixmap();
} // timerEvent()


/*
** private
*/
void AnimatedImage::sendPixmap()
{
    m_currentFrame++;
    if (m_currentFrame >= m_picList.count())
        m_currentFrame=0;
    emit newFrame(m_picList.value(m_currentFrame));
} // sendPixmap()

// EOF - vim:ts=4:sw=4:et:
