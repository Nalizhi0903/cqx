#include <iostream>
using namespace std;

namespace bit
{
    template<class _Ty>
        class vector 
        {
        public:
            typedef _Ty* iterator;
            typedef const _Ty* const_iterator;
        public:
            vector():_start(nullptr), _finish(nullptr), _endOfStorage(nullptr)
            {}
            vector(int n, const _Ty& v = _Ty()): _start(nullptr), _finish(nullptr), _endOfStorage(nullptr)
            {
               reserve(n);
               while(n--)
               {
                   push_back(v);
               }
            }
        public:
            iterator begin()
            {
                return _start;
            }
            void push_back()
            {
                
            }
            size_t size()
            {
                return _finish - _start;
            }
            size_t capacity()const 
            {
                return _endOfStorage - _start;
            }
        public:
            void insert(iterator it, const _Ty& v = _Ty())
            {
                if(_finish == _endOfStorage)
                {
                    size_t offset = it - _start;
                    size_t new_capacity = capacity() == 0 ? 1 : capacity()*2;
                    reserve(new_capacity);
                    //扩容成功后，it会失效，需重新赋值
                    it = _start + offset;
                }
                iterator pos = _finish;
                while(pos != it)
                {
                    *pos = *(pos -1);
                    pos--;
                }
                *it = v;
                
            }
            void reserve(size_t n)
            {
                if(n > capacity())
                {
                    _Ty* new_start = new _Ty[n];
                    int old_size = size();
                    for(int i = 0; i < old_size; ++i)
                    {
                        new_start[i] = _start[i];
                    }
                    delete []_start;
                    _start = new_start;
                    _finish = _start + old_size;
                    _endOfStorage = _start + n;
                }
            }

        private:
            iterator _start;
            iterator _finish;
            iterator _endOfStorage;
        };
}

int main()
{
    bit::vector<int> v;
    v.insert(v.begin(), 5);
    cout << v.capacity() << endl;
    return 0;
}
