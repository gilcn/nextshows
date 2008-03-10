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

/*
 * This pretty basic library assumes that the resulting images are square
 * shaped. Improvements will be made later (if needed :).
 */

#ifndef __ANIMATEDIMAGE_H__
#define __ANIMATEDIMAGE_H__

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtGui/QPixmap>


class AnimatedImage : public QObject
{
    Q_OBJECT

public:
    AnimatedImage(QObject *parent=0, const QString &fileName="");
    ~AnimatedImage();

    bool setPicture(const QString &fileName);
    void start();       // Starts animation
    void stop();        // Stops animation
    bool isActive();

private:
    QTimer         *m_timer;
    int             m_currentFrame;
    QList<QPixmap>  m_picList;

signals:
    void newFrame(const QPixmap&);

private slots:
    void sendPixmap();
};


#endif // __ANIMATEDIMAGE_H__
