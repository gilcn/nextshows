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
#include "nextshows.h"
#include "libs/config.h"
#include "dialogs/settings.h"
// QtCore
#include <QtCore/QDebug>
#include <QtCore/QSettings>


namespace Dialogs
{

/*
** public:
*/
Settings::Settings(QWidget *parent)
    : QDialog(parent, Qt::Dialog)
    , m_wFindShows(new ::Settings::FindShows(this))
    , m_wOptions(new ::Settings::Options(this))
    , m_data(new DataProvider(this))
{
    qDebug() << Q_FUNC_INFO;

    // Default behavior / attributes
    QWidget::setAttribute(Qt::WA_DeleteOnClose);

    ui.setupUi(this);

    ui.wPanel->addWidget(m_wFindShows);
    ui.wCategories->addCategory(m_wFindShows->windowTitle(), m_wFindShows->windowIcon());
    ui.wPanel->addWidget(m_wOptions);
    ui.wCategories->addCategory(m_wOptions->windowTitle(), m_wOptions->windowIcon());

    setCategoryTitle(ui.wPanel->currentWidget()->windowTitle());

    setMinimumSize(sizeHint());

    connect(ui.wCategories, SIGNAL(categoryChanged(const int &)), this, SLOT(changePage(const int &)));

    // Restore settings
    readSettings();

    connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(acceptDialog()));
    connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(close()));
} // ctor()

Settings::~Settings()
{
    qDebug() << Q_FUNC_INFO;
    delete m_wFindShows;
    delete m_wOptions;
    delete m_data;
} // dtor()


/*
** private Q_SLOTS:
*/
void Settings::changePage(const int &id)
{
    qDebug() << Q_FUNC_INFO;
    ui.wPanel->setCurrentIndex(id);
    setCategoryTitle(ui.wPanel->currentWidget()->windowTitle());
} // changePage()

void Settings::acceptDialog()
{
    qDebug() << Q_FUNC_INFO;
    // Save settings
    saveSettings();

    QDialog::accept();
    emit settingsChanged();
} // acceptDialog()


/*
** private:
*/
void Settings::setCategoryTitle(const QString &title)
{
    qDebug() << Q_FUNC_INFO;
    ui.lblCategoryName->setText(title);
} // setCategoryTitle()

void Settings::readSettings()
{
    qDebug() << Q_FUNC_INFO;
    // Get tracked shows
    m_wFindShows->setTrackedShows(m_data->getTrackedShows());

    // Options
    m_wOptions->setBrowser(Config::getValue(Config::Browser).toString());
    m_wOptions->setCacheDuration(Config::getValue(Config::CacheDuration).toInt());
} // readSettings()

void Settings::saveSettings()
{
    qDebug() << Q_FUNC_INFO;
    // Save tracked shows
    m_data->setTrackedShows(m_wFindShows->getTrackedShows());

    Config::setValue(Config::Browser, m_wOptions->getBrowser());
    Config::setValue(Config::CacheDuration, m_wOptions->getCacheDuration());
} // saveSettings()

} // namespace Dialogs


// EOF - vim:ts=4:sw=4:et:
