#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <queue>
using namespace std;

template<class T1, class T2>
class Data
{
public:
    Data()
    {}
private:
    T1 Data1;
    T2 Data2;
};
//全特化
template<>
class Data<int, char>
{
public:
    Data()
    {}
private:
    int Data1;
    char Data2;
};

//部分特化
template<class T1>
class Data<int, T1>
{
public:
    Data()
    {}
private:
    int Data1;
    T1 Data2;
};


//泛化版本
template<class T> 
bool IsEqual(T& left, T& right)
{
    return left == right;//strcmp(left, right)
}

//模版的特化 ---特殊化
template<> 
bool IsEqual<const char *>(const char*& left, const char*& right)
{
    return left == right;//strcmp(left, right)
}

int main()
{
    int a = 10;
    int b = 20;
    IsEqual(a, b);
    const char* ch1 = "Hello";
    const char* ch2 = "Hello";
    cout << IsEqual(ch1, ch2) << endl;
}

/*
//类型模版参数   非类型模版参数
template<class _Ty, size_t _N>
class SeqList
{
public:
    SeqList(int sz = _N)
    {
        capacity  = sz > _N ? sz : _N;
        base =new _Ty[capacity];
        size = 0;
    }
private:
    _Ty* base;
    size_t capacity;
    size_t size;
};

int main()
{
    SeqList<int, 10> s;
    return 0;
}*/
