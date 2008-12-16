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
#include "mainwindow.h"
#include "nextshows.h"
#include "libs/config.h"
// QtCore
#include <QtCore/QDebug>
#include <QtCore/QDate> // REMOVEME
#include <QtCore/QTime> // REMOVEME
// QtGui
#include <QtGui/QHeaderView>
// QtSql
#include <QtSql/QSqlRelationalTableModel>


/*
** public:
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_timer(new QBasicTimer)
    , m_dataProvider(new DataProvider(this))
    , m_dialogSettings(0) // Guarded by QPointer
    , m_dialogAbout(0)    // Guarded by QPointer
{
    qDebug() << Q_FUNC_INFO;

/*
    m_dataModel = new QStandardItemModel(this);
    m_dataModel->setColumnCount(5);
*/
    setupUi(this);

/*
    QStringList labels;
    labels << tr("Show name") << tr("Episode name")
           << tr("Season #") << tr("Episode #") << tr("Date");
    m_dataModel->setHorizontalHeaderLabels(labels);
//    showsTableView->setModel(m_dataModel);
    showsTableView->setModel(DbInterface::instance().readEpisodes());
    showsTableView->verticalHeader()->hide();
    showsTableView->horizontalHeader()->setResizeMode(QHeaderView::Interactive);
    showsTableView->horizontalHeader()->setStretchLastSection(true);
    showsTableView->horizontalHeader()->setCascadingSectionResizes(true);
    showsTableView->horizontalHeader()->setHighlightSections(true);
    showsTableView->horizontalHeader()->setMovable(true);

    srand(QTime::currentTime().toString("hhmmsszzz").toUInt());

    // Fill with random stuff
    for (int i=0; i<30; ++i) {
        m_dataModel->setItem(i, 0, new QStandardItem(QString("show_%1").arg(i)));
        m_dataModel->setItem(i, 1, new QStandardItem(QString("episode_%1").arg(i)));
        m_dataModel->setItem(i, 2, new QStandardItem(QString("%1").arg(rand()%10+1)));
        m_dataModel->setItem(i, 3, new QStandardItem(QString("%1").arg(rand()%24+1)));
        QDate rndDate = QDate::currentDate().addDays(i);
        m_dataModel->setItem(i, 4, new QStandardItem(rndDate.toString("yyyy/MM/dd")));
    }
*/

    setWindowTitle(QString("nextShows - v%1").arg(NEXTSHOWS_VERSION));
    statusBar()->showMessage(tr("nextShows started"), 1000*3);


    // TEMPORARY CODE FOR TESTING ////////////////////////////////////////////
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "NS_View");
    db.setDatabaseName("ns.db");
    db.open();
    QSqlRelationalTableModel *model = new QSqlRelationalTableModel(this, db);
    model->setTable("T_Episodes");
    model->setRelation(model->fieldIndex("shows_id"),
                       QSqlRelation("T_Shows", "idT_Shows", "ShowName"));
    model->setSort(model->fieldIndex("Date"), Qt::AscendingOrder);
    model->select();

    QStringList hideFields;
    hideFields << "idT_Episodes" << "ProdNumber" << "EpisodeCount"
               << "EpisodeUrl"   << "isSpecial";
    foreach (QString field, hideFields) {
        model->removeColumn(model->fieldIndex(field));
    }
    showsTableView->setModel(model);
//    qDebug() << "isSortingEnabled()" << showsTableView->isSortingEnabled();
    showsTableView->setSortingEnabled(true);
    //////////////////////////////////////////////////////////////////////////


    // Test alternate row colors
    QPalette pal(showsTableView->palette());
    pal.setColor(QPalette::Base, QColor("#C7FFFF"));
    pal.setColor(QPalette::AlternateBase, QColor("#E7FFFF"));
//    pal.setColor(QPalette::Highlight, QColor("#BEFFBE"));
    showsTableView->setPalette(pal);

    connect(actionSettings, SIGNAL(triggered()), this, SLOT(showSettings()));
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
    connect(actionQuit, SIGNAL(triggered()), this, SLOT(close()));

    // SysTray
    //SysTrayIcon *m_sysTrayIcon = new SysTrayIcon(this);
    //Q_UNUSED(m_sysTrayIcon)

    // Timer
    m_timer->start(500, this);
} // ctor()

MainWindow::~MainWindow()
{
    qDebug() << Q_FUNC_INFO;
//    delete m_dataModel;
//    delete m_sysTrayIcon;
    delete m_timer;
    delete m_dataProvider;

    QSqlDatabase::database("NS_View").close();
    QSqlDatabase::removeDatabase("NS_View");
} // dtor()


/*
** private Q_SLOTS:
*/
void MainWindow::showSettings()
{
    qDebug() << Q_FUNC_INFO;
    if (!m_dialogSettings) {
        m_dialogSettings = new Dialogs::Settings(this);
        connect(m_dialogSettings, SIGNAL(settingsChanged()), this, SLOT(readConfig()));
    }

    m_dialogSettings->show();
//    m_dialogSettings->adjustSize();
} // showSettings()

void MainWindow::showAbout()
{
    qDebug() << Q_FUNC_INFO;
    if (!m_dialogAbout) {
        m_dialogAbout = new Dialogs::About(this);
    }
    m_dialogAbout->show();
} // showAbout()

void MainWindow::readConfig()
{
    qDebug() << Q_FUNC_INFO;
    // Read config here
    qDebug() << "RC";
} // readConfig()

void MainWindow::timerEvent(QTimerEvent * /*event*/)
{
//    qDebug() << Q_FUNC_INFO;
    QTime currentTime(QTime::currentTime());
    QTime currentTimeHM(currentTime);
    // Force secs & msecs to 0
    currentTimeHM.setHMS(currentTime.hour(), currentTime.minute(), 0, 0);

    if (!m_lastUpdateTime.isNull() &&
        (currentTime.second() != 0 || m_lastUpdateTime == currentTimeHM)) {
//        qDebug() << "RETURN";
        return;
    }

    qDebug() << "QTime::currentTime():" << QTime::currentTime().toString("hh:mm:ss.zzz");
    qDebug() << "currentTime         :" << currentTime.toString("hh:mm:ss.zzz");
    qDebug() << "currentTimeHM       :" << currentTimeHM.toString("hh:mm:ss.zzz");

    m_dataProvider->updateOutdatedShows(Config::getValue(Config::CacheDuration).toInt()*60*60*24);

    m_lastUpdateTime = currentTimeHM;
} // timerEvent()


// EOF - vim:ts=4:sw=4:et:
