<h1 align=center>基于TCP的ChatSystem实现</h1>
<h2>客户端实现</h2>

开发环境:Qt5、C++11、windows11

<h3>模块：</h3>

tcp模块

登入模块

注册模块

聊天模块

消息模块

<h3>消息模块</h3>

消息类型：

```
enum chat_msg_type
{
    Register = 0,//注册请求
    Register_Resp, //注册应答
    Login,//登入
    Login_Resp,//登入应答
    AddFriend,//添加好友
    AddFriend_Resp,//添加好友应答 5
    PushAddFriendMsg,//推送好友请求
    PushAddFriendMsg_Resp,//推送添加好友应答
    SendMsg,//发送消息
    SendMsg_Resp,//发送消息应答
    PushMsg,//推送数据 10
    PushMsg_Resp,//推送数据应答
    GetFriend,//获取好友信息请求
    GetFriend_Resp//获取好友信息的应答
};
enum reply_statu
{
    REGISTER_SUCCESS = 0,
    REGISTER_FAILED,
    LOGIN_SUCCESS,
    LOGIN_FAILED,
    ADDFRIEND_SUCCESS,
    ADDFRIEND_FAILED,//5
    SENDMSG_SUCCESS,
    SENDMSG_FAILED,
    GETFRIEND_SUCCESS,
    GETFRIEND_FAILED
};
```

使用jsoncpp格式的消息，qt使用jsoncpp的方法，在项目下创建文件夹，将jsoncpp压缩包下的include目录中的全部头文件和src中lib目录的源文件全部复制到创建的文件夹中，在项目中将其添加，运行时要注意用的时Debug版本还是Release版本以及版本是32位还是64位

ChatMsg类

```C++
class ChatMsg
{
public:
    ChatMsg();
    ~ChatMsg();
public:
    //  提供一个序列化接口
    //  将成员变量的内存放到同一块连续的空间当中
    //  msg:出参，保存序列化的内容
    bool GetMsg(string* msg);

    //提供一个反序列化的接口
    //将连续的内存放到ChatMsg对象的成员变量当中去

    int PraseChatMsg(const std::string& msg);

    std::string GetValue(const std::string& key);

    void Clear();

public:
    int _msg_type;
    //存放客户端的文件描述符，方便发送线程获取，发送数据
    int _sockfd;
    //用户ID
    int _user_id;
    //应答状态
    int _reply_statu;
    //根据消息类型的不同，json_value的数据不一样
    Json::Value _json_msg;
};
```

ChatMsg.cpp

```C++
#include "chatmsg.h"
//消息序列化
bool JsonUtil::Serialize(const Json::Value& value, std::string* body)
{
    Json::StreamWriterBuilder swb;
    std::unique_ptr<Json::StreamWriter> sw(swb.newStreamWriter());
    std::stringstream ss;
    int ret = sw->write(value, &ss);
    if (ret != 0)
    {
        return false;
    }
    *body = ss.str();
    return true;
}
//反序列化
bool JsonUtil::UnSerialize(const std::string& body, Json::Value* value)
{
    Json::CharReaderBuilder crb;
    std::unique_ptr<Json::CharReader> cr(crb.newCharReader());
    std::string err;
    bool ret = cr->parse(body.c_str(), body.c_str() + body.size(), value, &err);
    if (ret == false)
    {
        return false;
    }
    return true;
}

ChatMsg::ChatMsg() :_msg_type(-1), _sockfd(-1), _user_id(-1), _reply_statu(-1)
{
    _json_msg.clear();
}

ChatMsg::~ChatMsg()
{

}

bool ChatMsg::GetMsg(string* msg)
{
    Json::Value tmp;
    tmp["msg_type"] = _msg_type;
    tmp["user_id"] = _user_id;
    tmp["reply_statu"] = _reply_statu;
    tmp["json_msg"] = _json_msg;

    JsonUtil::Serialize(tmp, msg);
    return true;
}

int ChatMsg::PraseChatMsg(const std::string& msg)
{
    Json::Value tmp;
    JsonUtil::UnSerialize(msg, &tmp);

    _msg_type = tmp["msg_type"].asInt();
    _msg_type = tmp["msg_type"].asInt();
    _user_id = tmp["user_id"].asInt();
    _reply_statu = tmp["reply_statu"].asInt();
    _json_msg = tmp["json_msg"];
    return true;
}

std::string ChatMsg::GetValue(const std::string& key)
{
    if (!_json_msg.isMember(key))
    {
        return "";
    }
    return _json_msg[key].asString();
}

void  ChatMsg::Clear()
{
    _msg_type = -1;
    _user_id = -1;
    _reply_statu = -1;
    _json_msg.clear();
}
```



<h3>tcp模块</h3>

在初始化客户端时，要将客户端与服务端需要先建立连接，服务器和客户端收发都会得到确认，传输完毕需要断开连接。

在工程文件*.pro里面加入网络模块

```c++
QT     += network
```

创建通信的套接字对象

```c++
#include  <QTcpSocket>
m_socket = new QTcpSocket(this);
```

tcpsvr.h文件

```c++
#ifndef TCPSVR_H
#define TCPSVR_H
#include <QTcpSocket>
#include <QMessageBox>


class tcpSvr
{
public:
    tcpSvr(QWidget* parent);
    //连接服务器
    int connectTcpSvr();
private:
    QTcpSocket* m_socket;
    //传递窗口，用于弹出信息
    QWidget* m_parent;
};

#endif // TCPSVR_H
```

tcpsvr.cpp文件

```c++
#include "tcpsvr.h"
#define IP "192.168.163.132"
#define port 7878
tcpSvr::tcpSvr(QWidget* parent):m_parent(parent)
{

}

int tcpSvr::connectTcpSvr()
{
    //创建通信的套接字对象
    m_socket = new QTcpSocket();
    QString ip = IP;
    //连接服务器
    m_socket->connectToHost(ip, port);
    //判断是否连接成功
    if(m_socket->waitForConnected() == true)
    {
        QMessageBox::information(m_parent, "消息", "连接服务器成功");
    }else
    {
        QMessageBox::warning(m_parent, "警告","连接服务器失败");
    }
    return 0;
}
```

