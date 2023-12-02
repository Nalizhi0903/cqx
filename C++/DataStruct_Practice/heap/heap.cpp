#include <iostream>
#include <vector>
using namespace std;

class Heap
{
public:
  Heap():_arr(nullptr), _capacity(0), _size(0)
  {}
  Heap(size_t capacity):_capacity(capacity), _size(0)
  {
    _arr = new int(capacity); 
  }
  ~Heap()
  {
    delete _arr;
  }
public:
  bool InsertHeap(int data)
  {
    
    return true;
  }
private:
  int* _arr;
  size_t _capacity;
  size_t _size;
};

int main()
{
  vector<int> vt = {3, 6, 7, 4, 9, 14, 2};
  return 0;
}
