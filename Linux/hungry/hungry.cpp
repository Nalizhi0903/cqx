#include <iostream>
#include <stdio.h>
using namespace std;

class Singleton
{
    public:
        static Singleton* GetInstance();//属于类，不属于对象，可以通过类进行调用
        void Print()
        {
            printf("Hello Singleton\n");
        }
    private:
        Singleton();//构造为私有的
        static Singleton* _sig;
};

Singleton* Singleton::GetInstance()
{
    return _sig;
}
Singleton* Singleton::_sig = new Singleton();//程序启动的时候初始化对象
//由于程序启动的时候，就实例化单例类的对象，所以不会存在线程安全问题，当单例类的业务非常复杂的时候，启动的时候非常慢
Singleton::Singleton()
{

}

int main()
{
    Singleton* s = Singleton::GetInstance();
    s->Print();
    return 0;
}
