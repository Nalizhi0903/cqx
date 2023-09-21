#include <iostream>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int AddItem(int a, int b, int& sign)
    {
        int sum = a + b;
        if(sum >= 10)
        {
            sum -= 10;
            sign = 1;
        }
        else 
        {
            sign = 0;
        }
        return sum;
    }

    string addString(string num1, string num2)
    {
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        
        string result;

        size_t i = 0, j= 0;
        int sign = 0;
        int sum = 0;
        while(i < num1.size() && j < num2.size())
        {
            sum = AddItem(num1[i] - '0', num2[j] - '0', sign);
            result += (sum + '0');
            i++;
            j++;
        }
        while(i < num1.size())
        {
            sum = AddItem(num1[i] - '0', 0, sign);
            result += sum;
            i++;
        }
        while(j < num2.size())
        {
            sum = AddItem(0, num2[j] - '0', sign);
            result += (sum + '0');
            j++;
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

int main()
{
    Solution s;
    string s1 = "1234";
    string s2 = "5567";
    cout << s1 << "+" << s2 << "= " << s.addString(s1, s2) << endl;
    cout << s1 + s2 << endl;
    return 0;
}
