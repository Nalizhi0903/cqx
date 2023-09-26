#include <iostream>
#include <vector>
using namespace std;
//给你一个 非空 整数数组 nums ，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。

//你必须设计并实现线性时间复杂度的算法来解决此问题，且该算法只使用常量额外空间。
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int j, idx;
        for(int i = 0; i<nums.size(); i++)
        {
            for(j = 0; j < nums.size();j++)
            {
                if(i == j)
                    continue;
                if(nums[i] == nums[j])
                    break;
            }
            if(j >= nums.size())
            {
                idx = i;
                break;
            }
        }
        return nums[idx];
    }
};

int main()
{
    vector<int> v{1, 2, 2, 4};
    Solution s;
    cout << s.singleNumber(v) << endl;;
    return 0;
}
