#include <iostream>
#include <unordered_set>
#include <string>

using namespace std;
#include <iostream>
#include <string>
using namespace std;
/*
    Given a string s, find the length of the longest substring without repeating characters.
*/
class Solution 
{
public:
  int lengthOfLongestSubstring(string s) 
  {
    string res;
    size_t res_len = 0;
    string tmp_res;
    size_t tmp_len = 0;
    auto iter = s.begin();
    auto last_pos = ++s.begin();
    while (iter != s.end())
    {
      if ((int)tmp_res.find(*iter) == -1 || tmp_res.size() == 0)//将不重复的字符添加到临时的结果集
      {
          tmp_res += *iter;
          tmp_len++;
          if (tmp_len > res_len)//如果临时的结果长度比结果长度长，将临时结果设置为结果
          {
              res = tmp_res;
              res_len = tmp_len;
          }
          iter++;
      }
      else//如果发现重复的字符，从上次开始的下一个字符重新开始寻找
      {
          iter = last_pos;
          last_pos++;
          tmp_res.clear();
          tmp_len = 0;
      }
    }
    return res_len;
  }
};

//滑动窗口方法
class Solution_swap_window {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.size() == 0) return 0;
        unordered_set<char> lookup;
        int maxStr = 0;
        int left = 0;
        for(int i = 0; i < (int)s.size(); i++){
            while (lookup.find(s[i]) != lookup.end()){
                lookup.erase(s[left]);
                left ++;
            }
            maxStr = max(maxStr,i-left+1);
            lookup.insert(s[i]);
    }
        return maxStr;
        
    }
};

int main()
{
    string s1 = "dvdf";
    Solution s;
    cout << s.lengthOfLongestSubstring(s1) << endl;
	return 0;
}
