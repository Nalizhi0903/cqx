#include <iostream>
#include <vector>

using namespace std;

class solution
{
public:
    int single_number(vector<int>& nums)
    {
        int ret = 0;
        for(int i = 0; i<(int)nums.size(); i++)
            ret ^= nums[i];
        return ret;
    }

    int hash(vector<int>& nums)
    {
       int hash[1000];
       for(int i = 0; i < (int)nums.size(); i++)
       {
           hash[nums[i]]++;
       }
       int ret;
       for(int j = 0; j< (int)nums.size(); j++)
       {
           if(hash[nums[j]] == 1)
           {
               ret = nums[j];
           }
       }
       return ret;
    }
};

int main()
{
    vector<int> v{2,2,1};
    solution s;
    cout << s.single_number(v) << endl;;
    return 0;
}
