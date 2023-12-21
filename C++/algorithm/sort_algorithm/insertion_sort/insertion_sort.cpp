#include <iostream>
#include <vector>

using namespace std;
//在未排序区间选择一个基准元素，将该元素与其左侧已排序区间的元素逐一比较大小，并将该元素插入到正确的位置。
void insertion_sort(vector<int>& vt)
{
  for(int i = 1; i< (int)vt.size(); i++)
  {
    int base = vt[i];
    int j = i - 1;
    while(j >= 0 && vt[j]> base)
    {
      vt[j+1] = vt[j];
      j--;
    }
    vt[j+1] = base;
  }
}
//时间复杂度O(n^2) 空间复杂度O(1)
int main()
{
  vector<int> vt = {5,7,3,4,1,2};
  insertion_sort(vt);
  for(auto& e : vt)
  {
    cout << e << endl;
  }
  return 0;
}

