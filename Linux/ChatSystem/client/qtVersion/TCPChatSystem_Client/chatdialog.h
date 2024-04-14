#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <qdebug.h>

namespace Ui {
class ChatDialog;
}

struct UserInfo
{
    std::string nickname;
    std::string school;
    int user_id;

    //消息历史
    std::vector<std::string> _history_msg;
    //未读消息个数
    int msg_count;
};

class ChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatDialog(QWidget *parent = nullptr, int user_id = -1);
    ~ChatDialog();
    //获取好友信息
    bool GetFriendInfo();
    //设置聊天窗口
    void SetChatArea(std::string receiver);

    void addMessageItems();
public:
    int _user_id;
    int _send_id;
    std::vector<struct UserInfo> _friend_vec;
    std::vector<std::string> _chatDlg;
    QListWidget* messageList;
private:
    Ui::ChatDialog *ui;
};

#endif // CHATDIALOG_H
