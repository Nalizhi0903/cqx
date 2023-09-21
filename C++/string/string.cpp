#include <iostream> 
#include <string>
//#include <string.h>
using namespace std;

namespace bit
{
    class string 
    {
    public:

    private:
    char* _str;        
    };
}

/*
class String
{
public:
    String(const char* str ="")
    {
        _str = new char[strlen(str)+1];
        strcpy(_str, str);
    }
    
    String(const String& s):_str(nullptr)
    {
        String strTmp(s._str);
        swap(_str, strTmp._str);
    }
    /*
    String& operator=(const String& s)
    {
        if(this != &s)
        {
            delete []_str;
            _str = new char[strlen(s._str)+1];//异常不安全
            strcpy(_str, s._str);
        }
        return *this;
    }*/
    /*
    String& operator=(const String& s)
    {
        if(this != &s)
        {
            String strTmp(s);
            swap(_str, strTmp._str);
        }
        return *this;
    }

    ~String()
    {
        if(_str)
        {
            delete[] _str;
            _str = nullptr;
        }
    }
private:
    char* _str;
};

int main()
{
    String s;
}
*/
/*
int main()
{
    string s = "Hello";
    string s1 = s;
    s.resize(3);
    cout << "size is " << s.size() << endl;
    cout << "capacity is " << s.capacity() << endl;
    
    string input;
    //cin>>input;//以空格自动分隔
    //cout << "input = " << input << endl;
    getline(cin, input);
    cout << "input = " << input << endl;
    return 0;
}*/
