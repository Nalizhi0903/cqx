#include "recvthread.h"

RecvThread::RecvThread(QObject *parent) : QThread(parent)
{

}

void RecvThread::run()
{
    for(int i = 0 ; i <= 100 ; i++)
    {
        QThread::msleep(100);
        ShowDownloadProgress(i);
    }
}
