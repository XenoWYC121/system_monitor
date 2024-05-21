//
// Created by fsy on 24-5-21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_monitorWidget.h" resolved

#include "qt_monitor/monitorwidget.h"
#include "./ui_monitorwidget.h"
#include "./ui_mainwindow.h"

namespace system_monitor::qt {
monitorWidget::monitorWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::monitorWidget) {
    ui->setupUi(this);
}

monitorWidget::~monitorWidget() {
    delete ui;
}
} // system_monitor::qt
