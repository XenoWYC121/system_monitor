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
    Q_OBJECT

public:
    explicit inputaddress(QWidget *parent = nullptr);

    ~inputaddress() override;

private:
    Ui::inputaddress *ui;
};


#endif //INPUTADDRESS_H
