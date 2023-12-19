#include <iostream>
#include <vector>
using namespace std;
//「冒泡排序 bubble sort」通过连续地比较与交换相邻元素实现排序。这个过程就像气泡从底部升到顶部一样，因此得名冒泡排序。
void bubble_sort(vector<int>& vt)
{
  int n = vt.size();
  for(int i = 1; i < n - 1; i++)
  {
    for(int j = 0; j < n -i; j++)
    {
      if(vt[j] > vt[j+1])
      {
        swap(vt[j], vt[j+1]);
      }
    }
  }
}
//时间复杂度O(n^2), 空间复杂度O(1)
int main()
{
  vector<int> vt = {3,6,7,9,2,1,4,5};
  bubble_sort(vt);
  for(auto&e : vt)
  {
    cout << e << endl;
  }
  return 0;
}
