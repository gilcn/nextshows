// Own
#include "mainwindow.h"
// QtCore
#include <QtCore/QDebug>
#include <QtCore/QMap>
// QtGui
#include <QtGui/QPushButton>

#include "cache.h"

/*
** public:
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_cache(new Cache(this))
{
    ui.setupUi(this);
    
    //connect(ui.btnCheckCache, SIGNAL(clicked(bool)), ui.textInfo, SLOT(clear()));
    connect(ui.btnCheckCache, SIGNAL(clicked(bool)), this, SLOT(initDb()));

    connect(m_cache, SIGNAL(stateChanged(const QString &)), ui.infoTextEdit, SLOT(append(const QString &)));
    
    connect(ui.btnListShows,SIGNAL(clicked(bool)),this,SLOT(getShowList()));
} // ctor()

MainWindow::~MainWindow()
{
} // dtor()

void MainWindow::initDb()
{
    ui.btnCheckCache->setEnabled(false);
    QMap<QString, QString> map = m_cache->getShows();

    foreach (QString id, map.keys()) {
        qDebug() << id << ":" << map.value(id);
        ui.infoTextEdit->append(id+" : "+map.value(id));
    }
}

void MainWindow::getShowList()
{
    QMap<QString, QString> map = m_cache->getShows();

    foreach (QString id, map.keys()) {
        qDebug() << id << ":" << map.value(id);
        ui.infoTextEdit->append(id+" : "+map.value(id));
    }
}
