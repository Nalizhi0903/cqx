#include <iostream>
using namespace std;

class Base
{
private:
    void Show()
    {
        cout << "Base::Base" << endl;
    }
protected:
    void Hello()
    {
        cout << "Hello" << endl;
    }
private: 
    int m_a;
};

class D:public Base
{
public:
    D() :m_d(5)
    {}
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
    Base B;
    D d;

    //子类对象可以直接赋值给父类对象
    B = d;
    
    //d = B;父类对象不可以给子类对象赋值
    
    //子类对象的地址可以直接给父类指针赋值
    Base* pb = &d;

    //子类对象可以直接初始化父类的引用
    Base &rb = d;


    return 0;
}
