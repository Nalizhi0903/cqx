#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <queue>
using namespace std;

class Solution 
{
public:
    void transform(string& s)
    {
        for(int i = 0; i< (int)s.size(); ++i)
        {
            if(s[i] >= 'A' && s[i] <= 'Z')
                s[i] += 32;
        }
    }

    bool IsLetterOrDigital(char ch)
    {
        if((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9'))
            return true;
        return false;
    }

    bool IsPalidrome(string s)
    {
        int start = 0;
        int end = s.size()-1;
        //判断是否为回文，遇到不是数字或字母的跳过
        while(start < end)
        {
            transform(s);
            while(start < end && !IsLetterOrDigital(s[start]))
            {
                start++;
            }
             while(start > end && !IsLetterOrDigital(s[start]))
            {
                end--;
            }
            if(s[start] != s[end])
                return false;
            start++;
            end--;
        }
        return true;
    }
};

int main()
{
    Solution s;
    cout << s.IsPalidrome("HEEEH") << endl;
    return 0;
}
