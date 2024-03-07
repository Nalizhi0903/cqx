#include "widget.h"
#include "tcpsvr.h"
#include <iostream>
#include <QApplication>
#include <thread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
