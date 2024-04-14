#ifndef WIDGET_H
#define WIDGET_H

#include "msgqueue.h"
#include "mythread.h"
#include <QWidget>
#include <QDebug>
#include <QDialog>
#include <QTimer>
#include <QMessageBox>
#include <tcpsvr.h>
#include <chatmsg.h>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

static void RecvMsgStart();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
