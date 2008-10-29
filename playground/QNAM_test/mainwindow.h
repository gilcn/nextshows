#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__


// Own
#include "ui_mainwindow.h"
// QtGui
#include <QtGui/QDialog>
#include <QtGui/QStandardItemModel>
// QtNetwork
#include <QtNetwork/QNetworkAccessManager>


class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void dlgBtnClicked(QAbstractButton *);
    void requestFinished(QNetworkReply *);
    void tableClicked(const QModelIndex &);
    void tableItemChanged(QStandardItem *);

private:
    QIcon colorIcon(const QColor &color);
    void processRequests();

    Ui::MainWindow ui;

    QNetworkAccessManager *m_nma;
    QStandardItemModel *m_model;
};


#endif // __MAINWINDOW_H__
