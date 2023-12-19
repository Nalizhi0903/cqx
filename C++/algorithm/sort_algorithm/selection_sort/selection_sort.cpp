#include <iostream>
#include <vector>

using namespace std;
//选择排序
//选取区间【0，n-1】中的最小元素，将其与0处的元素交换
//选取区间【1，n-1】中的最小元素，将其与1处的元素交换
//以此类推，经过n-1轮选择与交换后，叔祖前n-1个元素已排序，仅剩的一个元素必定是最大的元素，无需排序，数组排序完成
void selection_sort(vector<int>& vt)
{
  int n = vt.size();
  for(int i = 0; i < n - 1; i++)
  {
    int tmp = i;
    for(int j = i; j < n; j++)
    {
      if(vt[tmp] > vt[j])
      {
        tmp = j;
      }
    }
    swap(vt[i], vt[tmp]);
  }
}
//算法特性：时间复杂度为O(n^2) 空间复杂度O(1)
int main()
{
  vector<int> vt = {3,5,7,1,2};
  selection_sort(vt);
  auto it = vt.begin();
  while(it != vt.end())
  {
    cout << *it << endl;
    it++;
  }
  return 0;
}
