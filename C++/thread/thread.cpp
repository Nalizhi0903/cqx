#include <iostream>
#include <Windows.h>
#include <thread>
#include <mutex>
#include <atomic>
using namespace std;
unsigned long sum = 0;
atomic_long sum_ato = 0;//原子类型
//atomic<long> sum;
mutex mt;
void fun(size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        mt.lock();
        sum++;//原子操作区 //临界区
        mt.unlock();
    }
}

void atomic_fun(size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        //自动的互斥访问，无需对原子类型加锁解锁
        sum_ato++;//原子操作区 //临界区
     }
}


class MyThread
{
public:
    ~MyThread()
    {
        if (m_t.joinable())
        {
            m_t.join();
        }

    }
private:
    thread m_t;
};


class threadObject
{
public:
    void operator()(int n)
    {
        for (int i = 0; i < n; i++)
        {
            cout << i << endl;
        }
    }
};

void main()
{
    //lambda方式调动
    thread th([](int n)->void 
        {
            for (int i = 0; i < n; i++)
            {
                cout << i << endl;
            }
        }, 10);
    //线程对象调用
    threadObject tb;
    thread th1(tb, 10);
    Sleep(1000);
    if (th.joinable())
    {
        cout << "OK" << endl;
    }
    else
    {
        cout << "ShutDown" << endl;
    }
    th.join();//阻塞等待
    if (th.joinable())
    {
        cout << "OK" << endl;
    }
    else
    {
        cout << "ShutDown" << endl;
    }
    th1.join();


    thread th3(fun, 10000);
    thread th4(fun, 10000);
    th3.join();
    th4.join();
    cout << sum << endl;

}


