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


AnimImage::AnimImage(QObject *parent)
    : QObject(parent)
    , m_timer(new QTimer())
{
    m_timer->setInterval(50);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
}


AnimImage::~AnimImage()
{
    delete m_timer;
}

void AnimImage::setIdlePic(const QString &fileName)
{
    m_idlePic = fileName;
}

void AnimImage::setAnimatedPic(const QString &fileName)
{
    m_animatedPic    = fileName;
    m_picHeight      = qMin(m_animatedPic.width(), m_animatedPic.height());
    m_numberOfFrames = m_animatedPic.height() / m_picHeight;
}

void AnimImage::start()
{
    m_timer->start();
}

void AnimImage::stop()
{
    m_timer->stop();
}

void AnimImage::nextFrame()
{
}
