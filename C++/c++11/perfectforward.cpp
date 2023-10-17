#include <iostream>
using namespace std;

void Fun(int &t)
{
    cout << "int &" << t << endl;
}
void Fun(int &&t)
{
    cout << "int &&" << t << endl;
}
void Fun(const int &t)
{
    cout << "const int &" << t << endl;
}
void Fun(const int &&t)
{
    cout << "const int &&" << t << endl;
}
template<typename T>
void PerfectForward(T &&t)
{
    Fun(forward<T>(t));
}

int main()
{
    PerfectForward(10);
    int a = 10;
    PerfectForward(a);
    const int& x = 10;
    PerfectForward(x);
    const int&& y = 10;
    PerfectForward(move(y));
    return 0;
}
