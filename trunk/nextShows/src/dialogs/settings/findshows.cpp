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
#include "findshows.h"
// QtCore
#include <QtCore/QDebug>
#include <QtCore/QFile>


namespace Settings
{

/*
** public:
*/
FindShows::FindShows(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    // Category title
    setWindowTitle(tr("Find Shows"));
    // Category icon
    setWindowIcon(QIcon(":/pixmaps/prefs/television.png"));


    ui.leSearch->setClickMessage(tr("Enter a show name"));
//    ui.leSearch->setIcon(QIcon(":/pixmaps/prefs/progress_idle.png"));


    m_animatedImage = new AnimatedImage(this, ":/pixmaps/prefs/progress_working.png");
    connect(m_animatedImage, SIGNAL(newFrame(const QPixmap &)),
            this, SLOT(newImageFrame(const QPixmap &)));

//    m_data = new GetData(this);
    m_tvrage = new TvRageProvider(this);
    connect(m_tvrage, SIGNAL(searchShowReady(QVariantList)),
            this, SLOT(displaySearchResults(const QVariantList &)));
} // ctor()

FindShows::~FindShows()
{
//    delete m_data;
    delete m_tvrage;
    delete m_animatedImage;
} // dtor()


/*
** private Q_SLOTS:
*/
void FindShows::on_btnLookup_clicked()
{
    if (ui.leSearch->text().isEmpty()) {
        return;
    }

    ui.btnLookup->setEnabled(false);
    m_animatedImage->start();
    m_tvrage->searchShow(ui.leSearch->text());
} // on_btnLookup_clicked()

void FindShows::newImageFrame(const QPixmap &pixmap)
{
    ui.btnLookup->setIcon(pixmap);
} // newImageFrame()

void FindShows::displaySearchResults(const QVariantList &shows)
{
    m_animatedImage->stop();
    ui.btnLookup->setEnabled(true);

    ui.listWidget->clear();
    foreach(QVariant show, shows) {
        QVariantMap map(show.toMap());
        QListWidgetItem *item = new QListWidgetItem();
        QString flagFile = QString(":/pixmaps/flags/%1.gif").arg(map["country"].toString().toLower());
        if (QFile::exists(flagFile)) {
            item->setIcon(QIcon(flagFile));
        } else {
            item->setIcon(QIcon(":/pixmaps/flags/unknown.gif"));
        }
        item->setText(map["name"].toString());
        if (map["ended"].toInt() == 0) {
            QFont font(item->font());
            font.setBold(true);
            item->setFont(font);
        }
        else {
            QBrush brush(item->foreground());
            brush.setColor(Qt::gray);
            item->setForeground(brush);
        }
        ui.listWidget->addItem(item);
    }
} // displaySearchResults()


} // namespace Settings


// EOF - vim:ts=4:sw=4:et:
