#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "msgqueue.h"
#include "chatmsg.h"
#include "tcpsvr.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    //注册按钮
    connect(ui->Register_btn, &QPushButton::clicked, [=]()
    {
        //1.获取电话和密码
        QString phoneNumber = ui->phoneNumberlineEdit->text();
        QString password = ui->passWordlineEdit->text();
        QString school = ui->SchoollineEdit->text();
        QString nickname = ui->nickNamelineEdit->text();
        if(phoneNumber.size() == 0)
        {
            QMessageBox::warning(this, "警告", "电话不能为空");
            return;
        }else if(password.size() == 0)
        {
            QMessageBox::warning(this, "警告", "密码不能为空");
            return;
        }
        /*2.组织注册消息（ChatMsg）*/
        ChatMsg cm;
        cm._msg_type = chat_msg_type::Register;
        cm._json_msg["nickname"] = nickname.toUtf8().data();
        cm._json_msg["school"] = school.toUtf8().data();
        cm._json_msg["telnum"] = phoneNumber.toUtf8().data();
        cm._json_msg["passwd"] = password.toUtf8().data();
        std::string msg;
        cm.GetMsg(&msg);
        /*3.获取TcpSvr实例化指针*/
        tcpSvr* ts = tcpSvr::GetInstance();
        if (ts == nullptr)
        {
            QMessageBox::warning(this, "警告", "内部错误");
            return;
        }
        /*4.发送消息*/
        ts->Send(msg);
        connect(ts->m_socket, &QTcpSocket::readyRead, [=]{
            /*5.获取消息队列的实例化指针*/
            MsgQueue* mq = MsgQueue::GetInstance();
            if (mq == nullptr)
            {
                QMessageBox::warning(this, "警告", "内部错误");
                return;
            }
            /*6.获取注册应答*/
            std::string msg;
            ChatMsg cm;
            mq->Pop(Register_Resp, &msg);
            cm.PraseChatMsg(msg);
            if(msg.empty())
                return;
            /*7.判断注册应答当中的状态*/
            if (cm._reply_statu == REGISTER_SUCCESS)
            {
                //提醒用户注册成功，关闭页面
                QMessageBox::information(this, "Ok", "注册成功");
                //退出当前界面
            }
            else
            {
                //提醒用户注册失败
                QMessageBox::warning(this, "警告", "注册失败");
            }
        });
    });



    //返回按钮
    connect(ui->Back_btn, &QPushButton::clicked, this, &QWidget::close);

}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}
