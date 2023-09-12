//顺序表
#include <iostream>
using namespace std;
template<typename Type>
class SeqList
{
public:
    SeqList(int sz = SEQ_LIST_DEFAULT_SIZE);
    ~SeqList();
public:
    void show_size();
    void show_capacity();
    void push_back(const Type& v);
private:
    enum{ SEQ_LIST_DEFAULT_SIZE = 8 };
private:
    Type* base;
    size_t capacity;
    size_t size;
};

template<typename Type>
SeqList<Type>::SeqList(int sz)
{
    capacity = sz >SEQ_LIST_DEFAULT_SIZE ?sz :SEQ_LIST_DEFAULT_SIZE;
    base = new Type[capacity];
    size = 0;
}

template<typename Type>
SeqList<Type>::~SeqList()
{
    delete []base;
    base = NULL;
    capacity = size = 0;
}

template<typename Type>
void SeqList<Type>::show_size()
{
    cout << size << endl;;
}

template<typename Type>
void SeqList<Type>::show_capacity()
{
    cout << capacity << endl;;
}

template<typename Type>
void SeqList<Type>::push_back(const Type& v)
{

}
