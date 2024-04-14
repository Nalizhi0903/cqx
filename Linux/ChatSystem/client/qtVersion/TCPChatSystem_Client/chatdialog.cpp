#include "chatdialog.h"
#include "ui_chatdialog.h"
#include "tcpsvr.h"

ChatDialog::ChatDialog(QWidget *parent, int user_id) :
    QDialog(parent),
    _user_id(user_id),
    ui(new Ui::ChatDialog)
{
    ui->setupUi(this);
    tcpSvr* ts = tcpSvr::GetInstance();
    messageList = new QListWidget();

    //发送按钮
    connect(ui->sendButton, &QPushButton::clicked, [=](){
        //1.获取发送内容
        QString text = ui->plainTextEdit->toPlainText();
        if(text.isEmpty())
            return;
        std::string SendText = text.toStdString();
        //2.组织发送消息，序列化消息
        ChatMsg cm;
        cm._msg_type = chat_msg_type::SendMsg;
        cm._user_id = _user_id;
        cm._json_msg["recvid"] = _send_id;
        cm._json_msg["msg"] = SendText;
        std::string msg;
        cm.GetMsg(&msg);
        //4.发送消息
        ts->Send(msg);
        //5.接受应答，判断消息是否成功
        connect(ts->m_socket, &QTcpSocket::readyRead,[=]()
        {
            ChatMsg cm;
            std::string msg;
            MsgQueue* mq = MsgQueue::GetInstance();
            mq->Pop(SendMsg_Resp, &msg);
            if(msg.empty())
                return;
            cm.PraseChatMsg(msg);
            QString send_status = "";
            if (cm._reply_statu == SENDMSG_FAILED)
            {
                send_status += "(send failed)";
            }
            else
            {
                send_status += "(send successed)";
            }
            //6.将消息添加到历史消息当中，并且展示到输出框
            for (size_t i = 0; i < _friend_vec.size(); i++)
            {
                if (_send_id == _friend_vec[i].user_id)
                {
                    std::string tmp = "我：";
                    tmp += ui->plainTextEdit->toPlainText().toStdString();
                    tmp += send_status.toStdString();
                    _friend_vec[i]._history_msg.push_back(tmp);
                    messageList->addItem(QString::fromStdString(tmp));
                    tmp.clear();
                    //7.清空发送框
                    ui->plainTextEdit->clear();
                    update();
                }
            }
        });
    });
    //获取好友信息
    GetFriendInfo();

    //显示好友消息
    connect(ts->m_socket, &QTcpSocket::readyRead, [=]()
    {
        ChatMsg cm;
        std::string msg;
        MsgQueue* mq = MsgQueue::GetInstance();
        mq->Pop(PushMsg, &msg);
        if(msg.empty())
            return;
        cm.PraseChatMsg(msg);
        std::string peer_msg = cm._json_msg["peer_msg"].asString();
        int peer_userid = cm._json_msg["peer_userid"].asInt();
        //将消息添加到历史消息当中
        for (size_t i = 0; i < _friend_vec.size(); i++)
        {
            if (peer_userid == _friend_vec[i].user_id)
            {

                std::string tmp = _friend_vec[i].nickname;
                tmp += ":";
                tmp += peer_msg;
                _friend_vec[i]._history_msg.push_back(tmp);
                //如果是当前聊天界面，显示消息
                if(_friend_vec[i].nickname == ui->tabWidget->tabText(ui->tabWidget->currentIndex()).toStdString())
                    messageList->addItem(QString::fromStdString(tmp));
                update();
                tmp.clear();
            }
        }
    });

    //点击好友列表切换或添加窗口
    connect(ui->listWidget, &QListWidget::pressed, this, [=]()
    {
        QString currentSelect = ui->listWidget->currentItem()->text();
        std::string nickname = currentSelect.toStdString();
        //添加新窗口
        SetChatArea(nickname);
        auto it = _chatDlg.begin();
        int index = 0;
        while(it != _chatDlg.end())
        {
            if(*it == nickname)
            {
                break;
            }
            index++;
            it++;
        }
        ui->tabWidget->setCurrentIndex(index);
        update();
    });

    //切换聊天窗口改变发送对象
    connect(ui->tabWidget, &QTabWidget::currentChanged, [=]()
    {
        //切换聊天窗口改变发送对象
        for(int i = 0; i < ui->tabWidget->count(); i++)
        {
            if(_friend_vec[i].nickname == ui->tabWidget->tabText(ui->tabWidget->currentIndex()).toStdString())
            {
                _send_id = _friend_vec[i].user_id;
                break;
            }
        }
        //messageList重新显示当前的聊天记录
        messageList->setParent(ui->tabWidget->currentWidget());
        messageList->clear();
        addMessageItems();
        messageList->show();
    });
}

