// Own
#include "mainwindow.h"
// QtCore
#include <QtCore/QDebug>
#include <QtCore/QMetaEnum>
// QtGui
#include <QtGui/QAbstractButton>
#include <QtGui/QHeaderView>
#include <QtGui/QPainter>
#include <QtGui/QPushButton>
// QtNetwork
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>


//#define _TEXT(x) #x
//#define TEXT(x) _TEXT(x)
#define ADD_ITEM(url)                                   \
    {                                                   \
    QStandardItem *itemURL  = new QStandardItem( url ); \
    QStandardItem *itemIcon = new QStandardItem();      \
    itemIcon->setIcon(colorIcon(Qt::white));            \
    QList<QStandardItem *> items;                       \
    items << itemURL << itemIcon;                       \
    m_model->appendRow(items);                          \
    }


/*
** public:
*/
MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
    , m_nma(new QNetworkAccessManager(this))
    , m_model(new QStandardItemModel(this))
{
    ui.setupUi(this);

    // Buttons
    QPushButton *btnAddRow = new QPushButton("&Add row");
    btnAddRow->setObjectName("btnAddRow");
    ui.buttonBox->addButton(btnAddRow, QDialogButtonBox::ActionRole);
    QPushButton *btnExec = new QPushButton("&Exec");
    btnExec->setObjectName("btnExec");
    btnExec->setAutoDefault(true);
    btnExec->setDefault(true);
    ui.buttonBox->addButton(btnExec, QDialogButtonBox::ActionRole);
    QPushButton *btnClose = new QPushButton("&Close");
    btnClose->setObjectName("btnClose");
    ui.buttonBox->addButton(btnClose, QDialogButtonBox::AcceptRole);
    connect(ui.buttonBox, SIGNAL(clicked(QAbstractButton*)),
            this, SLOT(dlgBtnClicked(QAbstractButton*)));

    // Network
    connect(m_nma, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(requestFinished(QNetworkReply *)));

    // Model
    m_model->setColumnCount(2);
    ui.tableView->setModel(m_model);
    connect(m_model, SIGNAL(itemChanged(QStandardItem *)),
            this, SLOT(tableItemChanged(QStandardItem *)));

    // Table
    ui.tableView->horizontalHeader()->hide();
    ui.tableView->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    ui.tableView->horizontalHeader()->setResizeMode(1, QHeaderView::Fixed);
    ui.tableView->setColumnWidth(1, 22);
    connect(ui.tableView, SIGNAL(clicked(const QModelIndex &)),
            this, SLOT(tableClicked(const QModelIndex &)));

    // Add some items
    ADD_ITEM("file:///etc/passwd")
    ADD_ITEM("ftp://ftp.free.fr/mirrors/ftp.archlinux.org/iso/latest/README")
    ADD_ITEM("ftp://ftp.free.fr/mirrors/ftp.archlinux.org/iso/latest/INVALID_FILE")
    ADD_ITEM("http://example.com/")
    ADD_ITEM("http://google.com/")
    ADD_ITEM("http://invalid.domain/")
    ADD_ITEM("http://kde.org/")
    ADD_ITEM("http://kopete.kde.org/")
    ADD_ITEM("http://linuxfr.org/")
    ADD_ITEM("http://nextshows.googlecode.com/")
    ADD_ITEM("http://plasma.kde.org/")
    ADD_ITEM("http://slashdot.org/")
    ADD_ITEM("http://trolltech.com/")
    ADD_ITEM("http://w3.org/")
} // ctor()

MainWindow::~MainWindow()
{
    delete m_model;
    delete m_nma;
} // dtor()


/*
** private Q_SLOTS
*/
void MainWindow::dlgBtnClicked(QAbstractButton *button)
{
    if (button->objectName() == "btnClose") {
        accept();
    }
    else if (button->objectName() == "btnAddRow") {
        ADD_ITEM();
    }
    else if (button->objectName() == "btnExec") {
        processRequests();
    }
} // dlgBtnClicked()

void MainWindow::requestFinished(QNetworkReply *reply)
{
    QList<QStandardItem *> items;
    items = m_model->findItems(reply->request().url().toString());
    int row = m_model->indexFromItem(items[0]).row();
    QStandardItem *itemIcon = m_model->item(row, 1);

    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << qPrintable(reply->request().url().toString())
                 << "- OK";

        itemIcon->setIcon(colorIcon(Qt::green));
    } else {
        QString errorName;
        QMetaObject meta = QNetworkReply::staticMetaObject;
        for (int i=0; i < meta.enumeratorCount(); ++i) {
            QMetaEnum m = meta.enumerator(i);
            if (m.name() == QLatin1String("NetworkError")) {
                errorName = QLatin1String(m.valueToKey(reply->error()));
                break;
            }
        }

        qDebug() << qPrintable(reply->request().url().toString())
                 << "- ERROR:" << qPrintable(errorName);

        itemIcon->setIcon(colorIcon(Qt::red));
    }

    reply->deleteLater();
} // requestFinished()

void MainWindow::tableClicked(const QModelIndex &index)
{
    qDebug() << index;
} // tableClicked()

void MainWindow::tableItemChanged(QStandardItem *item)
{
    if (m_model->indexFromItem(item).column() == 0) {
        if (item->text().isEmpty()) {
            int row = m_model->indexFromItem(item).row();
            m_model->removeRow(row);
        }
    }
} // tableItemChanged()


/*
** private:
*/
QIcon MainWindow::colorIcon(const QColor &color)
{
    QPixmap pixmap(16, 16);
    pixmap.fill(color);

    QPainter p(&pixmap);
    p.setPen(Qt::black);
    p.drawRect(0, 0, pixmap.size().width()-1, pixmap.size().height()-1);

    return QIcon(pixmap);
} // colorIcon()


void MainWindow::processRequests()
{
    QStandardItem *item;
    int i = 0;
    while ( (item = m_model->item(i, 0)) ) {
        m_nma->get(QNetworkRequest(QUrl(item->text())));
        ++i;
    }

} // processRequests()
