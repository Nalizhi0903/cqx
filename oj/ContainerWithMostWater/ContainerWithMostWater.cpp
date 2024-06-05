#include <iostream>
#include <vector>

class Solution{
public:
  int maxArea(std::vector<int>& height)
  {
    //初始化数据，对应的下标赋值对应的高度
    std::vector<int> input;
    auto it = height.begin();
    while(it != height.end())
    {
      input.push_back(*it);
      std::cout << *it << std::endl;
      it++;
    }
    //双指针法
    int i = 0;
    int j = input.size() - 1;
    int maxArea = 0;
    int area =  0;
    while(i < j)
    {
      //计算当前区块大小
      area = caculateAre(i, j, input);

      //如果比最大值大，将其设置为最大值
      if(area > maxArea)
      {
        maxArea = area;
      }

      //移动高度较矮的一端
      if(input[i] > input[j])
      {
        j--;
      }
      else 
      {
        i++;
      }

     }
    return maxArea;
  }
  
  //计算区域大小函数
  int caculateAre(int idx1, int idx2, std::vector<int>& input)
  {
      int minHeight = std::min(input[idx1], input[idx2]); 
      int width = 0;
      width = idx2 - idx1;
      return minHeight * width;
  }

};

int main()
{
  std::vector<int> inputHeight = {1,8,6,2,5,4,8,3,7};
  Solution s;
  std::cout << s.maxArea(inputHeight) << std::endl;

  return 0;
}
