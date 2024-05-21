//
// Created by fsy on 24-5-21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_monitorWidget.h" resolved
#include "sys_info.grpc.pb.h"
#include "sys_info.pb.h"

#include "qt_monitor/monitorwidget.h"
#include "./ui_monitorwidget.h"
#include "./ui_mainwindow.h"

namespace system_monitor::qt
{
    monitorWidget::monitorWidget(QString address, int port, QWidget *parent)
        : QWidget(parent),
          ui(new Ui::monitorWidget),
          address(std::move(address)),
          port(port)
    {
        ui->setupUi(this);
        this->t = std::thread([this]()
        {
            this->run();
        });
    }

    monitorWidget::~monitorWidget()
    {
        this->stopFlag = true;
        if (this->t.joinable())
        {
            t.join();
        }
        delete ui;
    }

    void monitorWidget::updateInfo()
    {

    }

    void monitorWidget::run()
    {
        while (!this->stopFlag)
        {
            this->updateInfo();
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }
} // system_monitor::qt
