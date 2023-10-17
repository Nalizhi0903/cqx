#include <iostream>
#include <typeinfo>
#include <string>
#include <string.h>
#include <forward_list>
using namespace std;
class String 
{
public:
    String(const char* str = "")
    {
       m_data = new char[strlen(str)+1]; 
       strcpy(m_data, str);
    }
    String(const String& s)
    {
        m_data = new char[strlen(s.m_data)+1];
        strcpy(m_data, s.m_data);
    }
    //移动构造
    String(String &&s)
    {
        m_data = s.m_data;
        s.m_data = nullptr;
    }
    ~String()
    {}
    String operator+(const String& s1)
    {
        char* pTemp = new char[strlen(m_data)+strlen(s1.m_data)+1];
        strcpy(pTemp,m_data);
        strcpy(pTemp + strlen(m_data), s1.m_data);
        String tmp(pTemp);
        return tmp;
    }
private:
    char* m_data;
};
class Test
{
public:
    Test(int d):m_data(d)
    {

    }
    Test operator=(const Test &) = delete;//c++11,delete后可以杜绝调用函数
protected:
    Test(const Test&);//放入protected里，杜绝调动拷贝构造函数
private:
    int m_data;
};
void* GetMemory(size_t size)
{
    return malloc(size);
}
int fun(int a, int b)
{
    int sum = a+b;
    return sum;
}
int main()
{
    int a = 10;
    double c = 12.3;
    decltype(a+c) x;
    cout << typeid(x).name()<< endl;
    cout << typeid(decltype(GetMemory)).name() << endl;
    cout << typeid(decltype(GetMemory(0))).name() << endl;
    forward_list<int> fl = {1,2,3,4,5,6,7};
    auto it = fl.begin();
    cout << *it << endl;
    int &&b = 10;//右值引用
    cout << b << endl;
    const int& res = fun(1,3);
    cout << res << endl;
    String s1("abc");
    String s2("xyz");
    String s3(s1 + s2);
    const int p = 10;
    const int&& d = move(p);//move将左值强转为右值
    String s4(move(s1));//s1.m_data变为空移动到s4
    cout << d << endl;
    return 0;
}
