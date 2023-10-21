#include <iostream> 
#include <memory>
#include <string>
using namespace std;

namespace bit
{
    template<class _Ty>
    class auto_ptr
    {
    public:
        auto_ptr(_Ty* _Ptr = 0):_Myptr(_Ptr)
        {
        }
    private:
        _Ty* _Myptr;
    };
}

template<class _Ty>
class Auto_ptr 
{
public:
    Auto_ptr(_Ty* _P=0):_Owns(_P!=0), _Ptr(_P)
    {}
    ~Auto_ptr()
    {
        if(_Owns)
        {
            delete _Ptr;
            _Ptr = nullptr;
        }
    }
    Auto_ptr(Auto_ptr<_Ty>& Y):_Owns(Y._Owns), _Ptr(Y.release())
    {}
    Auto_ptr<_Ty>& operator=(Auto_ptr& Y)
    {
        if(this != Y)
        {
            if(_Ptr != Y._Ptr)
            {
                if(_Owns)
                    delete _Ptr;
                _Owns = Y._Owns;
            }
            else if(Y._Owns)
            {
                _Owns = true;
            }
            _Ptr = Y.release();
        }
        return *this;
    }
public:
    _Ty& operator*()
    {
        return *_Ptr;
    }
    _Ty* operator->()
    {
        return _Ptr;
    }
    _Ty* release()
    {
        _Owns = false;
        return _Ptr; 
    }
private:
    bool _Owns;
    _Ty* _Ptr;
};

class Test
{
public:
    void fun()
    {
        cout << "Test::fun()" << endl;
    }

};
int main()
{
    int* ptr = new int(1);
    //代理思想
    auto_ptr<int> ap(ptr);
    cout << *ap << endl;
    auto_ptr<string> aps(new string("abc"));
    cout << aps->size() << endl;
    
    int* ptr0 = new int(1);
    Auto_ptr<int> atp(ptr0);
    cout << *atp << endl;
    Test* ptr1 = new Test();
    Auto_ptr<Test> atp1(ptr1);
    atp1->fun();
    return 0;
}
