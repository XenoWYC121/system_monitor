#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "inputaddress.h"

#include <QMainWindow>
#include <QString>
#include <QMap>
QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

public slots:
    void newConnection(const QString &address, int port);

    void newConnectionTest();

private slots:
    void deleteTap() const;

private:
    void initSignals();

private:
    Ui::MainWindow *ui;
    QMap<QString, QString> connector_map;
    inputaddress *inputWidget{new inputaddress(this)};
};
#endif // MAINWINDOW_H
