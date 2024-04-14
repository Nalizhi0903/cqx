#ifndef TCPSVR_H
#define TCPSVR_H
#include <QTcpSocket>
#include <QMessageBox>
#include <mutex>
#include "chatmsg.h"
#include "msgqueue.h"


class tcpSvr : public QObject
{
public:
    tcpSvr();
    tcpSvr(QWidget* parent);
    //连接服务器
    int connectTcpSvr();
    //向服务器发送消息
    int Send(std:: string& msg);
    //接受服务器消息
    int Recv(std::string* msg);
    //获取套接字
    static tcpSvr* GetInstance();
private:
    /*全局唯一的实例化对象*/
    static tcpSvr* _instance;
    //传递窗口，用于弹出信息
    QWidget* m_parent;
public:
    QTcpSocket* m_socket;
};

#endif // TCPSVR_H
