//
// Created by fsy on 24-5-21.
//

#ifndef MONITORWIDGET_H
#define MONITORWIDGET_H

#include <QWidget>
#include <thread>
#include <atomic>

namespace system_monitor::qt
{
    QT_BEGIN_NAMESPACE

    namespace Ui
    {
        class monitorWidget;
    }

    QT_END_NAMESPACE

    class monitorWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit monitorWidget(QString address, int port, QWidget *parent = nullptr);

        ~monitorWidget() override;

    private:
        void updateInfo();

        void run();

        void updateMemoryView();

        void updateCpuView();

    private:
        Ui::monitorWidget *ui;
        const QString address;
        const int port;
        std::thread t;
        std::atomic<bool> stopFlag{false};
    };
} // system_monitor::qt

#endif //MONITORWIDGET_H
