//
// Created by fsy on 24-5-21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_inputaddress.h" resolved

#include "qt_monitor/inputaddress.h"
#include "./ui_inputaddress.h"


inputaddress::inputaddress(QWidget *parent)
    : QWidget(parent), ui(new Ui::inputaddress)
{
    ui->setupUi(this);
    // 设置模态对话框
    this->setWindowFlags(Qt::Dialog);
    this->setWindowModality(Qt::WindowModal);
    // 设置title
    this->setWindowTitle("输入连接地址");
}

inputaddress::~inputaddress()
{
    delete ui;
}
