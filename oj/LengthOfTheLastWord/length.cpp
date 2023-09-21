#include <iostream>
#include <string>
using namespace std;
//获得最后一个单词的长度
int getLengthOfWord(const string& s)
{
    int pos = s.rfind(" ");
    cout << pos << endl;
    if(pos == (int)string::npos)
    {
        return s.length();
    }
    else 
        return s.size() - pos - 1;
}

int main()
{
    string s;
    getline(cin, s);
    cout << getLengthOfWord(s) << endl;    
    return 0;
}
