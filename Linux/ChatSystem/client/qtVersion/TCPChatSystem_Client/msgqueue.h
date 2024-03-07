#ifndef MSGQUEUE_H
#define MSGQUEUE_H


#include <vector>
#include <string>
#include <QDebug>
#include <queue>
#include <mutex>
/*这个消息队列可以按照消息类型存放消息， 也可以按照消息类型获取消息
    消息：ChatMsg
*/
class MsgQueue
{
public:
    static MsgQueue* GetInstance();
    void Push(int msg_type, const std::string& msg);
    void Pop(int msg_type, std::string* msg);
private:
    std::vector <std::queue<std::string>> _v_msg;
    MsgQueue();
    MsgQueue(const MsgQueue& m);
    /*保存队列唯一的实例化对象*/
    static MsgQueue* _instance;
};

#endif // MSGQUEUE_H
