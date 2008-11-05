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
{
    ui.setupUi(this);
    
    //connect(ui.btnCheckCache, SIGNAL(clicked(bool)), ui.textInfo, SLOT(clear()));
    connect(ui.btnCheckCache, SIGNAL(clicked(bool)), this, SLOT(initDb()));

} // ctor()

MainWindow::~MainWindow()
{
} // dtor()

void MainWindow::initDb()
{
    m_cache = new Cache();
    ui.btnCheckCache->setEnabled(false);
    connect(m_cache, SIGNAL(stateChanged(QString text)), ui.infoTextEdit, SLOT(append()));
}