#pragma once 
#include <iostream>
#include <queue>
#include <pthread.h>
using namespace std;
/*
 * 线程池当中安全队列的元素类型
 *  1.待要处理的数据
 *  2.如何处理数据的方法
 * */
typedef void(*Handle)(int data);

class QueueData
{
public:
    QueueData()
    {

    }
    ~QueueData()
    {

    }
public:
    //该函数是提供给线程调用的
    void Run()
    {
        _handler(_data);
    }
private:
    int _data;
    Handle _handler;//函数指针保存处理数据的方法
};

class ThreadPool
{
public:
    ThreadPool()
    {
        pthread_mutex_init(&_lock, NULL);
        pthread_cond_init(&_cons_cond, NULL);
        pthread_cond_init(&_prod_cond, NULL);
        _thread_count = 10;
    }
    ~ThreadPool()
    {
        pthread_mutex_destroy(&_lock);
        pthread_cond_destroy(&_cons_cond);
        pthread_cond_destroy(&_prod_cond);

    }
public:
    //初始化线程池
    // 1.创建线程池的线程
    int OnInit()
    {
        int exit_thread_count = 0;
        for(int i = 0; i < _thread_count; i++)
        {
            pthread_t tid;
            int ret = pthread_create(&tid, NULL, thread_pool_start, (void*)this);
            if(ret < 0)
            {
                exit_thread_count++;
            }
        }
        _thread_count -= exit_thread_count;
        if(_thread_count <= 0)
        {
            return -1;
        }
        return _thread_count;
    }
    //线程入口函数，线程池中的线程执行的都是这个函数
    //创建线程的时候，将this指针通过入口函数传递进来
    static void* thread_pool_start(void* arg)//变成静态成员不会隐式传递*this,满足thread_create函数的参数要求
    {
        pthread_detach(pthread_self());
        ThreadPool* tp = (ThreadPool*)arg;
        while(1)
        {
            pthread_mutex_lock(&tp->_lock);
            while(tp->_que.empty())
            {
                pthread_cond_wait(&tp->_cons_cond, &tp->_lock);
            }
            QueueData qd;
            tp->Pop(&qd);
            qd.Run();
            pthread_mutex_unlock(&tp->_lock);
        }
    }
    void Push(const QueueData& qd)
    {

    }
    void Pop(QueueData* qd)
    {
        *qd = _que.front();
        _que.pop();
    }
private:
    queue<QueueData> _que;
    int _thread_count;
    //互斥
    pthread_mutex_t _lock;
    //同步
    pthread_cond_t _cons_cond;
    pthread_cond_t _prod_cond;
};
