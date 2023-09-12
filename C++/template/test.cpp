#include <iostream>
#include <typeinfo>
using namespace std;
//模版效率不高，要根据类型实例化函数
template<typename Type>
Type fun(Type a, Type b)
{
    cout << typeid(Type).name() << "result is " << a + b << endl;
    return a + b;
}

template<typename Type1, typename Type2>
Type1 fun1(Type1 a, Type2 b)
{
    return Type1(a + b);
}

template<typename Type>
void fun2()//零初始化
{
    Type x = Type();
}

int main()
{
    int res = fun(10,20);

    char res1 = fun('A', 'B');

    double res2 = fun(12.3, 23.4);
    
    //fun(10, 12.3);Type是相同的类型fun()不可以编译成功，不能发生二异性
    fun1(10, 12.3);
    fun(10,(int)12.3);
    fun<int>(10, 12.3);//显式转换，给模版传参赛是尖括号，给函数传函数是小括号
    fun2<int>();//零初始化
    return 0;
}
