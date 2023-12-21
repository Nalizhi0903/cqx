#include <iostream>
#include <vector>
using namespace std;
//建堆有向上调整和向下调整两种方法
void adjust_up(vector<int>& vt, int start)
{
  int i = start;
  int j = (i - 1) / 2;
  while(i > 0)
  {
    if(vt[j] < vt[i])
    {
      int tmp = vt[i];
      vt[i] = vt[j];
      vt[j] = tmp;
      i = j;
      j = (i - 1) / 2;
    }
    else 
      break;
  }
}

void heap_sort(vector<int>& vt)
{
  //建堆 时间复杂度O(n)
  for(int i =  vt.size() - 1; i > 0; i--)
  {
    adjust_up(vt, i);
  }
  //排序 时间复杂度O(logn)
  for(int i = vt.size() - 1; i > 0 ;i--)
  {
    //将第一个元素交换到后面已经排序的区域
    swap(vt[0], vt[i]);
    //将为排序的区域调整成新的大堆
    adjust_up(vt, i - 1);
  }
}
//时间复杂度O(nlogn) 因为建堆的复杂度为O(n) 排序的复杂度为O(logn)
int main()
{
  vector<int> vt = {5,7,2,4,8};
  heap_sort(vt);
  for(auto& e : vt)
  {
    cout << e << endl;
  }
  return 0;
}
