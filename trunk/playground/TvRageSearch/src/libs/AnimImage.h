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

#ifndef __ANIMIMAGE_H__
#define __ANIMIMAGE_H__

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtGui/QPixmap>


class AnimImage : public QObject
{
    Q_OBJECT

public:
    AnimImage(QObject *parent=0);
    ~AnimImage();

    void setIdlePic(const QString &fileName);
    void setAnimatedPic(const QString &fileName);
    void start();
    void stop();

signals:
    void timeout();

private:
    QTimer  *m_timer;
    QPixmap  m_idlePic;
    QPixmap  m_animatedPic;
    uint     m_numberOfFrames;
    uint     m_currentFrame;
    uint     m_picHeight;

    void nextFrame();
};

#endif // __ANIMIMAGE_H__
