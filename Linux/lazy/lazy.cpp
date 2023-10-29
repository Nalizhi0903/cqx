#include <iostream>
#include <stdio.h>
#include <mutex>
using namespace std;
std::mutex g_lock;
class Data
{
    public:
        static Data* GetInstance();
        void Print()
        {
            cout << "Hello Data" << endl;
        }
    private:
        Data();
        static Data* _d;
};
Data::Data()
{

}
Data* Data::_d = nullptr;

Data* Data::GetInstance()
{
    //存在线程安全问题
    //加锁
    if(_d == nullptr)
    {
        g_lock.lock();
        if(_d == nullptr)
        {
            _d = new Data();
        }
        g_lock.unlock();
    }
    return _d;
}
int main()
{
    Data* d = Data::GetInstance();
    Data* dd = Data::GetInstance();
    d->Print();
    cout << d << endl;
    cout << dd << endl;
    return 0;
}
