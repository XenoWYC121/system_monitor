//
// Created by fsy on 24-5-21.
//

#ifndef INPUTADDRESS_H
#define INPUTADDRESS_H

#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui
{
    class inputaddress;
}

QT_END_NAMESPACE

class inputaddress : public QWidget
{
protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Q_OBJECT

public:
    explicit inputaddress(QWidget *parent = nullptr);

    ~inputaddress() override;

signals:
    void addConnection(const QString &address, int port);

private slots:
    void addConnectionSlot();

private:
    void widgetInit();

    void lineEditInit();

    void signalInit(QWidget *parent);

private:
    Ui::inputaddress *ui;
};


#endif //INPUTADDRESS_H
