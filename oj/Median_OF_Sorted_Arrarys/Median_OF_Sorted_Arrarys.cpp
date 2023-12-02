#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
    {
        vector<double> elem(nums1.size() + nums2.size());
        for (int i = 0; i < (int)elem.size(); i++)
        {
            if (i < (int)nums1.size())
            {
                elem[i] = nums1[i];
            }
            else
            {
                elem[i] = nums2[i - nums1.size()];
            }
        }
        sort(elem.begin(), elem.end());
        if (elem.size() % 2 != 0)
        {
            return elem[elem.size() / 2];
        }
        else
        {
            return (elem[elem.size() / 2 - 1] + elem[elem.size() / 2]) / 2;
        }
    }
};

int main()
{
    //vector<int> v1 = { 1,2,3,4 };
    //vector<int> v2 = { 5,6,7,8 };
    vector<int> v1 = { 1,3 };
    vector<int> v2 = { 2 };
    Solution s1;
    double res = s1.findMedianSortedArrays(v1, v2);
    cout << res << endl;
	return 0;
}
