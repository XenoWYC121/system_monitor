//
// Created by fsy on 24-5-21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_inputaddress.h" resolved

#include "qt_monitor/mainwindow.h"
#include "qt_monitor/inputaddress.h"
#include "qt_monitor/inputaddress.h"
#include "./ui_inputaddress.h"

#include <QValidator>
#include <QRegularExpressionValidator>

void inputaddress::closeEvent(QCloseEvent *event)
{
    this->ui->address->clear();
    this->ui->port->clear();
}

inputaddress::inputaddress(QWidget *parent)
    : QWidget(parent), ui(new Ui::inputaddress)
{
    ui->setupUi(this);
    this->signalInit(parent);
    this->widgetInit();
    this->lineEditInit();
}

inputaddress::~inputaddress()
{
    delete ui;
}

void inputaddress::addConnectionSlot()
{
    const auto &address = this->ui->address->text();
    const int port = this->ui->port->text().toInt();
    this->addConnection(address, port);
    qDebug() << "back to add connection slot";
    this->close();
}

void inputaddress::widgetInit()
{
    // 设置模态对话框
    this->setWindowFlags(Qt::Dialog);
    this->setWindowModality(Qt::WindowModal);
    // 设置title
    this->setWindowTitle("输入连接地址");
}

void inputaddress::lineEditInit()
{
    this->ui->port->setValidator(new QIntValidator(0, 25536, this));
    const QRegularExpression reg("[0-9]+.[0-9]+.[0-9]+.[0-9]");
    this->ui->address->setValidator(new QRegularExpressionValidator(reg, this));
}

void inputaddress::signalInit(QWidget *parent)
{
    connect(this->ui->pushButton, &QPushButton::released, this, &inputaddress::addConnectionSlot);
    const auto parent_ptr = dynamic_cast<MainWindow *>(parent);
    if (!parent_ptr)
    {
        abort();
    }
    connect(this, &inputaddress::addConnection, parent_ptr, &MainWindow::newConnection);
}
