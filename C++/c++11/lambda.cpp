#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;
class Test
{
    friend struct My_less;
public:
    Test(int data = 0):m_data(data)
    {

    }
public:
    bool operator<(const Test& t)const //重载小于号后，sort函数才可以对Test排序
    {
        return m_data < t.m_data;
    }
    bool operator>(const Test& t)const //重载大于号后，greater函数才能对Test使用
    {
        return m_data > t.m_data;
    }
private:
    int m_data;
};
struct My_less
{
    bool operator()(const Test& t1,const Test& t2)
    {
        return t1.m_data > t2.m_data;
    }
};
int main()
{
    vector<int> iv = {4,3,1,6,8};
    sort(iv.begin(), iv.end());
    auto it = iv.begin();
    while(it!=iv.end())
    {
        cout << *it << " ";
        it++;
    }
    cout << endl;
    sort(iv.begin(),iv.end(), greater<int>());
    it = iv.begin();
    while(it!=iv.end())
    {
        cout << *it << " ";
        it++;
    }
    cout << endl;
    vector<Test> ic = {4,6,2,3,1};
    sort(ic.begin(), ic.end());
    sort(ic.begin(),ic.end(),greater<Test>());
    sort(ic.begin(),ic.end(),My_less());
    []{};//最基本的lambda表达式
    [](int n)->void 
    {
        cout << "n = " << n << endl;
    }(10);
    auto f = [](int n)->void{cout<<"n = "<<n<<endl;};
    f(100);
    auto f1 = [](int a, int b)->int{return a+b;};
    cout << f1(4,8) << endl;
    int k = 1, m = 2;
    auto f2 = [k , m]()->int{return k+m;};//不可修改k，m
    int x = 0, y = 0;
    auto f3 = [x,y](int a, int b)mutable->int{x=1000;y=20000;return a+b+x+y;};//mutable可以消除常性使参赛可以修改
    cout << f2() << endl;
    cout << f3(4,5) << endl;
    return 0;
}
