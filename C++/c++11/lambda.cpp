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
    return 0;
}
