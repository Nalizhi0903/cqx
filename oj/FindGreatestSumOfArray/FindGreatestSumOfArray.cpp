#include <iostream>
#include <vector>
using namespace std;

//输入一个长度为n的整型数组array，数组中的一个或连续多个整数组成一个子数组，子数组最小长度为1。求所有子数组的和的最大值。

class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param array int整型vector 
     * @return int整型
     */
    int FindGreatestSumOfSubArray(vector<int>& array) {
        int cur = array[0];
        int max = array[0];
        for(int i = 1; i < array.size(); i++)
        {
            cur += array[i];
            if(cur < array[i])
                cur = array[i];
            if(cur > max)
                max=cur;
        }
        return max;
    }  
};

int main()
{
    return 0;
}
