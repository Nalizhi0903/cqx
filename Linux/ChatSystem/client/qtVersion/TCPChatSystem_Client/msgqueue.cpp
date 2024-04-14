#include "msgqueue.h"
#include "windows.h"
std::mutex g_que;

MsgQueue* MsgQueue::_instance = nullptr;

MsgQueue* MsgQueue::GetInstance()
{
    g_que.lock();
    if (_instance == nullptr)
    {
        _instance = new MsgQueue();
    }
    g_que.unlock();
    return _instance;
}

void MsgQueue::Push(int msg_type, const std::string& msg)
{
    g_que.lock();
    _v_msg[msg_type].push(msg);
    g_que.unlock();
}

void MsgQueue::Pop(int msg_type, std::string* msg)
{
    if (_v_msg[msg_type].empty())
    {
        Sleep(100);
    }
    if(_v_msg[msg_type].empty())
        return;
    g_que.lock();
    *msg = _v_msg[msg_type].front();
    _v_msg[msg_type].pop();
    g_que.unlock();
}

MsgQueue::MsgQueue()
{
    _v_msg.resize(100);
}

