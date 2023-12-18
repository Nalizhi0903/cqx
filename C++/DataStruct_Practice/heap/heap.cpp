#include <iostream>
#include <assert.h>
#define HeapElemType int
using namespace std;

typedef struct Heap
{
  HeapElemType* hp;
  size_t capacity;
  size_t size;
}Heap;

void HeapInit(Heap* php, int sz);
void HeapInsert(Heap* php, HeapElemType v);
bool HeapFull(Heap* php)
{
  return php->size >= php->capacity;
}
void AdjustUp(Heap* php, int start);
void HeapInit(Heap* php, int sz)
{
  php->capacity = sz;
  php->hp = (HeapElemType*)malloc(sizeof(HeapElemType)*php->capacity);
  assert(php->hp!=nullptr);
  php->size = 0;
}
void HeapInsert(Heap* php, HeapElemType v)
{
  if(HeapFull(php))
  {
    cout << "堆空间已满，不能插入" << endl;
  }
  php->hp[php->size] = v;
  AdjustUp(php, php->size);
  php->size++;
}
void AdjustUp(Heap* php, int start)
{
  int j = start;
  int i = (j - 1) / 2;
  while(j > 0)
  {
    if(php->hp[j] < php->hp[i])
    {
      HeapElemType tmp = php->hp[j];
      php->hp[j] = php->hp[i];
      php->hp[i] = tmp;
      
      j = i;
      i = (j-1) / 2;
    }
    else 
      break;
  }
}
void HeapShow(Heap* php)
{
  for(size_t i = 0; i < php->size; i++)
  {
    cout << php->hp[i] << endl;
  }
}
int main()
{
  int ar[] = {27,15,19,18,28,34,65,49,25,37};
  int n = sizeof(ar) / sizeof(ar[0]);
  Heap hp;
  HeapInit(&hp, 16);
  for(int i = 0; i < n; i++)
  {
    HeapInsert(&hp, ar[i]);
  }
  HeapShow(&hp);
  return 0;
}
