#include <iostream>
using namespace std;

class CInt
{
public:
    CInt(int data = 2):m_data(data)
    {}
public:
    int GetSum(int times)
    {
        return m_data * times;
    }
private:
    int m_data;
};
class CFloat
{
public:
    CFloat(float data = 2.1):m_data(data)
    {}
public:
    float GetSum(float times)
    {
        return m_data * times;
    }
private:
    float m_data;
};

template<class T>
class TypeTraits//说明，可以什么都不写
{

};

template<>
class TypeTraits<CInt>
{
public:
    typedef int inPara;
    typedef int outPara;
};

template<>
class TypeTraits<CFloat>
{
public:
    typedef float inPara;
    typedef float outPara;
};

template<class _Ty>
class CApply
{
public:
    typename TypeTraits<_Ty>::outPara GetSum(_Ty& t, typename TypeTraits<_Ty>::inPara times)
    {
        return t.GetSum(times);
    }
};

int main()
{
    CInt i;
    CFloat f;
    cout << i.GetSum(3) << endl;;
    cout << f.GetSum(2.3) << endl;
    //萃取
    CApply<CInt> ci;
    CApply<CFloat> cf;
    cout << ci.GetSum(i, 3) << endl;
    cout << cf.GetSum(f,2.3) << endl;
    return 0;
}
