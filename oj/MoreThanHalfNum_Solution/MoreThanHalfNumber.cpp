#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int MoreThanHalfNumber(vector<int> number)
    {
        sort(number.begin(), number.end());
        return number[number.size()/2];
    }
};
int main()
{
    Solution s;
    vector<int> v = {1, 2, 3, 4, 2, 2, 2, 2, 2};
    cout << s.MoreThanHalfNumber(v) << endl;;
    return 0;
}
