#include <iostream>
using namespace std;

class Car
{
public:
    virtual void Drive() final //final 不允许重写
    {}
    virtual void Drivefun()
    {

    }
};

class Benz:public Car 
{
public:
    virtual void Drivefun() override//override 要重写 
    {
        cout << "Benz-舒适" << endl;
    }
    
};

class Base1
{
public:
    Base1()//多态在父类的构造函数中失效
    {
        cout << "Base::Base()" << endl;
        this->fun();
    }
    ~Base1()
    {
        cout << "Base::~Base()" << endl;
    }
    void fun()
    {
        cout << "Base::fun()" << endl;
    }
};
class Base2
{
public:
    Base2()
    {
        cout << "Base::Base()" << endl;
    }
    ~Base2()
    {
        cout << "Base::~Base()" << endl;
    }
};

class D:public Base1, virtual public Base2 //实例化顺序按照，继承的顺序，若有虚继承则先调用虚继承，和初始化顺序无关
{

};
int main()
{
    return 0;
}
