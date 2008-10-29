// Own
#include "mainwindow.h"
// Qtgui
#include <QtGui/QApplication>


int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
