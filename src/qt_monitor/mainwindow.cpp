#include "qt_monitor/mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->signInSingl();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newConnection(const QString &address)
{
    this->ui->tabWidget->addTab(new QWidget(this), "new tab");
}

void MainWindow::newConnectionTest()
{
    this->ui->tabWidget->addTab(new QWidget(this), "new tab");
}

void MainWindow::signInSingl()
{
    //connect(this->ui->newConnection, &QAction::triggered, this, &MainWindow::newConnectionTest);
    connect(this->ui->newConnection, &QAction::triggered, this->inputWidget, &QWidget::show);
}
