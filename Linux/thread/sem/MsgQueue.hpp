#pragma once
#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <vector>
using namespace std;
#define CAPACITY 4
class MsgQueue
{
public:
    MsgQueue():_vec(CAPACITY), _capactiy(CAPACITY), _w_pos(0), _r_pos(0)
    {
        sem_init(&_lock, 0, 1);
        //对与消费者，初始化的时候，没有任何有效元素
        sem_init(&_cons_sem, 0, 0);
        sem_init(&_prod_sem, 0, CAPACITY);
    }
    ~MsgQueue()
    {
        sem_destroy(&_lock);
        sem_destroy(&_cons_sem);
        sem_destroy(&_prod_sem);
    }
public:
    void Push(int data)
    {
        sem_wait(&_prod_sem);
        sem_wait(&_lock);
        _vec[_w_pos] = data;
        _w_pos = (_w_pos + 1) % CAPACITY;
        sem_post(&_lock);
        sem_post(&_cons_sem);
    }
    int Pop()
    {
        sem_wait(&_cons_sem);
        sem_wait(&_lock);
        int tmp = _vec[_r_pos];
        _r_pos = (_r_pos + 1) % CAPACITY;
        sem_post(&_lock);
        sem_post(&_prod_sem);
        return tmp;
    }
private:
    vector<int> _vec;
    size_t _capactiy;

    //互斥
    sem_t _lock;
    //同步
    sem_t _cons_sem;
    sem_t _prod_sem;
    //读写位置
    int _w_pos;
    int _r_pos;
};
