#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int k = 1;
        if (nums.size() <= 1)
            return nums.size();
        vector<int>::iterator p1 = nums.begin();
        vector<int>::iterator p2 = p1 + 1;
        vector<int>::iterator tmp = p1 + 1;
        while (p2 != nums.end())
        {
            if (*p1 == *p2)
            {
                p2++;
            }
            else
            {
                while (p1 != p2)
                { 
                    p1++;
                    *p1 = *p2;
                }
                p1 = tmp++;
                k++;
            }
        }
        return k;
    }
};

class Solution_best
{
public:
    int removeDuplicates(vector<int>& nums)
    {
        int p = 0;
        int q = 1;
        while (q < (int)nums.size())
        {
            if (nums[p] != nums[q])
            {
                nums[++p] = nums[q];
            }
            q++;
        }
        return p + 1;
    }
};

int main()
{
    Solution s;
    vector<int> v = {1, 1, 2, 2, 4, 5, 6, 8, 8};
    cout << s.removeDuplicates(v) << endl;
    return 0;
}
