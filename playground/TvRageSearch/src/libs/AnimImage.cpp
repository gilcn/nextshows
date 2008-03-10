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

#include "AnimImage.h"

#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtGui/QPainter>


AnimImage::AnimImage(QObject *parent, const QString &fileName)
    : QObject(parent)
    , m_timer(new QTimer())
{
    if (!setPicture(fileName))
        return;

    m_timer->setInterval(50);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(sendPixmap()));
}

AnimImage::~AnimImage()
{
    delete m_timer;
}

bool AnimImage::setPicture(const QString &fileName)
{
    if (!QFile::exists(fileName)) {
        qCritical("File %s not found!", qPrintable(fileName));
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
        p.drawPixmap(QPoint(0,0),
                     animatedPic,
                     QRect(0,i*picSize,picSize,picSize));
        m_picList.append(pic);
    }

    return true;
}

void AnimImage::start()
{
    if(m_picList.isEmpty())
        return;

    sendPixmap();
    m_timer->start();
}

void AnimImage::stop()
{
    m_timer->stop();
    m_currentFrame=0;
}

bool AnimImage::isActive()
{
    return m_timer->isActive();
}

void AnimImage::sendPixmap()
{
    m_currentFrame++;
    if (m_currentFrame >= m_picList.count())
        m_currentFrame=0;
    emit newFrame(m_picList.value(m_currentFrame));
}
