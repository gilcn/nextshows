/*
 *   Copyright 2008 Gilles CHAUVIN <gcnweb@gmail.com>
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

#include "animatedimage.h"

#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtGui/QPainter>


AnimatedImage::AnimatedImage(QObject *parent, const QString &fileName)
    : QObject(parent)
    , m_timer(new QTimer())
{
    m_timer->setInterval(50);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(sendPixmap()));

    if (!fileName.isEmpty())
        setPicture(fileName);
}

AnimatedImage::~AnimatedImage()
{
    delete m_timer;
}

bool AnimatedImage::setPicture(const QString &fileName)
{
    if (!QFile::exists(fileName)) {
        if (fileName.isEmpty()) {
            qCritical() << tr("No filename given!");
        } else {
            qCritical(tr("File %1 not found!").arg(fileName).toLocal8Bit().constData());
        }
        return false;
    }

    if (!m_picList.isEmpty())
        m_picList.clear();

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
}

void AnimatedImage::start()
{
    if(m_picList.isEmpty())
        return;

    sendPixmap();
    m_timer->start();
}

void AnimatedImage::stop()
{
    m_timer->stop();
    m_currentFrame=0;
}

bool AnimatedImage::isActive()
{
    return m_timer->isActive();
}

void AnimatedImage::sendPixmap()
{
    m_currentFrame++;
    if (m_currentFrame >= m_picList.count())
        m_currentFrame=0;
    emit newFrame(m_picList.value(m_currentFrame));
}
