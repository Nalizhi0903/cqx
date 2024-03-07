#include "tcpsvr.h"
#define IP "192.168.163.132"
#define port 7878

std::mutex g_mt;
tcpSvr* tcpSvr::_instance = nullptr;

tcpSvr::tcpSvr():m_parent(nullptr)
{

}


tcpSvr::tcpSvr(QWidget* parent):m_parent(parent)
{

}

tcpSvr* tcpSvr::GetInstance()
{
    g_mt.lock();
    if(_instance == nullptr)
    {
        _instance = new tcpSvr();
        _instance->m_socket = new QTcpSocket();
        _instance->connectTcpSvr();
    }
    g_mt.unlock();
    return _instance;
}

int tcpSvr::connectTcpSvr()
{
    //创建通信的套接字对象
    QString ip = IP;
    //连接服务器
    m_socket->connectToHost(ip, port);

    //接受信息,放入消息队列
    connect(m_socket, &QTcpSocket::readyRead, [=]()
    {
        std::string msg;
        int ret = this->Recv(&msg);
        if(ret != 0)
        {
            ChatMsg cm;
            cm.PraseChatMsg(msg);
            MsgQueue* mq = MsgQueue::GetInstance();
            mq->Push(cm._msg_type, msg);
        }
    });
    return 0;
}

//向服务器发送消息
int tcpSvr::Send(std:: string& msg)
{
    return m_socket->write(msg.c_str());
}
//接受服务器消息
int tcpSvr::Recv(std::string* msg)
{
    QByteArray buf = m_socket->readAll();
    int r_s = buf.size();
    if (r_s < 0)
    {
        return r_s;
    }
    else if (r_s == 0)
    {
        //1.重新连接
        //2.关闭应用
    }
    else
    {
        msg->append(buf);
    }
    return r_s;
}
