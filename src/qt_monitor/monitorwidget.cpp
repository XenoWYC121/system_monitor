//
// Created by fsy on 24-5-21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_monitorWidget.h" resolved

#include "sys_info.pb.h"

#include "qt_monitor/monitorwidget.h"
#include <grpcpp/create_channel.h>

#include "./ui_monitorwidget.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>

namespace system_monitor::qt
{
    monitorWidget::monitorWidget(QString address, int port, QWidget *parent)
        : QWidget(parent),
          ui(new Ui::monitorWidget),
          address(std::move(address)),
          port(port),
          client(grpc::CreateChannel(std::string(this->address.toStdString() + ":" + std::to_string(this->port)),
                                     grpc::InsecureChannelCredentials()))
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
        monitor::sys_info_response res;
        try
        {
            res = this->client.call(true, true);
        }
        catch (const std::runtime_error &error)
        {
            this->stopFlag = true;
            QMessageBox::critical(this, "error", error.what());
        }
        this->updateCpuView(res.cpu_info());
        this->updateMemoryView(res.memory_info());
    }

    void monitorWidget::run()
    {
        while (!this->stopFlag)
        {
            this->updateInfo();
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }

    void monitorWidget::updateMemoryView(const monitor::memory_usage &memInfo) const
    {
        this->ui->memoryTable->clear();
        this->ui->memoryTable->setRowCount(1);
        this->ui->memoryTable->setColumnCount(2);
        this->ui->memoryTable->setHorizontalHeaderLabels({"total", "free"});
        this->ui->memoryTable->setItem(0, 0, new QTableWidgetItem(QString::number(memInfo.total_ram())));
        this->ui->memoryTable->setItem(0, 1, new QTableWidgetItem(QString::number(memInfo.free_ram())));
    }

    void monitorWidget::updateCpuView(const monitor::all_cpu_usage &cpuInfo) const
    {
        this->ui->cpuTable->clear();
        this->ui->cpuTable->setRowCount(cpuInfo.list_size()); //hang
        this->ui->cpuTable->setColumnCount(4); //lie
        this->ui->cpuTable->setHorizontalHeaderLabels({"name", "sys usage", "user usage", "total usage"});
        int row = 0;
        for (const auto &item: cpuInfo.list())
        {
            this->ui->cpuTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(item.cpu_name())));
            this->ui->cpuTable->setItem(row, 1, new QTableWidgetItem(QString::number(item.system_usage())));
            this->ui->cpuTable->setItem(row, 2, new QTableWidgetItem(QString::number(item.user_usage())));
            this->ui->cpuTable->setItem(row, 3, new QTableWidgetItem(QString::number(item.total_usage())));
            row++;
        }
    }
} // system_monitor::qt
