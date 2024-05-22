#ifndef MSGBOX_H
#define MSGBOX_H

#include <QObject>
#include<QEventLoop>
#include<QMessageBox>
#include<QApplication>
#include<QTimer>

class msgBox : public QObject
{
    Q_OBJECT

public:
    explicit msgBox(QObject *parent = nullptr);

private:
    const QString title;
    const QString msg;
    int type;

    void readyShow(void);

public:
    msgBox(const QString &title, const QString &msg, const int type);

    static void show(const QString &title, const QString &msg, const int type);

public slots:
    void onShow();
};

#endif // MSGBOX_H
