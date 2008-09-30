/*
** Copyright (C) 2008 Gilles CHAUVIN <gcnweb+kde@gmail.com>
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
#include "gmailnotifierdialog.h"

// Plasma
#include <Plasma/Dialog>

// KDE
#include <KDE/KDebug>


/*
** Public
*/
GmailNotifierDialog::GmailNotifierDialog(DialogArea area, QObject *parent)
    : QObject(parent)
    , m_widget(0), m_lblLogo(0), m_layoutMain(0), m_layoutMails(0)
    , m_displayLogo(true)
{
    kDebug();
    buildDialog(area);
} // ctor()

GmailNotifierDialog::~GmailNotifierDialog()
{
    kDebug();
} // dtor()

QWidget * GmailNotifierDialog::widget()
{
    kDebug();
    return m_widget;
} // widget()

void GmailNotifierDialog::show()
{
    kDebug();
    m_widget->show();
} // show()

void GmailNotifierDialog::hide()
{
    kDebug();
    m_widget->hide();
} // hide()

void GmailNotifierDialog::setDisplayLogo(const bool &display)
{
    m_displayLogo = display;
    if (!m_lblLogo) {
        return;
    }

    if(display) {
        m_lblLogo->show();
    } else {
        m_lblLogo->hide();
    }
} // setDisplayLogo()

void GmailNotifierDialog::setAccounts(const QList<QMap<QString, QString> > &accounts)
{
    kDebug();

    // Remove any existing labels
    QLayoutItem *item;
    while ((item = m_layoutMails->takeAt(0)) != 0) {
        delete item->widget();
        delete item;
    }

    // Populate...
    QList<QMap<QString, QString> >::ConstIterator it;
    int row = 0;
    for (it = accounts.constBegin(); it != accounts.constEnd(); ++it) {
        QString label = (it->value("Label").isEmpty()) ? "inbox" : it->value("Label");
        QString display;
        if (!it->value("Display").isEmpty()) {
            display = it->value("Display");
        } else {
            display = QString("%1/%2").arg(it->value("Login")).arg(label);
        }

        QString loginNLabel = QString("%1:%2").arg(it->value("Login")).arg(label);

        QLabel *lblAccount = new QLabel(display);
        lblAccount->setObjectName(QString("lblAccount_%1").arg(loginNLabel));
        m_layoutMails->addWidget(lblAccount, row, 0);

        QLabel *lblMailCount = new QLabel("---");
        lblMailCount->setObjectName(QString("lblMailCount_%1").arg(loginNLabel));
        m_layoutMails->addWidget(lblMailCount, row, 1);

        ++row;
    }
} //setAccounts()

void GmailNotifierDialog::updateMailCount(const QString &source, const Plasma::DataEngine::Data &data)
{
    kDebug();

    QLabel *label = m_widget->findChild<QLabel *>("lblMailCount_"+source);
    QString content;
    if (!data["error"].toString().isEmpty()) {
        content = "Err.";
    } else {
        content = data["fullcount"].toString();
    }
    label->setText(content);
} // updateMailCount()


/*
** Private
*/
void GmailNotifierDialog::buildDialog(DialogArea area)
{
    kDebug();
    switch (area) {
    case DesktopArea:
        m_widget = new QWidget();
//        m_widget->setBackgroundRole(QPalette::Window);
        m_widget->setAttribute(Qt::WA_NoSystemBackground);
        break;
    case PanelArea:
        m_widget = new Plasma::Dialog();
        m_widget->setWindowFlags(Qt::Popup);
        break;
    }

    // Use white colored text
    QPalette palette(m_widget->palette());
    QBrush brush(QColor(Qt::white));
    palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
    palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
    m_widget->setPalette(palette);

    // Main layout
    m_layoutMain = new QVBoxLayout(m_widget);
    m_layoutMain->setSpacing(0);
    m_layoutMain->setMargin(10);

    if(m_displayLogo) {
        m_lblLogo = new QLabel(m_widget);
        m_lblLogo->setPixmap(QPixmap(":/images/gmail_logo.png"));
        m_lblLogo->setAlignment(Qt::AlignCenter);
        m_layoutMain->addWidget(m_lblLogo);
    }

    m_layoutMain->addSpacerItem(new QSpacerItem(0, 10, QSizePolicy::Expanding, QSizePolicy::Fixed));

    m_layoutMails = new QGridLayout();
    m_layoutMails->setSpacing(5);
    m_layoutMails->setHorizontalSpacing(30);
    m_layoutMails->setMargin(0);

    for (int i=0; i<=5; ++i) {
        QLabel *lblL = new QLabel(m_widget);
        QLabel *lblR = new QLabel(m_widget);

        //lblL->setText(QString("<font color=\"white\">account/label_%1</font>").arg(i));
        //lblR->setText(QString("<font color=\"white\">%1</font>").arg(random()%1000));
        lblL->setText(QString("account/label_%1").arg(i));
        lblR->setText(QString("%1").arg(random()%1000));

        m_layoutMails->addWidget(lblL, i, 0, Qt::AlignLeft | Qt::AlignVCenter);
        m_layoutMails->addWidget(lblR, i, 1, Qt::AlignRight | Qt::AlignVCenter);
    }

    m_layoutMain->addLayout(m_layoutMails);

    m_layoutMain->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
} // buildDialog()


#include "gmailnotifierdialog.moc"