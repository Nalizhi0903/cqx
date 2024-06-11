#include <iostream>
#include <vector> 
#include <algorithm>
#include <set>

using namespace std;

class Solution
{
public:
  vector<vector<int>> threeSum(vector<int>& nums)
  {
    vector<vector<int>> res;
    vector<int> vecLeft;
    vector<int> vecRight;
    std::sort(nums.begin(), nums.end());
    auto it = nums.begin();
    while(it != nums.end())
    {
      if(*it >= 0)
      {
        vecRight.push_back(*it);
      }
      else
      {
        vecLeft.push_back(*it);
      }
      it++;
    }
    vector<vector<int>> leftComb= combine(vecLeft);
    vector<vector<int>> rightComb= combine(vecRight);
    cout << "combination" << endl;
    print(leftComb);
    print(rightComb);
    if(leftComb.size() >= rightComb.size())
    {
      cout << "left compare" << "leftComb size" << leftComb.size() << "rightComb size" << rightComb.size()<< endl;
      res = compare(leftComb, rightComb);
    }
    else 
    {
      cout << "right compare" << "leftComb size" << leftComb.size() << "rightComb size" << rightComb.size()<< endl;
      res = compare(rightComb, leftComb);
    }
    cout << "res" << endl;
    print(res);
    return res;
  }

  vector<vector<int>> combine(vector<int>& vt)
  {
    vector<vector<int>> combination;
    vector<int> zero;
    for(size_t i = 0; i < vt.size(); i++)
    {
      vector<int> itself;
      itself.push_back(vt[i]);
      combination.push_back(itself);
      for(size_t j = i + 1; j < vt.size(); j++)
      {
        if(vt[i] == 0)
        {
          zero.push_back(0);
        }
        vector<int> tmp;
        tmp.push_back(vt[i]);
        tmp.push_back(vt[j]);
        tmp.push_back(vt[i] + vt[j]);
        combination.push_back(tmp);
      }
    }
    if(zero.size() >= 3)
    {
      vector<int> zeroRes{0,0,0,0};
      combination.push_back(zeroRes);
    }
    return combination;
  }

  vector<vector<int>> compare(vector<vector<int>> &bigVec, vector<vector<int>> &smallVec)
  {
    print(bigVec);
    print(smallVec);
    cout << "compare" << endl;
    vector<vector<int>> res;
    if(bigVec.at(bigVec.size() - 1).size() == 4 || smallVec.at(smallVec.size()-1).size() == 4)
    {
      vector<int> zeroRes{ 0, 0, 0};
      res.push_back(zeroRes);
    }  
    set<int> mark;
    for(size_t i = 0; i < bigVec.size(); i++)
    {
      for(size_t j = 0; j < smallVec.size(); j++)
      {
        if(bigVec[i].size() > smallVec[j].size())
        {
          auto it = mark.find(j);
          if(it != mark.end())
            continue;
          cout << bigVec[i][bigVec[i].size() - 1] << smallVec[j][0] << endl;
          if(bigVec[i][bigVec[i].size() - 1] == -smallVec[j][0])
          {
            mark.insert(j);
            cout << "big mark" << j << endl;
            vector<int> tmp;
            for(size_t k = 0; k < bigVec[i].size() - 1; k++)
            {
              tmp.push_back(bigVec[i][k]);
            }
            tmp.push_back(smallVec[j][0]);
            res.push_back(tmp);
          }
        }
        else if(bigVec[i].size() < smallVec[j].size())
        {
          cout << bigVec[i][bigVec[i].size() - 1] << smallVec[j][0] << endl;
          auto it = mark.find(j);
          if(it != mark.end())
            continue;
          if(bigVec[i][0] == -smallVec[j][smallVec[j].size() - 1])
          {
            mark.insert(j);
            cout << "small mark" << j << endl;
            vector<int> tmp;
            for(size_t k = 0; k < smallVec[j].size() - 1; k++)
            {
              tmp.push_back(smallVec[j][k]);
            }
            tmp.push_back(bigVec[i][0]);
            res.push_back(tmp);
          }
        }
      }
    }
    return res;
  }

  void print(vector<vector<int>>& vt)
  {
    auto it = vt.begin();
    while(it != vt.end())
    {
      auto it1 = it->begin();
      while(it1 != it->end())
      {
        cout << *it1 << " ";
        it1++;
      }
      cout << endl;
      it++;
    }
  }
};
int main()
{
  vector<int> nums1{-1, 0, 1, 2, -1, -4};
  vector<int> nums2{0, 1, 1};
  vector<int> nums3{0, 0, 0};
  Solution s;
  s.threeSum(nums3);
  return 0;
}