bool ChatDialog::GetFriendInfo()
{
    //组织登入信息
    ChatMsg cm;
    cm._msg_type = GetFriend;
    cm._user_id = _user_id;
    std::string msg;
    cm.GetMsg(&msg);
    tcpSvr* ts = tcpSvr::GetInstance();
    ts->Send(msg);
    //获取消息队列实例化指针
    MsgQueue* mq = MsgQueue::GetInstance();
    if (mq == nullptr)
    {
        QMessageBox::warning(this, "警告", "内部错误");
        return false;
    }
    connect(ts->m_socket, &QTcpSocket::readyRead,[=]()
    {
        //从队列中获得消息
        std::string msg;
        MsgQueue* mq = MsgQueue::GetInstance();
        mq->Pop(GetFriend_Resp, &msg);
        if(msg.empty())
            return;
        //解析消息
        ChatMsg cm;
        cm.PraseChatMsg(msg);
        if (cm._reply_statu == GETFRIEND_SUCCESS)
        {
            for (int i = 0; i < (int)cm._json_msg.size(); i++)
            {
                struct UserInfo ui;
                ui.nickname = cm._json_msg[i]["nickname"].asString();
                ui.school = cm._json_msg[i]["school"].asString();
                ui.user_id = cm._json_msg[i]["userid"].asInt();

                _friend_vec.push_back(ui);
            }
            //刷新好友信息到userlist当中
            for(size_t i = 0; i < _friend_vec.size(); i++)
            {
                std::string nickname = _friend_vec[i].nickname;
                ui->listWidget->addItem(nickname.c_str());
            }
            //默认第一个好友为发送对象
            _send_id = _friend_vec[0].user_id;
            //设置初始聊天窗口
            ui->tabWidget->setTabText(0, QString::fromStdString(_friend_vec[0].nickname));
            messageList->setParent(ui->tabWidget->currentWidget());
            messageList->resize(500,400);
            messageList->show();
            _chatDlg.push_back(_friend_vec[0].nickname);
            update();
        }
        else
        {
            return;
        }
    });
    return true;
}

void ChatDialog::SetChatArea(std::string receiver)
{
    auto empty = new QWidget();
    auto it = _chatDlg.begin();
    while(it != _chatDlg.end())
    {
        if(receiver != *it)
        {
            it++;
            continue;
        }
        else
        {
            break;
        }
    }
    if(it == _chatDlg.end())
    {
        _chatDlg.push_back(receiver);
        ui->tabWidget->addTab(empty, QString::fromStdString(receiver));
    }
    update();
}

void ChatDialog::addMessageItems()
{
    update();
    for(int i = 0; i < ui->tabWidget->count(); i++)
    {
        if(_friend_vec[i].nickname == ui->tabWidget->tabText(ui->tabWidget->currentIndex()).toStdString())
        {
            if(_friend_vec[i]._history_msg.size() == 0)
                break;
            for(size_t j = 0; j < _friend_vec[i]._history_msg.size(); j++)
            {
                QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(_friend_vec[i]._history_msg[j]));
                messageList->addItem(item);
            }
            break;
        }
    }
}

ChatDialog::~ChatDialog()
{
    delete ui;
}
