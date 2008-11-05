// Own
#include "mainwindow.h"
// QtCore
#include <QtCore/QDebug>
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
} // ctor()

MainWindow::~MainWindow()
{
} // dtor()

void MainWindow::initDb()
{
    ui.btnCheckCache->setEnabled(false);
    m_cache->openDB();
}
