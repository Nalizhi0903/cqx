#include "widget.h"
#include "ui_widget.h"
#include "windows.h"
#include "registerdialog.h"
#include "chatdialog.h"
#include <thread>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    MyThread* thread = new MyThread;
    thread->start();

    tcpSvr*ts = tcpSvr::GetInstance();

    //登入按钮
    connect(ui->Login_btn, &QPushButton::clicked, [=]()
    {
        //1.获取电话和密码
        QString phoneNumber = ui->phoneNumberlineEdit->text();
        QString password = ui->passWordlineEdit->text();
        if(phoneNumber.size() == 0)
        {
            QMessageBox::warning(this, "警告", "电话不能为空");
            return;
        }else if(password.size() == 0)
        {
            QMessageBox::warning(this, "警告", "密码不能为空");
            return;
        }
        //2.组织登入信息
        ChatMsg cm;
        cm._msg_type = Login;
        cm._json_msg["telnum"] = phoneNumber.toUtf8().data();
        cm._json_msg["passwd"] = password.toUtf8().data();
        std::string msg;
        cm.GetMsg(&msg);
        if (ts == nullptr)
        {
            QMessageBox::warning(this, "警告", "内部错误，请联系开发人员");
        }
        //4.发送登入信息
        ts->Send(msg);
        connect(ts->m_socket, &QTcpSocket::readyRead, this,[=](){
            //5.获取消息队列
            MsgQueue* mq = MsgQueue::GetInstance();
            if (mq == nullptr)
            {
                QMessageBox::warning(this, "警告", "内部错误，请联系开发人员");
                return;
            }
            //6.从消息队列中获取登入应答
            std::string msg;
            ChatMsg cm;
            mq->Pop(Login_Resp, &msg);
            if(msg.empty())
                return;
            //7.通过登入应答判断是否登入成功
            cm.PraseChatMsg(msg);
            if (cm._reply_statu == LOGIN_SUCCESS)
            {
                QMessageBox::information(this, "Ok", "登入成功");
                //关闭当前界面
                this->close();
                //跳转到聊天界面
                ChatDialog* chatdlg = new ChatDialog(this, cm._user_id);
                chatdlg->setWindowTitle("聊天界面");
                //不能用exec,会阻塞socket的传递
                chatdlg->show();
            }
            else
            {
                QMessageBox::warning(this, "警告", "登入失败，请检查账号和密码");
            }
        });
    });



    //注册按钮
    connect(ui->Register_btn, &QPushButton::clicked, [=](){
        RegisterDialog* REGDLOG = new RegisterDialog(this);
        REGDLOG->exec();
    });

}

Widget::~Widget()
{
    delete ui;
}

