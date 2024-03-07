//mythread.cpp
#include "mythread.h"
#include "msgqueue.h"
#include "tcpsvr.h"
#include <QDebug>
#include <QString>

MyThread::MyThread()
{
}
void MyThread::run()
{
    /*获取tcp服务*/
        tcpSvr* ts = tcpSvr::GetInstance();
        if (ts == nullptr)
        {
            return;
        }
        /*获取消息队列*/
        MsgQueue* mq = MsgQueue::GetInstance();
        if (mq == nullptr)
        {
            return;
        }
        /*循环接收数据*/
        connect(ts->m_socket, &QTcpSocket::readyRead,[=]()
        {
            std::string msg;
            int ret = ts->Recv(&msg);
            if (ret < 0)
            {
                return;
            }
            ChatMsg cm;
            cm.PraseChatMsg(msg);
            mq->Push(cm._msg_type, msg);
        });
        while (1)
        {
        }
}
