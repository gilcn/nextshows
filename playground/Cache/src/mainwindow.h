#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__


// Own
#include "ui_mainwindow.h"
// QtCore
#include <QtCore/QMap>
// QtGui
#include <QtGui/QDialog>

#include "cache.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void initDb();

private:
    Ui::MainWindow ui;
    Cache *m_cache;
    //QMap<int, QString> *map;
};


#endif // __MAINWINDOW_H__
