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

    }
    void Push(const QueueData& qd)
    {

    }
    void Pop(QueueData* qd)
    {

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
