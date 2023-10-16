#include <iostream>
#include <bitset>

namespace bit 
{
    template<size_t _N>
    class My_bitmap
    {

    };
}
using namespace std;
int main()
{
    bitset<10> bt;
    cout << bt << endl;
    cout << sizeof(bt) << endl;
    bt.set(4);
    cout << bt << endl;
    bitset<10> bt1(123);
    cout << bt1 << endl;
    bt.flip(1);
    cout << bt << endl;//取反
    cout << bt.any() << endl;//任意一位为1则返回真
    cout << bt.none() << endl;//任意一位都不为1，则返回真
    cout << bt[2]<< endl;
    return 0;
}
