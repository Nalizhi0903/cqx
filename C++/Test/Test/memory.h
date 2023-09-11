#pragma once
#include <iostream>
#include <typeinfo>
using namespace std;
//�ռ�������
template<class _Ty>
_Ty* _My_Allocate(size_t _N, _Ty*)
{
    cout << typeid(_Ty).name() << endl;
    if (_N < 0)
        _N = 0;
    return ((_Ty*)operator new((size_t)_N * sizeof(_Ty)));
}

template<class _T1, class _T2>
void _My_Construct(_T1* _P, const _T2& _V)
{
    new((void*)_P) _T1(_V);
}

template<class _Ty>
void _My_Destroy(_Ty* _P)
{
    _P->~_Ty();
}

template<class _Ty>
class my_allocator
{
public:
    typedef size_t size_type;
    typedef _Ty* pointer;
public:
    //����ռ�
    pointer allocate(size_type _N, const void*)
    {
        return _My_Allocate(_N, (pointer)0);
    }
    char* _Charalloc(size_type _N)
    {
        return (_My_Allocate(_N, (char*)0));
    }
    //�ͷſռ�
    void deallocate(void* _P, size_type)
    {
        operator delete(_P);
    }

    //����Ĺ���
    void construct(pointer _P, const _Ty& _V)
    {
        _My_Construct(_P, _V);
    }

    //����Ĵݻ�
    void destroy(pointer _P)
    {
        _My_Destroy(_P);
    }
};
