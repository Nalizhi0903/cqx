#include <iostream>
#include <string>
#include <vector>
using namespace std;
//开散列 闭散列 除留余数法+链地址
enum State{EMPTY, EXIST, DELETE};

template<class K, class V>
class HashTable
{
public:
    struct Elem 
    {
        pair<K,V> _val;
        State     _state;
    };
    int HashFun()
    {

    }
public:
    HashTable(size_t capacity = 13):_ht(capacity),_size(0)
    {
        for(int i = 0; i<= 13; i++)
        {
            _ht[i]._state = EMPTY;
        }
    }
    bool Insert(const pair<K,V> &v)
    {
        if(_size >= _ht.capacity())
            return false;
        //计算hash地址
        size_t index = HashFun();
        while(_ht[index]._state == EXIST)
        {
            //线性探测
            if(v == _ht[index]._val)
                return false;
            index = (index + 1) % _ht.capacity();
        }
        Elem e = {v, EXIST};
        _ht[index] = e;
        _size++;
    }
private:
    vector<Elem> _ht;
    size_t       _size;
};

int main()
{
    HashTable<int, int> hTable;
    vector<int> v = { 4,5,7,1,6,9 };

    return 0;
}
