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


// Private
class AnimatedImage::Private
{
public:
    Private()
        : timer(new QTimer())
    {
        timer->setInterval(50);
    };
    ~Private()
    {
        delete timer;
    };
    QTimer         *timer;
    int             currentFrame;
    QList<QPixmap>  picList;
}; // Private


/*
** public:
*/
AnimatedImage::AnimatedImage(QObject *parent, const QString &fileName)
    : QObject(parent)
    , d(new Private())
{
    connect(d->timer, SIGNAL(timeout()), this, SLOT(sendPixmap()));

    if (!fileName.isEmpty())
        setPicture(fileName);
} // ctor()

AnimatedImage::~AnimatedImage()
{
    delete d;
} // dtor()

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

    if (!d->picList.isEmpty())
        d->picList.clear();

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
        d->picList.append(pic);
    }

    return true;
} // setPicture()

void AnimatedImage::start()
{
    if(d->picList.isEmpty())
        return;

    sendPixmap();
    d->timer->start();
} // start()

void AnimatedImage::stop()
{
    d->timer->stop();
    d->currentFrame=0;
} // stop()

bool AnimatedImage::isActive()
{
    return d->timer->isActive();
} // isActive()


/*
** private Q_SLOTS:
*/
void AnimatedImage::sendPixmap()
{
    d->currentFrame++;
    if (d->currentFrame >= d->picList.count())
        d->currentFrame=0;
    emit newFrame(d->picList.value(d->currentFrame));
} // sendPixmap()


// EOF - vim:ts=4:sw=4:et:
