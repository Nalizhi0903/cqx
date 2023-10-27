#pragma once
#include <iostream>
#include <queue>
#include <pthread.h>
using namespace std;

class MsgQueue
{
public:
    MsgQueue():_capacity(10)
    {
        pthread_mutex_init(&_q_lock, NULL);
        pthread_cond_init(&_cons_cond, NULL);
        pthread_cond_init(&_prod_cond, NULL);
    }
    ~MsgQueue()
    {
        pthread_mutex_destroy(&_q_lock);
        pthread_cond_destroy(&_cons_cond);
        pthread_cond_destroy(&_prod_cond);
    }
public:
    void Push(int data)
    {
        pthread_mutex_lock(&_q_lock);
        if((int)_que.size() >= _capacity)
        {
            pthread_cond_wait(&_prod_cond, &_q_lock);
        }
        _que.push(data);
        pthread_mutex_unlock(&_q_lock);
        pthread_cond_signal(&_cons_cond);
    }
    int Pop()
    {
        pthread_mutex_lock(&_q_lock);
        if(_que.size() <= 0)
        {
            pthread_cond_wait(&_cons_cond, &_q_lock);
        }
        int tmp = _que.front();
        _que.pop();
        pthread_mutex_unlock(&_q_lock);
        pthread_cond_signal(&_prod_cond);
        return tmp;
    }
private:
    queue<int> _que;
    int _capacity;
    //互斥锁
    pthread_mutex_t _q_lock;
    //生产者的条件变量
    pthread_cond_t _cons_cond;
    //生产者的条件变量
    pthread_cond_t _prod_cond;
};

