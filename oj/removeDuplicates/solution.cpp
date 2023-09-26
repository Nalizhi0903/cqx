#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int k = 1;
        if (nums.size() <= 1)
        {
            return nums.size();
        }
        vector<int>::iterator cur = nums.begin();
        vector<int>::iterator next = cur + 1;
        while (next != nums.end())
        {
            if (*cur == *next)
            {
                next = nums.erase(next);
            }
            else
            {
                cur++;
                next++;
                k++;
            }
        }
        return k;
    }
};

int main()
{
    vector<int> v = { 1, 1, 2, 3, 4, 5 };
    Solution s;
    s.removeDuplicates(v);
    vector<int>::iterator it = v.begin();

    while (it != v.end())
    {
        cout << *it << " ";
        it++;
    }
    return 0;
}
