//
// Created by fsy on 24-5-21.
//

#ifndef MONITORWIDGET_H
#define MONITORWIDGET_H

#include <QWidget>

namespace system_monitor::qt {
QT_BEGIN_NAMESPACE
namespace Ui { class monitorWidget; }
QT_END_NAMESPACE

class monitorWidget : public QWidget {
Q_OBJECT

public:
    explicit monitorWidget(QWidget *parent = nullptr);
    ~monitorWidget() override;

private:
    Ui::monitorWidget *ui;
};
} // system_monitor::qt

#endif //MONITORWIDGET_H
