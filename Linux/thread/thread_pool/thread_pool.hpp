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
    QueueData(int data, Handle fun):_data(data), _handler(fun)
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
    ThreadPool(int thread_count, int capacity = 10):_thread_count(thread_count), _capacity(capacity), _exit_flag(0)
    {
        pthread_mutex_init(&_lock, NULL);
        pthread_cond_init(&_cons_cond, NULL);
        pthread_cond_init(&_prod_cond, NULL);
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
            while(tp->_que.empty())//如果while都换成if的话，那么线程1、2都被唤醒了，但是，此时应该线程1继续等待才对，换成while的话 就可避免了
            {
                if(tp->_exit_flag)
                {
                    pthread_mutex_unlock(&tp->_lock);
                    tp->_thread_count--;
                    pthread_exit(NULL);
                }
                pthread_cond_wait(&tp->_cons_cond, &tp->_lock);
            }
            QueueData qd;
            tp->Pop(&qd);
            pthread_mutex_unlock(&tp->_lock);
            pthread_cond_signal(&tp->_prod_cond);
            qd.Run();
        }
    }
    void Push(const QueueData& qd)
    {
        pthread_mutex_lock(&_lock);
        if(_exit_flag)
        {
            pthread_mutex_unlock(&_lock);
            return;
        }
        while((int)_que.size() > _capacity)
        {
            pthread_cond_wait(&_prod_cond, &_lock);
        }
        _que.push(qd);
        pthread_mutex_unlock(&_lock);
        pthread_cond_signal(&_cons_cond);
    }
    void Pop(QueueData* qd)
    {

        *qd = _que.front();
        _que.pop();
    }
    void ThreadPoolExit()
    {
        _exit_flag = 1;
        //方法一
        while(_thread_count > 0)
        {
            pthread_cond_signal(&_cons_cond);
        }
        //方法二
        //pthread_cond_broadcast(&_cons_cond);
    }
private:
    queue<QueueData> _que;
    int _thread_count;
    int _capacity;
    int _exit_flag;
    //互斥
    pthread_mutex_t _lock;
    //同步
    pthread_cond_t _cons_cond;
    pthread_cond_t _prod_cond;
};
