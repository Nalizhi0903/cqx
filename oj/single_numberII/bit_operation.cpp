#include <iostream>
#include <vector>
/*
给你一个整数数组 nums ，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次 。请你找出并返回那个只出现了一次的元素。
你必须设计并实现线性时间复杂度的算法且使用常数级空间来解决此问题。
 */


using namespace std;

class Solution
{
public:
    int singleNumber(vector<int>& nums)
    {
        int result = 0;
        for(int i = 0; i<32; i++)
        {
        	int count = 0;
            int mask = 0x01 <<i;
            for(int j = 0; j<(int)nums.size(); j++)
            {
                if((nums[j] & mask) != 0)
                    count++;
            }
            if(count % 3 != 0)
            {
                result ^= mask;
            }
        }
        return result;
    }
};

int main()
{
    vector<int> v = {1,2,2,3,8,1,1,2,3,3};
    Solution s;
    cout << s.singleNumber(v) << endl;;
    return 0;
}
