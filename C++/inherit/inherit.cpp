#include <iostream>
using namespace std;

class A
{
friend ostream& operator<<(ostream& out ,const A& a);
friend void print(const A& a);//友元不具有传递性
public:
    A(int a):m_a(a)
    {}
public:
    static void fun()//供所有对象共享，用类名就可以直接调用，不需要对象调用,A::fun()
    {}
private:
    int m_a;
    static int m_b;
};

int A::m_b = 2;//静态成员要在类的作用域外初始化,所有对象共享

void print(const A& a)
{
    cout << a.m_a << endl;
}

class Test:A
{
public:
    Test(int data):m_data(data),A(3)
    {}
private:
    int m_data;
};

class Base
{
public:
    Base(int a)
    {}
    Base(const Base& b)
    {
        m_a = b.m_a;
    }
    Base& operator=(const Base& b)
    {
        if(this != &b)
            cout << "Base::operator=(const Base&)" << endl;
        return *this;
    }
    ~Base()
    {
        cout << "Base::~Base()" << endl;
    }
public:
    void show(int a)
    {
        cout << "Base::Base" << endl;
    }
protected:
    void Hello()
    {
        cout << "Hello" << endl;
    }
private:
    void fun()
    {
        cout << "private fun()" << endl;
    }
private: 
    int m_a;
};

class D:public Base
{
public:
    D() :Base(3)//父类有构造函数参数，则要在子类构造函数初始化，若父类有默认的构造参数，则不需要
    {}
    D(const D& d):Base(d)//子类调动拷贝构造函数也会调动父类的拷贝构造函数
    {
        cout << "D::D(const D&)" << endl;
    }
    D operator=(const D& d)
    {
        if(this!=&d)
        {
            Base::operator=(d);
            cout << "D::operator=(const D&)" << endl;
        }
        return *this;
    }
    ~D()
    {
        cout << "D::~D()" << endl;//在调动子类的析构函数前调用父类的析构函数
    }
public:
    void show()
    {
        cout << m_d << endl;
        //Show();//private不能被子类访问
        Hello();//protect可以被子类访问
    }
private:
    int m_d;
};
//赋值兼容规则
int main()
{
    Base B(3);
    D d;

    //子类对象可以直接赋值给父类对象
    B = d;
    
    //d = B;父类对象不可以给子类对象赋值
    
    //子类对象的地址可以直接给父类指针赋值
    Base* pb = &d;

    //子类对象可以直接初始化父类的引用
    Base &rb = d;
    
    d.show();
    d.Base::show(8);//函数隐藏，与子类同名的父类函数会被隐藏
    return 0;
}
