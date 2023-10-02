#include <iostream>
using namespace std;
//多态的实现，一、继承关系 二、虚函数 三、三同 四、用父类的指针或引用调用函数
class Animals
{
public:
    virtual void Eat()//虚函数
    {
        cout << "A::Eat()" << endl;
    }
    virtual void Walk()
    {
        cout << "A::Eat()" << endl;
    }
    virtual void Sleep()
    {
        cout << "A::Eat()" << endl;
    }
};
//多态的意义 相同的接口实现不同的功能
class Dog:public Animals 
{
public:
    virtual void Eat()//重写父类的虚函数 三同：名字相同，返回值相同，参数列表相同
    {
        cout << "Dog::Eat()" << endl;
    }   
    virtual void Walk()
    {
        cout << "Dog:Walk()" << endl;
    }
    virtual void Sleep()
    {
        cout << "Dog::Eat()" << endl;
    }
};

class Person:public Animals 
{
public:
    virtual void Eat()
    {
        cout << "Person::Eat()" << endl;
    }   
    virtual void Walk()
    {
        cout << "Person:Walk()" << endl;
    }
    virtual void Sleep()
    {
        cout << "Person::Eat()" << endl;
    }
};

void Active(Animals *pa)//晚期绑定
{
    pa->Eat();
    pa->Walk();
    pa->Sleep();
}

int main()
{
    Dog d;
    Person p;
    Active(&d);
    Active(&p);
    Animals &ref = d;
    ref.Eat();
    return 0;
}

/*
class Base 
{
public:
    void fun()
    {
        cout << "Base::fun()" << endl;
    }
};

class D:public Base 
{
public:
    void fun()
    {
        cout << "D::fun()" << endl;;
    }
};

int main()
{
    D d;
    Base* pb = &d;//父类指针只操作子类中的父类部分
    pb->fun();
    return 0;
}*/
