#include <iostream>
using namespace std;

namespace bit
{
    template<class _Ty>
    struct ListNode
    {
        ListNode(_Ty v = _Ty()) : _value(v), _next(nullptr), _prev(nullptr) //初始化v为0
        {}
        _Ty _value;
        ListNode<_Ty>* _next;
        ListNode<_Ty>* _prev;
    };

    template<class _Ty>
    class ListIterator
    {
    public:
        typedef ListNode<_Ty> Node;
    public:
        ListIterator(Node* ptr = nullptr) : Ptr(ptr)
        {
        }
        Node* MyNode()
        {
            return Ptr;
        }
    private:
        ListNode<_Ty>* Ptr;
    };


    template<class _Ty>
    class List
    {
    public:
        typedef ListNode<_Ty> Node;
        typedef Node* PNode;
    public:
        typedef ListIterator<_Ty> iterator;
    public:
        List()
        {
            CreateHead();
        }
        iterator begin()
        {
            return iterator(_Head->_next);
        }
        iterator insert(iterator pos, const _Ty v)
        {
            Node* s = new Node(v);
            Node* cur = pos.MyNode();
            s->_next = cur;
            s->_prev = cur->_prev;
            s->_next->_prev = s;
            s->_prev->_next = s;
            return s;
        }
        iterator end()
        {
            return iterator(_Head);
        }
        void push_back(const _Ty& v)
        {
            insert(end(), v);
        }
    private:
        void CreateHead()
        {
            _Head = new Node;
            _Head->_next = _Head;
            _Head->_prev = _Head;
        }
        PNode _Head;
    };
}



int main()
{
    bit::List<int> mylist;
    bit::List<int>::iterator pos = mylist.begin();
    for (int i=0; i <= 5; i++)
    {
        mylist.push_back(i);
    }
    return 0;
}
