#include <iostream>
using namespace std;

class Person
{
    //静态的多态是静态绑定即重载
public:
    virtual void BuyTicket()
    {
        cout << "Buy FUll-PriceTicket" << endl;
    }
};

class student:public Person 
{
public:
    virtual void BuyTicket()
    {
        cout << "Buy Half-PriceTicket" << endl;
    }
};

void fun(Person& p)//动态的多态：晚期绑定（动态绑定）
{
    p.BuyTicket();
}


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

class Father
{
public:
    virtual void fun1()
    {
        cout << "Father::fun1()" << endl;
    }
    virtual void fun2()
    {
        cout << "Father::fun2()" << endl;
    }
};

class Son:Father 
{
public:
    virtual void fun3()
    {
        cout << "Son:fun3()" << endl;
    }
};

typedef void(*pFun_t)();

int main()
{
    Son f;
    cout << "对象地址" << &f << endl;
    cout << "虚表地址" << *(int*)&f << endl;//将地址强转为指针，int指针转为四个字节，*取对象地址前四个字节的内容即虚表的地址
    cout << "第一个函数的地址" << *(int*)*(int*)(&f) << endl;
    cout << "第二个函数的地址" << (*(int*)*(int*)(&f))+1 << endl;
    void(*pfun)() = (pFun_t)*(int*)*(int*)(&f);
    pfun();

    pfun = (pFun_t)*((int*)*(int*)(&f) + 1);
    pfun();
    return 0;
    
}
