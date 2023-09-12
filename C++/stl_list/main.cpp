#include "memory.h"

namespace bit
{
    template<class _Ty, class _A = my_allocator<_Ty> >
    class list
    {
    public:
        typedef _Ty value_type;
        typedef _Ty* pointer_type;
        typedef _Ty& reference_type;
        typedef const _Ty* const_pointer_type;
        typedef const _Ty& const_reference_type;
        typedef size_t size_type;
    public:
        struct _Node;
        typedef struct _Node* _Nodeptr;
        struct _Node
        {
            _Ty _Value;
            _Nodeptr _Next;
            _Nodeptr _Prev;
        };
        struct _Acc
        {
            typedef _Nodeptr& _NodePref;
            static _NodePref _Next(_Nodeptr _P)
            {
                return _P->_Next;
            }
            static _NodePref _Prev(_Nodeptr _P)
            {
                return _P->_Prev;
            }
            static reference_type _Value(_Nodeptr _P)
            {
                return _P->_Value;
            }
        };
    public:
        //迭代器
        class iterator
        {
        public:
            iterator() {}
            iterator(_Nodeptr _P) :_Ptr(_P)
            {}
        public:
            iterator& operator++()
            {
                _Ptr = _Acc::_Next(_Ptr);
                return *this;
            }
            iterator operator++(int)
            {
                iterator tmp = *this;
                _Ptr = _Acc::_Next(_Ptr);
                return tmp;
            }
            iterator& operator--()
            {
                _Ptr = _Acc::_Prev(_Ptr);
                return *this;
            }
            iterator& operator--(int)
            {
                iterator tmp = *this;
                _Ptr = _Acc::_Prev(_Ptr);
                return tmp;
            }
            _Ty& operator*()
            {
                return _Acc::_Value(_Ptr);
            }
            bool operator!=(const iterator& it)
            {
                return _Ptr != it._Ptr;
            }
            bool operator==(const iterator& it)
            {
                return _Ptr == it._Ptr;
            }
        public:
            _Nodeptr _Mynode()const
            {
                return _Ptr;
            }
        private:
            _Nodeptr _Ptr;
        };
    public:
        explicit list() :_Head(_Buynode()), _size(0)
        {
            _size = 0;
        }
    public:
        iterator begin()
        {
            return iterator(_Acc::_Next(_Head));
        }
        iterator end()
        {
            return iterator(_Head);
        }
    public:
        void push_back(const value_type& v)
        {
            insert(end(), v);
        }
        void push_front(const value_type& v)
        {
            insert(begin(), v);
        }
    public:
        iterator insert(iterator _P, const _Ty& _X = _Ty())
        {
            _Nodeptr _S = _P._Mynode();
            _Acc::_Prev(_S) = _Buynode(_S, _Acc::_Prev(_S));
            _S = _Acc::_Prev(_S);
            _Acc::_Next(_Acc::_Prev(_S)) = _S;
            allocator.construct(&_Acc::_Value(_S), _X);
            ++_size;
            return (iterator(_S));

        }
    protected:
        _Nodeptr _Buynode(_Nodeptr _Narg = 0, _Nodeptr _Parg = 0)
        {
			_Nodeptr _S = (_Nodeptr)allocator._Charalloc(sizeof(_Node));
			_Acc::_Next(_S) = _Narg != 0 ? _Narg : _S;
			_Acc::_Prev(_S) = _Parg != 0 ? _Parg : _S;
			return _S;
        }
    private:
        _Nodeptr _Head;
        size_type _size;
        _A allocator;
    };
}

int main()
{
    bit::list<int> mylist;
    for (int i = 1; i <= 5; ++i)
    {
        //mylist.push_back(i);
        //mylist.push_front(i);
        mylist.insert(mylist.begin(), i);
    }

    bit::list<int>::iterator it = mylist.begin();
    while (it != mylist.end())
    {
        cout << *it << "-->";
        //++it; 
        it++;
    }
    return 0;
}
