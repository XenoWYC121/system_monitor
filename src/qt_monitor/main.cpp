#include "qt_monitor/mainwindow.h"
#include "qt_monitor/monitorwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
