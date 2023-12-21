#include <iostream>
#include <vector>
using namespace std;

void swap(vector<int>& vt, int num1, int num2)
{
  int tmp = vt[num1];
  vt[num1] = vt[num2];
  vt[num2] = tmp;
}

int partition(vector<int>& vt, int left, int right)
{
  int i = left;
  int j = right;
  while(i < j)
  {
    while(i < j && vt[j] >= vt[left])
    {
      j--; 
    }
    while(i < j && vt[i] <= vt[left])
    {
      i++;
    }
    swap(vt,i,j);
  }
  swap(vt, i, left);
  return i;
}

void quick_sort(vector<int>& vt, int left, int right)
{
  if(left >= right)
  {
    return;
  }
  int pivot = partition(vt, left, right);
  quick_sort(vt, left, pivot - 1);
  quick_sort(vt, pivot + 1, right);
}
//空间复杂的O(nlogn)空间复杂度O(n)、原地排序：在输入数组完全倒序的情况下，达到最差递归深度n，使用O(n)栈帧空间。排序操作是在原数组上进行的，未借助额外数组。
int main()
{
  vector<int> vt = {1,3,2,8,6,4,5};
  quick_sort(vt, 0, vt.size() - 1);
  for(auto& e : vt)
  {
    cout << e << endl;
  }
  return 0;
}
