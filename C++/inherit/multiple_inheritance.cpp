#include <iostream>
using namespace std;

class Base
{
public:
    int m_base =  1;
};
//虚拟继承可以解决二义性和数据冗余
class A:virtual public Base //虚基类
{
public:
    int m_a =  1;
};

class B:virtual public Base
{
public:
    int m_b =  1;
};

class D:public A, public B//菱形继承
{
public:
    int m_d =  1;
};

int main()
{
    A a;
    cout << a.m_base << endl;
    B b;
    cout << b.m_base << endl;
    D d;
    cout << d.m_base << endl;
    //cout << d.A::m_base << endl;//菱形继承会有数据冗余和二义性，A与B都有m_base，d访问m_base时需要指明是那个类的m_base
    return 0;
}
